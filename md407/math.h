#pragma once
#include "types.h"

// Constants
#define PI 3.14159
#define E  2.718281

// Trig
#define DEG_TO_RAD(deg) (deg * 0.0174532)
#define RAD_TO_DEG(rad) (rad * 57.295779)

// Generic artihmetic functions
#define SIGNEXT(n, dn) (dn < 0 ? -n : n)
#define ABS(n)         SIGNEXT(n, n)

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

/* IMPLEMENTATION */

float f_invsqrt(float number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = *(long *) &y;          // evil floating point bit level hacking
	i  = 0x5f3759df - (i >> 1); // what the fuck?
	y  = *(float *) &i;
	y  = y * (threehalfs - (x2 * y * y)); // 1st iteration
	//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can
	// be removed

	return y;
}

// Integer division
uint32_t idiv(uint32_t a, uint32_t b) {
	uint32_t i = 0;
	while (a >= b) {
		a -= b;
		i++;
	}
	return i;
}

// Modulus
uint32_t mod(uint32_t a, uint32_t b) {
	while (a >= b) {
		a -= b;
	}
	return a;
}

// Power, a^b
uint32_t power(uint32_t a, uint32_t b) {
	uint32_t i = 1;
	while (b > 0) {
		i *= a;
		b--;
	}
	return i;
}

float sqrt(float a) {
	if (a < 0) // too complex for me
		return NULL;

	// this is dumb
	float i = 0.0f;
	while (i * i <= a) {
		i += 0.01f;
	}
	return i - 0.01f;
}
