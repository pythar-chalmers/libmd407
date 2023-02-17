#pragma once

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
