__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

/* Keypad test */

#include "../md407/keypad.h" // NOTE: Should be "#include <md407/keypad.h>" in actual source files
#include "../md407/debug.h"

int main() {
	Keypad kp;

	// Connect the keypad to GPIO_D (HIGH)
	keypad_connect(&kp, GPIO_D, true);

	char key;
	char* str = " \n";
	while(true) {
		key = keypad_read(&kp);

		if(key) {
			str[0] = key;
			printc(str);
		}
	}

	return 0;
}
