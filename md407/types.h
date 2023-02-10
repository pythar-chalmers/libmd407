#pragma once

// Boolean
typedef unsigned char boolean;
#define true  ((boolean) 1)
#define false ((boolean) 0)

// Integers
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long int64_t;

// Unsigned integers
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

// String
typedef char *string;

// Size
typedef int size_t;

// Byte
typedef unsigned char byte_t;

// Null pointer
#define NULLPTR ((void *) 0)
#define NULL    0
