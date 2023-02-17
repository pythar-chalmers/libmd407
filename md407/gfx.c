#include "gfx.h"
#include "display.h"
#include "math.h"

// Vertex functions
void _gfx_point_render(Vertex *self) {
	display_set_pixel(self->x, self->y, true);
}

// Line functions
float gfx_line_length(Line *self) {
	float dx, dy;

	dx = (float) (self->vert2.x - self->vert1.x);
	dy = (float) (self->vert2.y - self->vert1.y);

	// TOneverDO: replace this with a better sqrt alg
	float invsqr = f_invsqrt(dx * dx + dy * dy);

	return 1 / invsqr;
}

void _gfx_line_vertical_render(Line *self, Point position, int16_t dy) {
	for (int16_t y = 0; y <= ABS(dy); y++)
		display_set_pixel(self->vert1.x + position.x,
		                  self->vert1.y + position.y + SIGNEXT(y, dy), true);
}

void gfx_line_render(Line *self, Point position) {
	int16_t dx, dy;
	dx = self->vert2.x - self->vert1.x;
	dy = self->vert2.y - self->vert1.y;

	if (dx == 0)
		return _gfx_line_vertical_render(self, position, dy);

	int16_t D = 2 * dy - dx;

	int16_t y = self->vert1.y + position.y;
	for (int16_t x = 0; x <= ABS(dx); x++) {
		display_set_pixel(self->vert1.x + position.x + SIGNEXT(x, dx), y, true);

		if (D > 0) {
			y += SIGNEXT(1, dy);
			D -= SIGNEXT(2 * dx, dx);
		}

		D += 2 * dy;
	}
}

// Polygon functions
void gfx_polygon_render(Polygon *self, Point position) {
	Line line_buf;

	// Draw each line from i -> i+1
	for (int i = 0; i < self->count - 1; i++) {
		line_buf = LINE(self->verts[i], self->verts[i + 1]);
		gfx_line_render(&line_buf, position);
	}

	// Draw the line from the last vertex to the first
	line_buf = LINE(self->verts[self->count - 1], self->verts[0]);
	gfx_line_render(&line_buf, position);
}

// Sprite functions
