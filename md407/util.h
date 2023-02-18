#pragma once

// Function to swap two chars
void c_swap(char *a, char *b) {
	char tmp = *a;
	*a       = *b;
	*b       = tmp;
}
