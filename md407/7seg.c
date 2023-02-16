#include "7seg.h"

void sevenseg_connect(SEVENSEG *self, PGPIO port) {
	self->port = port;

	// pin 7-0 outport
	// pin 15-8 inport
	port->moder = 0x55005555;

	// GPIO OT
	port->otyper = 0x00FF;

	// GPIO PUPDR
	port->pupdr_high = 0x00AA;
}

int _sevenseg_get_char_index(char c) {
	if (ISALPHA(c)) {
		return c - 'A' + 10;
	}

	return c - '0';
}

void sevenseg_write(SEVENSEG *self, char c) {
	self->c = c;

	int index = _sevenseg_get_char_index(self->c);
	if (index >= 16) {
		self->port->odr_low = 0x0;
	} else {
		self->port->odr_low = seg_codes[index];
	}
}
