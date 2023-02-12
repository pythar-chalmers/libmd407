#include "keypad.h"

/**
 *  Initialize the keypad driver
 *
 * @param keypad The keypad struct to initialize
 * @param port The GPIO port that the keypad is connected to.
 * @param isHigher If the keypad is connected to the higher 8 pins of the
 * port.
 */
void keypad_init(Keypad *keypad, PGPIO port, boolean isHigher) {
	keypad->port  = port;
	keypad->upper = isHigher;

	uint8_t pin_start = isHigher ? 8 : 0;

	// Set the output pins to high and the input pins to low
	port->moder = 0x5500 << (pin_start * 2);

	// Set the output type to push-pull
	port->otyper = 0x0000 << pin_start;

	// Set the speed to high
	port->ospeedr = 0x5555 << (pin_start * 2);

	// Set the input type to pull-up
	port->pupdr = 0x0066 << (pin_start * 2);
}

/**
 *  Get the key that is currently pressed
 *
 * @param keypad The keypad struct to use
 * @return The key that is currently pressed. If no key is pressed, 0xFF is
 * returned.
 */
char keypad_read_char(Keypad *keypad) {

	char keys[4][4] = {{'1', '2', '3', 'A'},
	                   {'4', '5', '6', 'B'},
	                   {'7', '8', '9', 'C'},
	                   {'*', '0', '#', 'D'}};

	uint8_t pin_start = keypad->upper ? 8 : 0;

	for (uint8_t i = 0; i < 4; i++) {
		keypad->port->odr = 0x0000 << pin_start;
		keypad->port->odr = 0x10 << (i + pin_start);

		for (uint8_t j = 0; j < 4; j++) {
			if (keypad->upper) {
				if (keypad->port->idr_high & 0x1 << j) {
					return keys[i][j];
				}
			} else {
				if (keypad->port->idr_low & 0x1 << j) {
					return keys[i][j];
				}
			}
		}
	}

	return 0xFF;
}
