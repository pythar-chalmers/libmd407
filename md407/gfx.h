#pragma once

#include "display.h"
#include "math.h"
#include "types.h"

// Struct for a vertex
typedef struct {
	char x, y;
} Vertex, Point;

// Function to render a point/vertex
void _gfx_point_render(Vertex *self);

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

// Function to get a lines length
float gfx_line_length(Line *self);
// Function to render vertical line (helper function)
void _gfx_line_vertical_render(Line *self, int16_t dy);
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
typedef struct Sprite {
	uint8_t width, height;
	uint8_t **pixelmap;
	Point pos;

	void (*render)(struct Sprite *self);
} Sprite;

#define SPRITE(w, h, pm)                                                     \
	(Sprite) {                                                               \
		.width = w, .height = h, .pos = POINT(0, 0),                         \
		.render = &_gfx_sprite_render, .pixelmap = pm                        \
	}

// Function to render the sprite
void _gfx_sprite_render(Sprite *self);

/* IMPLEMENTATION */

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

void _gfx_line_vertical_render(Line *self, int16_t dy) {
	for (int16_t y = 0; y <= ABS(dy); y++)
		display_set_pixel(self->vert1.x + self->pos.x,
		                  self->vert1.y + self->pos.y + SIGNEXT(y, dy), true);
}

void _gfx_line_render(Line *self) {
	int16_t dx, dy;
	dx = self->vert2.x - self->vert1.x;
	dy = self->vert2.y - self->vert1.y;

	if (dx == 0) {
		_gfx_line_vertical_render(self, dy);
	} else {
		int16_t D = 2 * dy - dx;

		int16_t y = self->vert1.y + self->pos.y;
		for (int16_t x = 0; x <= ABS(dx); x++) {
			display_set_pixel(self->vert1.x + self->pos.x + SIGNEXT(x, dx), y,
			                  true);

			if (D > 0) {
				y += SIGNEXT(1, dy);
				D -= SIGNEXT(2 * dx, dx);
			}

			D += 2 * dy;
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
void _gfx_sprite_render(Sprite *self) {
	for (uint8_t w = 0; w < self->width; w++)
		for (uint8_t h = 0; h < self->height; h++)
			display_set_pixel(self->pos.x + w, self->pos.y + h,
			                  self->pixelmap[h][w]);
}
