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

#define _ASCII_WAIT_STATE_FLAG(display)                                      \
	while ((_ascii_read_status(display) & 0x80) == 0x80)

// FIXME: might be broken
#define _ASCII_CTRL_BIT_SET(display, mask)                                   \
	BIT_SET(uint8_t, &display->port->odr_low, mask)

#define _ASCII_CTRL_BIT_CLEAR(display, mask)                                 \
	BIT_CLEAR(uint8_t, &display->port->odr_low, mask)

typedef struct {
	PGPIO port;
	char *text1;
	char *text2;
} ASCII;

static char *_ASCII_EMPTY_TEXT = {0};

// Write to the display controller
void _ascii_write_ctrl(ASCII *display, uint8_t cmd);
// Read from the display controller
uint8_t _ascii_read_controller(ASCII *display);

// Write a command to the display
void _ascii_write_cmd(ASCII *display, uint8_t cmd);
// Write data to the data port
void _ascii_write_data(ASCII *display, uint8_t data);
// Read status of the display
uint8_t _ascii_read_status(ASCII *display);
// Read data from the display
uint8_t _ascii_read_data(ASCII *display);

// Write char to display
void _ascii_write_char(ASCII *display, uint8_t c);
// Set cursor pos
void ascii_set_cursor(ASCII *display, uint8_t x, uint8_t y);
// Write string to display
void ascii_puts(ASCII *display, uint8_t x, uint8_t y, char *text);

// Constructor
void ascii_connect(ASCII *display, PGPIO port);
// Sync text to display
void _ascii_sync(ASCII *display);
