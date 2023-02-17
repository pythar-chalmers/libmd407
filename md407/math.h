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
