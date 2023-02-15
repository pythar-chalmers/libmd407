#pragma once
#include "types.h"

// Constants
#define PI 3.14159
#define E  2.718281

// Trig
#define DEG_TO_RAD(deg) (deg * 0.0174532)
#define RAD_TO_DEG(rad) (rad * 57.295779)

// Generic artihmetic functions
float f_invsqrt(float);
uint32_t idiv(uint32_t, uint32_t);
uint32_t mod(uint32_t, uint32_t);
uint32_t power(uint32_t, uint32_t);
float sqrt(float);
uint32_t isqrt(uint32_t);

// LinAlg
typedef struct {
	int x;
	int y;
} Vector32;
