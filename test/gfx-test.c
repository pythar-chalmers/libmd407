__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

/* Keypad test */

#include "../md407/display.h"

int main() {
	_display_init();
	_display_clear();

	for (int i = 0; i < 128; i++) {
		display_set_pixel(i, 0, true);
	}

	return 0;
}
