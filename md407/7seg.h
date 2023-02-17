#include "gpio.h"

#define ISALPHA(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))

static const uint8_t seg_codes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
                                    0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C,
                                    0x39, 0x5E, 0x79, 0x71};

typedef struct {
	PGPIO port;
	char c;
} SEVENSEG;

// Function to convert char to 7seg char
int _sevenseg_get_char_index(char c);

// Function to connect 7 seg display to port
void sevenseg_connect(SEVENSEG *self, PGPIO port);
// Function to write to display
void sevenseg_write(SEVENSEG *self, char c);

/* IMPLEMENTATION */

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
