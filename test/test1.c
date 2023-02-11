#include <md407/debug.h>
#include <md407/gpio.h>
#include <md407/math.h>
#include <md407/time.h>
#include <md407/types.h>

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

int main(void) {
	uint32_t test = 123456;
	test          = idiv(test, 100);

	printc("Hello ");
	delay_milli(1000);
	printc("World!");

	return 0;
}
