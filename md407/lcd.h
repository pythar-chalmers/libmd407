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

#define _LCD_WAIT_STATE_FLAG while ((_lcd_read_status(self) & 0x80) == 0x80)

// FIXME: might be broken
#define _LCD_CTRL_BIT_SET(mask)                                              \
	BIT_SET(uint8_t, &self->port->odr_low, mask | _LCD_CMD_SELECT)

#define _LCD_CTRL_BIT_CLEAR(mask)                                            \
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

/* IMPLEMENTATION */

void lcd_connect(LCD *self, PGPIO port) {
	// Start the clock for the GPIO D & E ports
	self->port = port;

	// Set port state
	self->port->moder = 0x00005555;

	_LCD_CTRL_BIT_CLEAR(_LCD_CMD_RW);
	_LCD_CTRL_BIT_CLEAR(_LCD_CMD_RS);

	// Display control
	_LCD_WAIT_STATE_FLAG;
	delay_micro(8);
	_lcd_write_cmd(self, 0b00001111);
	delay_micro(40);

	// Function set
	_LCD_WAIT_STATE_FLAG;
	delay_micro(8);
	_lcd_write_cmd(self, 0b00111011);
	delay_micro(40);

	// Clear screen & set cursor at 0, 0
	lcd_clear(self);

	// Entry mode set
	_LCD_WAIT_STATE_FLAG;
	delay_micro(8);
	_lcd_write_cmd(self, 0b00000110);
	delay_micro(40);
}

void _lcd_write_ctrl(LCD *self, uint8_t cmd) {
	// Enable control bit
	_LCD_CTRL_BIT_SET(_LCD_CMD_ENABLE);

	// Write command
	self->port->odr_high = cmd;

	// Wait and disable
	delay_250ns(); // should be 230 but 250 is more safe
	_LCD_CTRL_BIT_CLEAR(_LCD_CMD_ENABLE);
}

uint8_t _lcd_read_ctrl(LCD *self) {
	uint8_t rv;
	_LCD_CTRL_BIT_SET(_LCD_CMD_ENABLE);

	delay_nano(360);

	rv = self->port->idr_high;

	_LCD_CTRL_BIT_CLEAR(_LCD_CMD_ENABLE);

	return rv;
}

void _lcd_write_cmd(LCD *self, uint8_t cmd) {
	_LCD_CTRL_BIT_CLEAR(_LCD_CMD_RS | _LCD_CMD_RW); // RS = 0, RW = 0
	_lcd_write_ctrl(self, cmd);
}

void _lcd_write_data(LCD *self, uint8_t data) {
	// Set the controller to write mode
	_LCD_CTRL_BIT_CLEAR(_LCD_CMD_RW); // RW=0
	_LCD_CTRL_BIT_SET(_LCD_CMD_RS);   // RS=1

	// Write the data
	_lcd_write_ctrl(self, data);
}

uint8_t _lcd_read_status(LCD *self) {
	self->port->moder &= 0x0000FFFF;

	_LCD_CTRL_BIT_CLEAR(_LCD_CMD_RS);
	_LCD_CTRL_BIT_SET(_LCD_CMD_RW);

	uint8_t rv;
	rv = _lcd_read_ctrl(self);

	self->port->moder |= 0x55550000;

	return rv;
}

uint8_t _lcd_read_data(LCD *self) {
	_LCD_CTRL_BIT_SET(_LCD_CMD_RW);
	_LCD_CTRL_BIT_SET(_LCD_CMD_RS);

	uint8_t rv;
	rv = _lcd_read_ctrl(self);

	return rv;
}

void _lcd_write_char(LCD *self, uint8_t c) {
	_LCD_WAIT_STATE_FLAG;
	_lcd_write_data(self, c);
	delay_micro(44); // 43
}

void lcd_set_cursor(LCD *self, uint8_t x, uint8_t y) {
	int offset = x;
	offset += 0x40 * y;

	_lcd_write_cmd(self, 0x80 | offset);
}

void lcd_puts(LCD *self, uint8_t x, uint8_t y, char *text) {
	lcd_set_cursor(self, x, y);
	do {
		switch (*text) {
		case _LCD_NL:
			lcd_set_cursor(self, x, ++y);
			continue;
		case _LCD_CR:
			lcd_set_cursor(self, 0, y);
			continue;
		default:
			_lcd_write_char(self, *text);
			break;
		}
	} while (*text++);
}

void lcd_clear(LCD *self) {
	// Clear the screen
	_LCD_WAIT_STATE_FLAG;
	delay_micro(8);
	_lcd_write_cmd(self, 1);
	delay_milli(2);

	// Return home
	_LCD_WAIT_STATE_FLAG;
	delay_micro(8);
	_lcd_write_cmd(self, 2);
	delay_milli(2);
}
