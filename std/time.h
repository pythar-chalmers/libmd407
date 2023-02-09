#pragma once
#include "types.h"

typedef struct {
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
void delay_micro(uint32_t us);
void delay_milli(uint32_t ms);
