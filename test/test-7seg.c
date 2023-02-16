#include "../md407/7seg.h"
#include "../md407/gpio.h"
#include "../md407/time.h"

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

int main(void) {

	SEVENSEG seg;
	sevenseg_connect(&seg, GPIO_D);

	uint8_t chs[] = {'0', '1', '2', '3', '4', '5', '6', '7',
	                 '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	size_t len = sizeof(chs) / sizeof(uint8_t);
	uint8_t i  = 0;

	while (true) {
		sevenseg_write(&seg, chs[i]);
		delay_milli(800);
		i++;
		i %= len;
	}

	return 0;
}
