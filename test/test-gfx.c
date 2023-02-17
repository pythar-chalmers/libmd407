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
	Line line  = LINE(POINT(0, 0), POINT(40, 40));

	// Render the line but with a offset
	line.pos = POINT(20, 0);
	line.render(&line);

	// Create a polygon
	Vertex poly_verts[] = {
	    POINT(0, 0),
	    POINT(10, 0),
	    POINT(10, 10),
	    POINT(0, 10),
	};

	Polygon poly = POLYGON(poly_verts, 4);

	// Render the polygon
	delay_milli(4000);

	display_clear();
	poly.pos = POINT(20, 40);
	poly.render(&poly);

	return 0;
}
