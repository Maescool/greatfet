#!/usr/bin/env python
#
# This file is part of GreatFET

from __future__ import print_function

import argparse
import shutil
import sys
import os

from greatfet import GreatFET
from greatfet import find_greatfet_asset


def ensure_access_linux():
    """ Installs udev rules as appropriate for the Linux distribution. """

    rules_target_path = '/etc/udev/rules.d/54-greatfet.rules'

    # The 'canonical' way to test if systemd is running, from man page sd_booted(3).
    has_systemd = os.path.isdir('/run/systemd/system')

    try:

        if has_systemd:

            # Use uaccess udev rules on systems with systemd
            uaccess_rules = find_greatfet_asset('54-greatfet-uaccess.rules')

            if uaccess_rules is None:
                raise FileNotFoundError('Could not find uaccess udev rules!')

            print('Copying uaccess udev rules...')
            shutil.copy(uaccess_rules, rules_target_path)

        else:
            # Otherwise use plugdev udev rules
            plugdev_rules = find_greatfet_asset('54-greatfet-plugdev.rules')

            if plugdev_rules is None:
                raise FileNotFoundError('Could not find plugdev udev rules!')

            print('Copying plugdev udev rules...')
            shutil.copy(plugdev_rules, rules_target_path)

    except PermissionError:
        raise PermissionError('Failed to copy udev rules to {}! Maybe try with sudo -E?'.format(rules_target_path)) from None

    print('Done')


def ensure_access():
    """ Ensures that the system is set up to have permissions to access GreatFETs. """

    if 'linux' in sys.platform:
        ensure_access_linux()

    elif 'win32' in sys.platform:
        # TODO: install libusb with libwdi?
        raise NotImplementedError()

    else:
        raise RuntimeError('Unknown or unsupported system!')


def main():

    # Set up a simple argument parser
    parser = argparse.ArgumentParser(description="Utilities for managing the host tools")
    parser.add_argument('--ensure-access', dest='ensure_access', action='store_true')
    args = parser.parse_args()

    if not any((args.ensure_access,)):
        parser.print_help()
        sys.exit(0)

    if args.ensure_access:
        ensure_access()
