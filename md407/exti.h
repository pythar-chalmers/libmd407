#pragma once

#include "mem.h"
#include "types.h"

#define _EXTI_REG(r)                                                         \
	union {                                                                  \
		uint32_t _##r;                                                       \
		unsigned r : 23;                                                     \
	}

typedef struct {
	_EXTI_REG(imr);
	_EXTI_REG(emr);
	_EXTI_REG(rtsr);
	_EXTI_REG(ftsr);
	_EXTI_REG(swier);
	_EXTI_REG(pr);
} *PEXTI;

#define EXTI ((PEXTI) 0x40013C00)

#define EXTI_BIT_SET(r, n)   BIT_SET(unsigned : 23, &EXTI->r, (1 << n))
#define EXTI_BIT_CLEAR(r, n) BIT_CLEAR(unsigned : 23, &EXTI->r, (1 << n))

void _test() {
	EXTI_BIT_SET(imr, 2);
}
