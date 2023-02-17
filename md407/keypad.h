#include "gpio.h"
#include "types.h"
/*
    Keypad driver for the MD407
    Key mapping:
    1 2 3 A
    4 5 6 B
    7 8 9 C
    * 0 # D
    The 4 rows are set to output and the 4 columns are set to input.
    The columns are set to pull-up and the rows are set to high speed.
    When a key is pressed, the corresponding column will be pulled down.

    The keypad is connected to GPIOE or GPIOD ( upper or lower )
*/

#define _KEYPAD_ASSIGN_REGISTERS(NAME, TYPE, I)                              \
	self->_##NAME =                                                          \
	    ((TYPE *) ((char *) &self->_port->NAME + sizeof(TYPE) * (I)))

#define KEYPAD_NULL_KEY 0

// Defualt key mapping
static char KEYPAD_MAP[4][4] = {{'1', '2', '3', 'A'},
                                {'4', '5', '6', 'B'},
                                {'7', '8', '9', 'C'},
                                {'*', '0', '#', 'D'}};

typedef volatile struct {
	PGPIO _port;

	// Port offsets
	uint16_t *_moder;
	uint8_t *_otyper;
	uint16_t *_ospeedr;
	uint16_t *_pupdr;
	uint8_t *_idr;
	uint8_t *_odr;

	char (*map)[4][4]; // Keymap
} Keypad;

void keypad_connect(Keypad *self, PGPIO port, boolean high_port);
char keypad_read(Keypad *self);

// TODO
// void keypad_set_callback(void (*callback)(uint8_t));

/* IMPLEMENTATION */

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

	// Assign each register pins to the keypad
	_KEYPAD_ASSIGN_REGISTERS(moder, uint16_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(otyper, uint8_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(ospeedr, uint16_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(pupdr, uint16_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(idr, uint8_t, high_port);
	_KEYPAD_ASSIGN_REGISTERS(odr, uint8_t, high_port);

	// Configure the pins
	// Set the output pins to high and the input pins to low
	*self->_moder = 0x5500;

	// Set the output type to push-pull
	*self->_otyper = 0x0000;

	// Set the speed to high
	*self->_ospeedr = 0x5555;

	// Set the input type to pull-up
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
				return (*self->map)[i][j]; // TODO: fix j-offset
			}
		}
	}
	*self->_odr = 0;
	return KEYPAD_NULL_KEY;
}
