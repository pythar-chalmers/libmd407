__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

#include <md407/debug.h>
#include <md407/gpio.h>
#include <md407/time.h>

int main() {
	// Set pins 8-15 as outputs.
	GPIO_D->moder_high = 0x5555; // 0101 0101 0101 0101

	// Delay for 1 second.

#ifndef SIMULATOR
	delay_milli(1000);
#else
	delay_milli(1); // because the sim is very slow
#endif

	// Write to the output.
	GPIO_D->odr_high = 0xFF;

	// Print a text to USART1 for debug.
	printc("Hello World!\n");

	return 0;
}
