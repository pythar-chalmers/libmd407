#pragma once
#include "mem.h"
#include "types.h"

typedef volatile struct {
	union {
		uint32_t control;
		struct {
			unsigned enable     : 1;
			unsigned interupt   : 1;
			unsigned source     : 1;
			unsigned _reserved  : 13;
			unsigned count      : 1;
			unsigned _reserved2 : 15;
		};
	};
	union {
		uint32_t load_full;
		struct {
			unsigned load           : 24;
			unsigned _reserved_load : 8;
		};
	};
	union {
		uint32_t value_full;
		struct {
			unsigned value           : 24;
			unsigned _reserved_value : 8;
		};
	};
	union {
		uint32_t calib_full;
		struct {
			unsigned tenms           : 24;
			unsigned _reserved_tenms : 6;
			unsigned skew            : 1;
			unsigned noref           : 1;
		};
	};
} SYSTICK, *PSYSTICK;

#define STK ((PSYSTICK) 0xE000E010)

void delay_250ns(void);
void delay_nano(uint32_t ns);
void delay_micro(uint32_t us);
void delay_milli(uint32_t ms);

/* IMPLEMENTATION */

void delay_250ns(void) {
	STK->control = 0;
	STK->load    = (168 / 4) - 1;
	STK->value   = 0;
	STK->control = 5;
	while (STK->count == 0)
		;
	STK->control = 0;
}

void delay_nano(uint32_t ns) {
	STK->control = 0;
	STK->load    = 6 * ns; // 5.9 ~ 6
	STK->value   = 0;
	STK->control = 5;
	while (STK->count == 0)
		;
	STK->control = 0;
}

void delay_micro(uint32_t delay) {
	while (delay > 0) {
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay--;
	}
}

void delay_milli(uint32_t delay) {
	while (delay > 0) {
#ifndef SIMULATOR
		delay_micro(1000);
#else
		delay_micro(1);
#endif
		delay--;
	}
}
