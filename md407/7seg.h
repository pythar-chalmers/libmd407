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
