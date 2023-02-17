#include "display.h"

// Functions defined in debug
__attribute__((naked))
void _display_init() {
	__asm__ volatile (".HWORD 0xDFF0\n");
	__asm__ volatile ("BX LR\n");
}

__attribute__((naked))
void display_clear() {
	__asm__ volatile (".HWORD 0xDFF1\n");
	__asm__ volatile ("BX LR\n");
}

__attribute__((naked))
void _display_px_set(int x, int y) {
	__asm__ volatile (".HWORD 0xDFF2\n");
	__asm__ volatile ("BX LR\n");
}

__attribute__((naked))
void _display_px_clear(int x, int y) {
	__asm__ volatile (".HWORD 0xDFF3\n");
	__asm__ volatile ("BX LR\n");
}

// User functions
void display_connect() {
	_display_init();
	display_clear();
}

void display_set_pixel(int x, int y, boolean on) {
	// x and y needs to be 1 <= x, y <= 128
	// Because some idiot decided that it should start on one?!
	x++;
	y++;
	if(on)
		_display_px_set(x, y);
	else
		_display_px_clear(x, y);
}
