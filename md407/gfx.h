#pragma once

#include "types.h"

// Struct for a vertex
typedef struct {
	char x, y;
} Vertex;

#define POINT(x, y)                                                          \
	Vertex { x, y }

// Struct for a polygon
typedef struct {
	Vertex **verts;
	size_t count;
} Polygon;

Polygon *polygon_new(Vertex **verts, size_t count);

// Struct for a line
typedef struct {
	Vertex *vert1;
	Vertex *vert2;
} Line;

float gfx_line_length(Line *line);
