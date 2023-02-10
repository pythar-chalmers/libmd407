#include "time.h"
#include "mem.h"
#include "types.h"

void delay_250ns(void) {
	STK->control = 0;
	STK->load    = (168 / 4) - 1;
	STK->value   = 0;
	STK->control = 5;
	while (BIT_CHECK(uint32_t, &STK->control, 16))
		;
	STK->control = 0;
}
void delay_micro(uint32_t delay) {
	while (delay > 0) {
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay--;
	}
}
void delay_milli(uint32_t delay) {
	while (delay > 0) {
		delay_micro(1000);
		delay--;
	}
}
