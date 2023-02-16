#pragma once

#include "gpio.h"
#include "types.h"

// Initialize the display
void _display_init();
// Set a pixel at x, y
void _display_px_set(int x, int y);
// Clear a pixel at x, y
void _display_px_clear(int x, int y);

// Connect the display
void display_connect();
// Clear the screen
void display_clear();
// Set pixel as on/off
void display_set_pixel(int x, int y, boolean on);
