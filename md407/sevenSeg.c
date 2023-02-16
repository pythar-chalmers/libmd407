#include "sevenSeg.h"

void seven_seg_init(PSEVENSEG pSeg, PGPIO port) {

	pSeg->gpio = port;

	// pin 7-0 outport
	// pin 15-8 inport
	port->moder = 0x55005555;

	// GPIO OT
	port->otyper = 0x00FF;

	// GPIO PUPDR
	port->pupdr_high = 0x00AA;
}

int charToInt(uint8_t c) 
{
	if (isalpha(c)) {
		return c - 'A' + 10;
	}
	return (c - '0');
}
void out7seg(uint8_t c, PGPIO port) 
{
	int index = charToInt(c);
    if (index >= 16) {
    	port->odr_low = 0x0;
    } else {
    	port->odr_low = seg_codes[index];
	}
}

