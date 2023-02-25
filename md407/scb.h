#pragma once

#include "types.h"

// CPUID, information about the CPU
typedef struct cpuid {
	unsigned revision : 4;
	unsigned partno   : 12;
	unsigned constant : 4;
	unsigned variant  : 4;
	uint8_t implementer;
} CPUID;

// Interrupt control and state register (ICSR)
typedef struct icsr {
	unsigned vectactive   : 9;
	unsigned              : 2;
	unsigned ret_to_base  : 1;
	unsigned vectpending  : 7;
	unsigned              : 3;
	unsigned isr_pending  : 1;
	unsigned              : 2;
	unsigned pend_st_clr  : 1;
	unsigned pend_st_set  : 1;
	unsigned pend_sv_clr  : 1;
	unsigned pend_sv_set  : 1;
	unsigned              : 2;
	unsigned nmi_pend_set : 1;
} ICSR;

typedef struct vtor {
	unsigned              : 9;
	unsigned table_offset : 21;
} VTOR;

// Application interrupt and reset control register (AIRCR)
typedef struct aircr {
	unsigned vect_reset    : 1;
	unsigned vect_clr_act  : 1;
	unsigned sys_reset_req : 1;
	unsigned               : 5;
	unsigned prigroup      : 3;
	unsigned               : 4;
	unsigned endianess     : 1;
	uint16_t vectkey;
} AIRCR;

// SCR
typedef struct scr {
	unsigned               : 1;
	unsigned sleep_on_exit : 1;
	unsigned sleep_deep    : 1;
	unsigned               : 1;
	unsigned sev_on_pend   : 1;
} SCR;

// Configuration and control register (CCR)
typedef struct ccr {
	unsigned non_base_thrd_ena : 1;
	unsigned user_setm_pend    : 1;
	unsigned                   : 1;
	unsigned unalign_trp       : 1;
	unsigned div_0_trp         : 1;
	unsigned                   : 3;
	unsigned bfhf_nmign        : 1;
	unsigned stk_align         : 1;
} CCR;

// System handler priority register 1 (SHPR1)
typedef struct shpr1 {
	union {
		uint8_t _mmu_fault;
		struct {
			unsigned : 4;
			unsigned mmu_fault;
		};
	};
	union {
		uint8_t _bus_fault;
		struct {
			unsigned : 4;
			unsigned bus_fault;
		};
	};
	union {
		uint8_t _usage_fault;
		struct {
			unsigned : 4;
			unsigned usage_fault;
		};
	};
} SHPR1;

// System handler priority register 2 (SHPR2)
typedef struct shpr2 {
	unsigned : 24;
	union {
		uint8_t _sv_call;
		struct {
			unsigned : 4;
			unsigned sv_call;
		};
	};
} SHPR2;

// System handler priority register 3 (SHPR3)
typedef struct shpr3 {
	unsigned : 16;
	union {
		uint8_t _pend_sv;
		struct {
			unsigned : 4;
			unsigned pend_sv;
		};
	};
	union {
		uint8_t _systick;
		struct {
			unsigned : 4;
			unsigned systick;
		};
	};
} SHPR3;

// System Control Block (SCB)
// _(name): to get the whole register as a uint32_t
// Otherwise uses the struct for said regsiter type

#define _EXC_REG_UNI(name)                                                   \
	union {                                                                  \
		uint32_t _##name;                                                    \
		struct name name;                                                    \
	}

typedef volatile struct {
	_EXC_REG_UNI(cpuid);
	_EXC_REG_UNI(icsr);
	_EXC_REG_UNI(vtor);
	_EXC_REG_UNI(aircr);
	_EXC_REG_UNI(scr);
	_EXC_REG_UNI(ccr);
	_EXC_REG_UNI(shpr1);
	_EXC_REG_UNI(shpr2);
	_EXC_REG_UNI(shpr3);
	// TODO: make structs for the below params
	uint32_t shprsr;
	uint32_t cfsr;
	uint32_t hfsr;
	uint32_t _reserved;
	uint32_t mmar;
	uint32_t bfar;
	uint32_t afsr;
} *PSCB;

#define SCB ((PSCB) 0xE000ED00)
