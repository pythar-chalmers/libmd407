#include "keypad.h"

/**
 *  Initialize the keypad driver
 *
 * @param self Pointer to the keypad (self)
 * @param port The GPIO port that the keypad is connected to.
 * @param high_port If the keypad is connected to the higher 8 pins of the
 * port.
 */
void keypad_connect(Keypad *self, PGPIO port, boolean high_port) {
	// Start the clock for the GPIO D & E ports
	*((unsigned long *) 0x40023830) = 0x18;

	self->_port = port;        // Assign the port base
	self->map   = &KEYPAD_MAP; // Assign default keymap

	/* Assign each register pins to the keypad */
	_KEYPAD_ASSIGN_REGISTERS(moder, uint16_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(otyper, uint8_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(ospeedr, uint16_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(pupdr, uint16_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(idr, uint8_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(odr, uint8_t, high_port);

	/* Configure the pins */
	// Set the output pins to high and the input pins to low
	*self->_moder = 0x5500;

	/* // Set the output type to push-pull */
	*self->_otyper = 0x0000;

	/* // Set the speed to high */
	*self->_ospeedr = 0x5555;

	/* // Set the input type to pull-up */
	*self->_pupdr = 0x0066;
}

/**
 *  Get the key that is currently pressed
 *
 * @param self Pointer to keypad (self)
 * @return The first found key that is being pressed. If no key is found then
 * KEYPAD_NULL_KEY is returned.
 */
char keypad_read(Keypad *self) {
	*self->_odr = 0;

	for (uint8_t i = 0; i < 4; i++) {
		*self->_odr = 0x10 << i;

		for (uint8_t j = 0; j < 4; j++) {
			if (*self->_idr & (1 << j)) {
				*self->_odr = 0;
				return *self->map[i][j]; // TODO: fix j-offset
			}
		}
	}

	*self->_odr = 0;
	return KEYPAD_NULL_KEY;
}
