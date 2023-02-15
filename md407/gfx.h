#pragma once

#include "types.h"

// Struct for a vertex
typedef struct {
	char x, y;
} Vertex, *PVertex;

#define POINT(x, y) Vertex {x, y}

// Struct for a polygon
typedef struct {
	Vertex** verts;
	size_t count;
} Polygon, *PPolygon;

Polygon* polygon_new(Vertex** verts, size_t count);
