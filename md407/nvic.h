#pragma once

#include "types.h"

#define _NVIC_RNG_THING(name)                                                \
	struct name {                                                            \
		uint32_t name##_0;                                                   \
		uint32_t name##_1;                                                   \
		unsigned name##_2        : 18;                                       \
		unsigned name##_reserved : 14;                                       \
	}

#define _NVIC_IPR(n)                                                         \
	struct ipr_##n {                                                         \
		uint8_t ip0;                                                         \
		uint8_t ip1;                                                         \
		uint8_t ip2;                                                         \
		uint8_t ip3;                                                         \
	}

typedef struct {
	_NVIC_RNG_THING(iser);
	_NVIC_RNG_THING(cer);
	_NVIC_RNG_THING(ispr);
	_NVIC_RNG_THING(icpr);
	_NVIC_RNG_THING(iabr);
	// Interrupt priority registers
	_NVIC_IPR(0);
	_NVIC_IPR(1);
	_NVIC_IPR(2);
	_NVIC_IPR(3);
	_NVIC_IPR(4);
	_NVIC_IPR(5);
	_NVIC_IPR(6);
	_NVIC_IPR(7);
	_NVIC_IPR(8);
	_NVIC_IPR(9);
	_NVIC_IPR(10);
	_NVIC_IPR(11);
	_NVIC_IPR(12);
	_NVIC_IPR(13);
	_NVIC_IPR(14);
	_NVIC_IPR(15);
	_NVIC_IPR(16);
	_NVIC_IPR(17);
	_NVIC_IPR(18);
	_NVIC_IPR(19);
	struct ipr_20 {
		uint8_t ip0;
		uint8_t ip1;
	};
} NVIC;
