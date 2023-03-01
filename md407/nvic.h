#pragma once

#include "mem.h"
#include "types.h"

#define _NVIC_RNG_THING(name)                                                \
	DT_32(name##_0);                                                         \
	DT_32(name##_1);                                                         \
	union {                                                                  \
		uint32_t _##name##_reserved;                                         \
		unsigned name##_2 : 18;                                              \
	}

typedef volatile struct {
	_NVIC_RNG_THING(iser);
	_NVIC_RNG_THING(icer);
	_NVIC_RNG_THING(ispr);
	_NVIC_RNG_THING(icpr);
	_NVIC_RNG_THING(iabr);

	// Interrupt priority registers
	uint8_t ip0;
	uint8_t ip1;
	uint8_t ip2;
	uint8_t ip3;
	uint8_t ip4;
	uint8_t ip5;
	uint8_t ip6;
	uint8_t ip7;
	uint8_t ip8;
	uint8_t ip9;
	uint8_t ip10;
	uint8_t ip11;
	uint8_t ip12;
	uint8_t ip13;
	uint8_t ip14;
	uint8_t ip15;
	uint8_t ip16;
	uint8_t ip17;
	uint8_t ip18;
	uint8_t ip19;
	uint8_t ip20;
	uint8_t ip21;
	uint8_t ip22;
	uint8_t ip23;
	uint8_t ip24;
	uint8_t ip25;
	uint8_t ip26;
	uint8_t ip27;
	uint8_t ip28;
	uint8_t ip29;
	uint8_t ip30;
	uint8_t ip31;
	uint8_t ip32;
	uint8_t ip33;
	uint8_t ip34;
	uint8_t ip35;
	uint8_t ip36;
	uint8_t ip37;
	uint8_t ip38;
	uint8_t ip39;
	uint8_t ip40;
	uint8_t ip41;
	uint8_t ip42;
	uint8_t ip43;
	uint8_t ip44;
	uint8_t ip45;
	uint8_t ip46;
	uint8_t ip47;
	uint8_t ip48;
	uint8_t ip49;
	uint8_t ip50;
	uint8_t ip51;
	uint8_t ip52;
	uint8_t ip53;
	uint8_t ip54;
	uint8_t ip55;
	uint8_t ip56;
	uint8_t ip57;
	uint8_t ip58;
	uint8_t ip59;
	uint8_t ip60;
	uint8_t ip61;
	uint8_t ip62;
	uint8_t ip63;
	uint8_t ip64;
	uint8_t ip65;
	uint8_t ip66;
	uint8_t ip67;
	uint8_t ip68;
	uint8_t ip69;
	uint8_t ip70;
	uint8_t ip71;
	uint8_t ip72;
	uint8_t ip73;
	uint8_t ip74;
	uint8_t ip75;
	uint8_t ip76;
	uint8_t ip77;
	uint8_t ip78;
	uint8_t ip79;
	uint8_t ip80;
} *PNVIC;

#define NVIC ((PNVIC) 0xE000E100)
