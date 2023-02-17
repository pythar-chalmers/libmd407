__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}

#include "../md407/display.h"
#include "../md407/gfx.h"
#include "../md407/time.h"

int main() {
	display_connect();

	// Create a line
	Line line = LINE(POINT(0, 0), POINT(40, 40));

	// Create a polygon
	Vertex poly_verts[] = {
	    POINT(0, 0),
	    POINT(10, 0),
	    POINT(10, 10),
	    POINT(0, 10),
	};

	Polygon poly = POLYGON(poly_verts, 4);

	// Create a rectangle
	Rectangle rect = RECTANGLE(20, 10);

	while(true) {
		// Render the line
		display_clear();
		line.pos = POINT(20, 0);
		line.render(&line);

		// Render the polygon
		delay_milli(2000);

		display_clear();
		poly.pos = POINT(20, 40);
		poly.render(&poly);

		// Render the rectangle
		delay_milli(2000);

		display_clear();
		rect.pos = POINT(80, 40);
		rect.render(&rect);

		delay_milli(2000);
	}

	return 0;
}
