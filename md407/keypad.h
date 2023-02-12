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
typedef struct {
	PGPIO port;
	boolean upper;
} Keypad;

// Keypad driver for the MD407
void keypad_init(Keypad *keypad, PGPIO port, boolean upper);
char keypad_read_char(Keypad *keypad);

// TODO
// void keypad_set_callback(void (*callback)(uint8_t));
