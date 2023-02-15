#pragma once

#include "gpio.h"
#include "mem.h"
#include "time.h"
#include "types.h"

#define _LCD_CMD_RS     1
#define _LCD_CMD_RW     2
#define _LCD_CMD_SELECT 4
#define _LCD_CMD_ENABLE 0x40

#define _LCD_NL '\n'
#define _LCD_CR '\r'

#define _LCD_WAIT_STATE_FLAG                                               \
	while ((_lcd_read_status(self) & 0x80) == 0x80)

// FIXME: might be broken
#define _LCD_CTRL_BIT_SET(mask)                                            \
	BIT_SET(uint8_t, &self->port->odr_low, mask | _LCD_CMD_SELECT)

#define _LCD_CTRL_BIT_CLEAR(mask)                                          \
	BIT_CLEAR(uint8_t, &self->port->odr_low, mask | _LCD_CMD_SELECT)

typedef struct {
	PGPIO port;
} LCD;

// Constructor
void lcd_connect(LCD *self, PGPIO port);
// Set cursor pos
void lcd_set_cursor(LCD *self, uint8_t x, uint8_t y);
// Write string to display
void lcd_puts(LCD *self, uint8_t x, uint8_t y, char *text);
// Clear the display
void lcd_clear(LCD *self);

// Read from the display controller
uint8_t _lcd_read_ctrl(LCD *self);

// Write to the display controller
void _lcd_write_ctrl(LCD *self, uint8_t cmd);
// Write char to display
void _lcd_write_char(LCD *self, uint8_t c);

// Write a command to the display
void _lcd_write_cmd(LCD *self, uint8_t cmd);
// Write data to the data port
void _lcd_write_data(LCD *self, uint8_t data);
// Read status of the display
uint8_t _lcd_read_status(LCD *self);
// Read data from the display
uint8_t _lcd_read_data(LCD *self);
