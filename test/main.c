#include "../md407/math.h"
#include "../md407/debug.h"
#include "../md407/time.h"
#include "../md407/types.h"

int main(void) {
	uint32_t test = 123456;
	test          = idiv(test, 100);

	printc("Hello ");
	delay_milli(1000);
	printc("World!");

	return 0;
}
