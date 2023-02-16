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
typedef struct {
	Vertex vert1;
	Vertex vert2;
} Line;

#define LINE(v1, v2)                                                         \
	(Line) { .vert1 = v1, .vert2 = v2 }

// Function to get a lines length
float gfx_line_length(Line *self);
// Function to render vertical line (helper function)
void _gfx_line_vertical_render(Line *self, Point position, int16_t dy);
// Function to render a line
void gfx_line_render(Line *self, Point position);

// Struct for a polygon
typedef struct {
	Vertex *verts;
	size_t count;
} Polygon;

// Function to create a polygon from an array of verts
#define POLYGON(vs, cc)                                                      \
	(Polygon) { .verts = vs, .count = cc }

// Function to render a polygon
void gfx_polygon_render(Polygon *self, Point position);
