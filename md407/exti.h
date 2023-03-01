#pragma once

#include "mem.h"
#include "types.h"

#define _EXTI_REG(r)                                                         \
	union {                                                                  \
		uint32_t _##r;                                                       \
		unsigned r : 23;                                                     \
	}

typedef volatile struct {
	_EXTI_REG(imr);
	_EXTI_REG(emr);
	_EXTI_REG(rtsr);
	_EXTI_REG(ftsr);
	_EXTI_REG(swier);
	_EXTI_REG(pr);
} *PEXTI;

#define EXTI ((PEXTI) 0x40013C00)
