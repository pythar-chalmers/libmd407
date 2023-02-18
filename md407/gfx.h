#pragma once

#include "display.h"
#include "math.h"
#include "types.h"
#include "util.h"

// Struct for a vertex
typedef struct {
	char x, y;
} Vertex, Point;

#define POINT(xx, yy)                                                        \
	(Point) { .x = xx, .y = yy }

// Struct for a line
typedef struct Line {
	Vertex vert1;
	Vertex vert2;
	Point pos;

	void (*render)(struct Line *self);
} Line;

#define LINE(v1, v2)                                                         \
	(Line) {                                                                 \
		.vert1 = v1, .vert2 = v2, .pos = POINT(0, 0),                        \
		.render = &_gfx_line_render                                          \
	}

// Function to render a line
void _gfx_line_render(Line *self);

// Struct for a polygon
typedef struct Polygon {
	Vertex *verts;
	size_t count;
	Point pos;

	void (*render)(struct Polygon *self);
} Polygon;

#define POLYGON(vs, cc)                                                      \
	(Polygon) {                                                              \
		.verts = vs, .count = cc, .pos = POINT(0, 0),                        \
		.render = &_gfx_polygon_render                                       \
	}

// Function to render a polygon
void _gfx_polygon_render(Polygon *self);

// Struct for a rectangle
typedef struct Rectangle {
	uint8_t width, height;
	Point pos;

	void (*render)(struct Rectangle *self);
} Rectangle;

#define RECTANGLE(w, h)                                                      \
	(Rectangle) {                                                            \
		.width = w, .height = h, .pos = POINT(0, 0),                         \
		.render = &_gfx_rectangle_render                                     \
	}

#define SQUARE(w) RECTANGLE(w, w)

// Function to render the rectangle
void _gfx_rectangle_render(Rectangle *self);

// Struct for a Sprite
#define _GFX_SPRITE_MAX_PIXELS 30
#define PIXEL_ARRAY(...)       __VA_ARGS__
typedef struct Sprite {
	uint8_t width;
	uint8_t height;
	Point pos;

	void (*render)(struct Sprite *self, boolean on);

	uint8_t count;
	Point pixels[_GFX_SPRITE_MAX_PIXELS];
} Sprite;

#define SPRITE(nm, w, h, pxs)                                                \
	(Sprite) {                                                               \
		.width = w, .height = h, .pos = POINT(0, 0), .count = nm,            \
		.render = &_gfx_sprite_render, .pixels = pxs                         \
	}

// Function to render the sprite
void _gfx_sprite_render(Sprite *self, boolean on);

/* IMPLEMENTATION */

// Line functions

void _gfx_line_render(Line *self) {
	// Lazy
	char x0 = self->vert1.x + self->pos.x;
	char y0 = self->vert1.y + self->pos.y;

	char x1 = self->vert2.x + self->pos.x;
	char y1 = self->vert2.y + self->pos.y;

	boolean steep = abs(y1 - y0) > abs(x1 - x0);

	if (steep) {
		c_swap(&x0, &y0);
		c_swap(&x1, &y1);
	}

	if (x0 > x1) {
		c_swap(&x0, &x1);
		c_swap(&y0, &y1);
	}

	int delta_x = x1 - x0;
	int delta_y = abs(y1 - y0);

	int error = 0;
	int y     = y0;
	int ystep = y0 < y1 ? 1 : -1;

	for (int x = x0; x <= x1; x++) {
		if (steep)
			display_set_pixel(y, x, true);
		else
			display_set_pixel(x, y, true);

		error += delta_y;
		if ((error << 1) >= delta_x) {
			y += ystep;
			error -= delta_x;
		}
	}
}

// Polygon functions
void _gfx_polygon_render(Polygon *self) {
	Line line_buf;

	// Draw each line from i -> i+1
	for (int i = 0; i < self->count - 1; i++) {
		line_buf     = LINE(self->verts[i], self->verts[i + 1]);
		line_buf.pos = self->pos;
		_gfx_line_render(&line_buf);
	}

	// Draw the line from the last vertex to the first
	line_buf     = LINE(self->verts[self->count - 1], self->verts[0]);
	line_buf.pos = self->pos;
	_gfx_line_render(&line_buf);
}

// Rectangle functions
void _gfx_rectangle_render(Rectangle *self) {
	// Render the sides
	for (uint8_t dy = 0; dy <= self->height; dy++) {
		display_set_pixel(self->pos.x, self->pos.y + dy, true);
		display_set_pixel(self->pos.x + self->width, self->pos.y + dy, true);
	}

	// Render the bottom and top lines
	for (uint8_t dx = 0; dx <= self->width; dx++) {
		display_set_pixel(self->pos.x + dx, self->pos.y, true);
		display_set_pixel(self->pos.x + dx, self->pos.y + self->height, true);
	}
}

// Sprite functions
void _gfx_sprite_render(Sprite *self, boolean on) {
	Point pxBuf;
	for (int i = 0; i < self->count; i++) {
		pxBuf = self->pixels[i];
		display_set_pixel(pxBuf.x + self->pos.x, pxBuf.y + self->pos.y, on);
	}
}
