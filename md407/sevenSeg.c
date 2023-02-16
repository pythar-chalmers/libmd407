
#include <gpio.h>

typedef struct {
	unsigned char SegCodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07 ,0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	PGPIO gpio;
} SEVENSEG, *PSEVENSEG;

int charToInt(char c) {
	if (isalpha(c)) {
		return c - 'a' + 10;
	}
	return (c - '0');
}
void out7seg(unsigned char c) {
    if (c >= 16) {
           *GPIO_D_LOW_ODR = 0x00;
    } else {
    	int index = charToInt(c);
		*GPIO_D_LOW_ODR = SegCodes[index];
	}
}
