__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

#include <md407/gpio.h>
#include <md407/time.h>
#include <md407/debug.h>

int main() {
    // Set pins 7-15 as outputs.
    GPIO_E->moder_high = 0x5555;

    // Delay for 1 second.
    delay_milli(1000);

    // Write 'E' to the output.
    GPIO_E->odr_high = 'E';

    // Print a text to USART1 for debug.
    printc("Hello World!\n");

	return 0;
}
