/*
 * This file is part of GreatFET
 */

#ifndef __SWRA124_H__
#define __SWRA124_H__

#include <stddef.h>
#include <stdint.h>

#define SWRA124_MAX_INSTR_SIZE 4
#define SWRA124_STATUS_CPUHALTED 0x20

#define HIBYTE_WORDS_PER_FLASH_PAGE 0x02
#define LOBYTE_WORDS_PER_FLASH_PAGE 0x00

/** Ugh, this varies by chip.
    0x800 for CC2430
    0x400 for CC1110
*/
//#define FLASHPAGE_SIZE 0x400
#define MAXFLASHPAGE_SIZE 0x800
#define MINFLASHPAGE_SIZE 0x400

// Debug Command definitions
// From datasheet Table 45 page 73
#define SWRA124_CMD_CHIP_ERASE 0x14
#define SWRA124_CMD_WR_CONFIG 0x1D
#define SWRA124_CMD_RD_CONFIG 0x24
#define SWRA124_CMD_GET_PC 0x28
#define SWRA124_CMD_READ_STATUS 0x34
#define SWRA124_CMD_SET_HW_BRKPNT 0x3B
#define SWRA124_CMD_HALT 0x44
#define SWRA124_CMD_RESUME 0x4C
#define SWRA124_CMD_DEBUG_INSTR 0x54
#define SWRA124_CMD_STEP_INSTR 0x5C
#define SWRA124_CMD_GET_CHIP_ID 0x68

//! Flash Word Size
extern uint8_t flash_word_size;

void swra124_setup();
void swra124_debug_init();
void swra124_debug_stop();
void swra124_chip_erase();
uint8_t swra124_read_config();
uint8_t swra124_write_config(const uint8_t config);
uint8_t swra124_read_status();
uint16_t swra124_get_chip_id();
void swra124_halt();
void swra124_resume();
uint8_t swra124_debug_instr(const uint8_t *instr, const size_t size);
void swra124_step_instr();
uint16_t swra124_get_pc();
void swra124_set_pc(const uint16_t v);
void swra124_set_hw_breakpoint(const uint8_t bp, const uint8_t active, const uint16_t adr);
uint8_t swra124_peek_code_byte(const uint32_t adr);
uint8_t swra124_peek_data_byte(const uint16_t adr);
void swra124_poke_data_byte(const uint16_t adr, const uint8_t val);
void swra124_write_flash_page(const uint32_t adr);
#endif
