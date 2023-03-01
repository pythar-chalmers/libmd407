#pragma once

#include "types.h"

/*
// PS register control
__attribute__((naked)) uint32_t _get_psr_reg() {
	__asm__ volatile("MRS R0, PSR\n");
	__asm__ volatile("BX LR\n");
}

__attribute__((naked)) void _set_psr_reg(uint32_t apsr) {
	__asm__ volatile("MSR PSR_nvzcq\n");
	__asm__ volatile("BX LR\n");
}

// Control register control
__attribute__((naked)) uint32_t _get_ctrl_reg() {
	__asm__ volatile("MRS R0, CONTROL\n");
	__asm__ volatile("BX LR\n");
}

__attribute__((naked)) void _set_ctrl_reg(uint32_t x) {
	__asm__ volatile("MSR CONTROL, R0\n");
	__asm__ volatile("BX LR\n");
}

// Enable/disable interrupts
__attribute__((naked)) void _int_enable() {
	__asm__ volatile("CPSIE I\n");
	__asm__ volatile("BX LR\n");
}
__attribute__((naked)) void _int_disable() {
	__asm__ volatile("CPSID I\n");
	__asm__ volatile("BX LR\n");
}
*/

#define EXCEPTION_ASSIGN(offset, func)                                       \
	*((void (**)(void))(0x2001C000 + offset)) = &func
