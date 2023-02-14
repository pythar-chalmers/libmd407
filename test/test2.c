#include "../md407/ascii.h"
#include "../md407/gpio.h"

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

int main(void) {
	char* text = "hej lol\n\rkekw";

	ASCII display;
	ascii_connect(&display, GPIO_E);
	ascii_puts(&display, 0, 0, text);

	return 0;
}
