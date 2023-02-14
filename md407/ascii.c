#include "ascii.h"

void ascii_connect(ASCII *display, PGPIO port) {
	display->port  = port;
	display->text1 = _ASCII_EMPTY_TEXT;
	display->text2 = _ASCII_EMPTY_TEXT;

	// NOTE: &... may be broken
	_ASCII_CTRL_BIT_CLEAR(display, _ASCII_CMD_RW | _ASCII_CMD_SELECT);
	_ASCII_CTRL_BIT_CLEAR(display, _ASCII_CMD_RS | _ASCII_CMD_SELECT);

	// Display control
	_ASCII_WAIT_STATE_FLAG(display);
	delay_micro(8);
	_ascii_write_cmd(display, 0b00001111);
	delay_micro(40);

	// Function set
	_ASCII_WAIT_STATE_FLAG(display);
	delay_micro(8);
	_ascii_write_cmd(display, 0b00111011);
	delay_micro(40);

	// Clear screen
	_ASCII_WAIT_STATE_FLAG(display);
	delay_micro(8);
	_ascii_write_cmd(display, 1);
	delay_milli(2);

	// Entry mode set
	_ASCII_WAIT_STATE_FLAG(display);
	delay_micro(8);
	_ascii_write_cmd(display, 0b00000110);
	delay_micro(40);
}

void _ascii_write_ctrl(ASCII *display, uint8_t cmd) {
	// Enable control bit
	_ASCII_CTRL_BIT_SET(display, _ASCII_CMD_ENABLE);

	// Write command
	display->port->odr_high = cmd;

	// Wait and disable
	delay_250ns();
	_ASCII_CTRL_BIT_CLEAR(display, _ASCII_CMD_ENABLE);
}

uint8_t _ascii_read_ctrl(ASCII *display) {
	uint8_t rv;
	_ASCII_CTRL_BIT_SET(display, _ASCII_CMD_ENABLE);

	// FIXME: 360 ns
	delay_250ns();
	delay_250ns();

	rv = display->port->idr_high;

	_ASCII_CTRL_BIT_CLEAR(display, _ASCII_CMD_ENABLE);

	return rv;
}

void _ascii_write_cmd(ASCII *display, uint8_t cmd) {
	_ASCII_CTRL_BIT_CLEAR(display, _ASCII_CMD_RS | _ASCII_CMD_RW);
	_ascii_write_ctrl(display, cmd);
}

void _ascii_write_data(ASCII *display, uint8_t data) {
	// Set the controller to write mode
	_ASCII_CTRL_BIT_CLEAR(display, _ASCII_CMD_RW);
	_ASCII_CTRL_BIT_SET(display, _ASCII_CMD_RS);

	// Send cmd
	_ascii_write_ctrl(display, data);
}

uint8_t _ascii_read_status(ASCII *display) {
	display->port->moder &= 0x0000FFFF;

	_ASCII_CTRL_BIT_CLEAR(display, _ASCII_CMD_RS);
	_ASCII_CTRL_BIT_SET(display, _ASCII_CMD_RW);

	uint8_t rv;
	rv = _ascii_read_controller(display);

	display->port->moder |= 0x55550000;

	return rv;
}

uint8_t _ascii_read_data(ASCII *display) {
	_ASCII_CTRL_BIT_SET(display, _ASCII_CMD_RS);
	_ASCII_CTRL_BIT_SET(display, _ASCII_CMD_RW);

	return _ascii_read_controller(display);
}

void _ascii_write_char(ASCII *display, uint8_t c) {
	_ASCII_WAIT_STATE_FLAG(display);
	_ascii_write_data(display, c);
	delay_micro(43);
}

void ascii_set_cursor(ASCII *display, uint8_t x, uint8_t y) {
	// FIXME: weird?
	int offset = x;
	offset += 0x40 * y;

	_ascii_write_cmd(display, 0x80 | offset);
}

void ascii_puts(ASCII *display, uint8_t x, uint8_t y, char *text) {
	ascii_set_cursor(display, x, y);
	while(*text++) {
		switch(*text) {
		case _ASCII_NL:
			ascii_set_cursor(display, x, y+1);
			continue;
		case _ASCII_CR:
			ascii_set_cursor(display, 0, y);
			continue;
		default:
			_ascii_write_char(display, *text);
			break;
		}
	}
}
