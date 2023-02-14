#pragma once

#include "gpio.h"
#include "mem.h"
#include "time.h"
#include "types.h"

#define _ASCII_CMD_RS     0x01
#define _ASCII_CMD_RW     0x02
#define _ASCII_CMD_SELECT 0x04
#define _ASCII_CMD_ENABLE 0x40

#define _ASCII_NL '\n'
#define _ASCII_CR '\r'

#define _ASCII_WAIT_STATE_FLAG(self)                                         \
	while ((_ascii_read_status(self) & 0x80) == 0x80)

// FIXME: might be broken
#define _ASCII_CTRL_BIT_SET(self, mask)                                      \
	BIT_SET(uint8_t, &self->port->odr_low, mask)

#define _ASCII_CTRL_BIT_CLEAR(self, mask)                                    \
	BIT_CLEAR(uint8_t, &self->port->odr_low, mask)

typedef struct {
	PGPIO port;
} ASCII;

// Constructor
void ascii_connect(ASCII *self, PGPIO port);
// Set cursor pos
void ascii_set_cursor(ASCII *self, uint8_t x, uint8_t y);
// Write string to display
void ascii_puts(ASCII *self, uint8_t x, uint8_t y, char *text);

// Read from the display controller
uint8_t _ascii_read_ctrl(ASCII *self);

// Write to the display controller
void _ascii_write_ctrl(ASCII *self, uint8_t cmd);
// Write char to display
void _ascii_write_char(ASCII *self, uint8_t c);

// Write a command to the display
void _ascii_write_cmd(ASCII *self, uint8_t cmd);
// Write data to the data port
void _ascii_write_data(ASCII *self, uint8_t data);
// Read status of the display
uint8_t _ascii_read_status(ASCII *self);
// Read data from the display
uint8_t _ascii_read_data(ASCII *self);
