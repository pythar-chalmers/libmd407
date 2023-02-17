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

// Function to create a polygon from an array of verts

// Struct for a rectangle
