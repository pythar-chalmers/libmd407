#pragma once

#include "mem.h"
#include "types.h"

typedef struct {
	// Port mode Register
	DT_32(moder);

	// Output TYPE Register
	DT_16_R(otyper);

	// Output SPEED Register
	DT_32(ospeedr);

	// Pull-up/Pull-down Register
	DT_32(pupdr);

	// Input data Register
	DT_16_R(idr);

	// Output data Register
	DT_16_R(odr);

	// Bit set/reset Register
	uint32_t bsrr;

	// Configuration Lock Register
	uint32_t lckr;

	// Alternate function low Register
	uint32_t afrl;

	// Alternate function high Register
	uint32_t afrh;

} GPIO, *PGPIO;

#define GPIO_A ((PGPIO) 0x40020000)
#define GPIO_B ((PGPIO) 0x40020400)
#define GPIO_C ((PGPIO) 0x40020800)
#define GPIO_D ((PGPIO) 0x40020C00)
#define GPIO_E ((PGPIO) 0x40021000)
