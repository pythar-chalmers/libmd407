#include "ascii.h"

void ascii_connect(ASCII *self, PGPIO port) {
	// Start the clock for the GPIO D & E ports
	self->port = port;

	// Set port state
	self->port->moder = 0x00005555;

	_ASCII_CTRL_BIT_CLEAR(_ASCII_CMD_RW);
	_ASCII_CTRL_BIT_CLEAR(_ASCII_CMD_RS);

	// Display control
	_ASCII_WAIT_STATE_FLAG;
	delay_micro(8);
	_ascii_write_cmd(self, 0b00001111);
	delay_micro(40);

	// Function set
	_ASCII_WAIT_STATE_FLAG;
	delay_micro(8);
	_ascii_write_cmd(self, 0b00111011);
	delay_micro(40);

	// Clear screen & set cursor at 0, 0
	ascii_clear(self);

	// Entry mode set
	_ASCII_WAIT_STATE_FLAG;
	delay_micro(8);
	_ascii_write_cmd(self, 0b00000110);
	delay_micro(40);
}

void _ascii_write_ctrl(ASCII *self, uint8_t cmd) {
	// Enable control bit
	_ASCII_CTRL_BIT_SET(_ASCII_CMD_ENABLE);

	// Write command
	self->port->odr_high = cmd;

	// Wait and disable
	delay_250ns(); // should be 230 but 250 is more safe
	_ASCII_CTRL_BIT_CLEAR(_ASCII_CMD_ENABLE);
}

uint8_t _ascii_read_ctrl(ASCII *self) {
	uint8_t rv;
	_ASCII_CTRL_BIT_SET(_ASCII_CMD_ENABLE);

	delay_nano(360);

	rv = self->port->idr_high;

	_ASCII_CTRL_BIT_CLEAR(_ASCII_CMD_ENABLE);

	return rv;
}

void _ascii_write_cmd(ASCII *self, uint8_t cmd) {
	_ASCII_CTRL_BIT_CLEAR(_ASCII_CMD_RS | _ASCII_CMD_RW); // RS = 0, RW = 0
	_ascii_write_ctrl(self, cmd);
}

void _ascii_write_data(ASCII *self, uint8_t data) {
	// Set the controller to write mode
	_ASCII_CTRL_BIT_CLEAR(_ASCII_CMD_RW); // RW=0
	_ASCII_CTRL_BIT_SET(_ASCII_CMD_RS);   // RS=1

	// Write the data
	_ascii_write_ctrl(self, data);
}

uint8_t _ascii_read_status(ASCII *self) {
	self->port->moder &= 0x0000FFFF;

	_ASCII_CTRL_BIT_CLEAR(_ASCII_CMD_RS);
	_ASCII_CTRL_BIT_SET(_ASCII_CMD_RW);

	uint8_t rv;
	rv = _ascii_read_ctrl(self);

	self->port->moder |= 0x55550000;

	return rv;
}

uint8_t _ascii_read_data(ASCII *self) {
	_ASCII_CTRL_BIT_SET(_ASCII_CMD_RW);
	_ASCII_CTRL_BIT_SET(_ASCII_CMD_RS);

	uint8_t rv;
	rv = _ascii_read_ctrl(self);

	return rv;
}

void _ascii_write_char(ASCII *self, uint8_t c) {
	_ASCII_WAIT_STATE_FLAG;
	_ascii_write_data(self, c);
	delay_micro(44); // 43
}

void ascii_set_cursor(ASCII *self, uint8_t x, uint8_t y) {
	int offset = x;
	offset += 0x40 * y;

	_ascii_write_cmd(self, 0x80 | offset);
}

void ascii_puts(ASCII *self, uint8_t x, uint8_t y, char *text) {
	ascii_set_cursor(self, x, y);
	do {
		switch (*text) {
		case _ASCII_NL:
			ascii_set_cursor(self, x, ++y);
			continue;
		case _ASCII_CR:
			ascii_set_cursor(self, 0, y);
			continue;
		default:
			_ascii_write_char(self, *text);
			break;
		}
	} while (*text++);
}

void ascii_clear(ASCII *self) {
	// Clear the screen
	_ASCII_WAIT_STATE_FLAG;
	delay_micro(8);
	_ascii_write_cmd(self, 1);
	delay_milli(2);

	// Return home
	_ASCII_WAIT_STATE_FLAG;
	delay_micro(8);
	_ascii_write_cmd(self, 2);
	delay_milli(2);
}
