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

// TODO: Create macros to fix this mess
typedef struct {
	uint16_t moder;
	uint16_t moder_reserved;

	uint8_t otyper;
	uint8_t otyper_reserved;

	uint16_t ospeedr;
	uint16_t ospeedr_reserved;

	uint16_t pupdr;
	uint16_t pupdr_reserved;

	uint8_t idr;
	uint8_t idr_reserved;

	uint8_t odr;
	uint8_t odr_reserved;

	uint32_t bsrr;
	uint32_t lckr;
	uint32_t afrl;
	uint32_t afrh;
} *PGPIO_PORT_1;
typedef struct {
	uint16_t moder_reserved;
	uint16_t moder;

	uint8_t otyper_reserved;
	uint8_t otyper;

	uint16_t ospeedr_reserved;
	uint16_t ospeedr;

	uint16_t pupdr_reserved;
	uint16_t pupdr;

	uint8_t idr_reserved;
	uint8_t idr;

	uint8_t odr_reserved;
	uint8_t odr;

	uint32_t bsrr;
	uint32_t lckr;
	uint32_t afrl;
	uint32_t afrh;
} *PGPIO_PORT_2;

// Define the low ports
#define PORT_A_1 ((PGPIO_PORT_1) 0x40020000)
#define PORT_B_1 ((PGPIO_PORT_1) 0x40020400)
#define PORT_C_1 ((PGPIO_PORT_1) 0x40020800)
#define PORT_D_1 ((PGPIO_PORT_1) 0x40020C00)
#define PORT_E_1 ((PGPIO_PORT_1) 0x40021000)

// Define the high ports
#define PORT_A_2 ((PGPIO_PORT_2) 0x40020000)
#define PORT_B_2 ((PGPIO_PORT_2) 0x40020400)
#define PORT_C_2 ((PGPIO_PORT_2) 0x40020800)
#define PORT_D_2 ((PGPIO_PORT_2) 0x40020C00)
#define PORT_E_2 ((PGPIO_PORT_2) 0x40021000)
