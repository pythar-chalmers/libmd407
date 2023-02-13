#include "keypad.h"

/**
 *  Initialize the keypad driver
 *
 * @param keypad The keypad struct to initialize
 * @param port The GPIO port that the keypad is connected to.
 * @param isHigher If the keypad is connected to the higher 8 pins of the
 * port.
 */
void _Keypad_connect(Keypad *self, PGPIO port) {
	self->port = port;

	// Set the output pins to high and the input pins to low
	self->port->moder = 0x5500;

	// Set the output type to push-pull
	self->port->otyper = 0x0000;

	// Set the speed to high
	self->port->ospeedr = 0x5555;

	// Set the input type to pull-up
	self->port->pupdr = 0x0066;
}

/**
 *  Get the key that is currently pressed
 *
 * @param keypad The keypad struct to use
 * @return The key that is currently pressed. If no key is pressed, 0xFF is
 * returned.
 */
char _Keypad_read(Keypad *self) {
	keypad->port->odr = 0;

	for (uint8_t i = 0; i < 4; i++) {
		keypad->port->odr = 0x10 << i;

		for (uint8_t j = 0; j < 4; j++) {
			if (keypad->port->idr_high & (1 << j)) {
				keypad->port->odr = 0;
				return keypad->map[i][j];
			}
		}
	}

	keypad->port->odr = 0;
	return 0xFF;
}
