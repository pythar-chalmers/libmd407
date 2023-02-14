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
