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

// Defualt key mapping
static char KEYPAD_MAP[4][4] = {{'1', '2', '3', 'A'},
                                {'4', '5', '6', 'B'},
                                {'7', '8', '9', 'C'},
                                {'*', '0', '#', 'D'}};

typedef struct Keypad {
	PGPIO port;
	char *map[4][4];

	void (*connect)(Keypad* self, PGPIO port); // Init
	char (*read)(Keypad* self); // Read from port
} Keypad;

void _Keypad_connect(Keypad* self, PGPIO port);
char _Keypad_read(Keypad* self);

// TODO
// void keypad_set_callback(void (*callback)(uint8_t));
