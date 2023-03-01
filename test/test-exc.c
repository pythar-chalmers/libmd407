#include "../md407/exti.h"
#include "../md407/syscfg.h"

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

int main(void) {
	// These are just to test. Doesn't actually do anything.
	EXTI->imr         = 0b1010100;
	SYSCFG->exticr2_0 = 0xE;

	return 0;
}
