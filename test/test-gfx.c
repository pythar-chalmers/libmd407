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
	Line line2 = LINE(POINT(0, 0), POINT(0, 40));

	// sak
	display_set_pixel(0, 0, true);
	display_set_pixel(40, 40, true);

	display_set_pixel(20, 0, true);
	display_set_pixel(60, 40, true);

	// Render the lines
	gfx_line_render(&line, POINT(0, 0));
	gfx_line_render(&line2, POINT(50, 0));

	// Render the line but with a offset
	gfx_line_render(&line, POINT(20, 0));

	// Line tests
	/* display_set_pixel(100, 5, true); */
	/* Line linex = LINE(POINT(50, 0), POINT(0, 0)); */
	/* Line liney = LINE(POINT(0, 50), POINT(0, 0)); */
	/* gfx_line_render(&linex, POINT(60, 5)); */
	/* gfx_line_render(&liney, POINT(60, 5)); */

	// Create a polygon
	Vertex poly_verts[] = {
	    POINT(0, 0),
	    POINT(10, 0),
	    POINT(10, 10),
	    POINT(0, 10),
	};

	Polygon poly = POLYGON(poly_verts, 4);

	// Render the polygon
	delay_milli(1000);

	display_clear();
	gfx_polygon_render(&poly, POINT(40, 40));

	return 0;
}
