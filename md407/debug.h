#pragma once

#include "types.h"

#define _USART_BASE 0x40011000
#define USART(n)    ((PUSART) _USART_BASE + 0x1400 * n)

void printc(char *s);
void print_usart(char *s, unsigned char id);

typedef volatile struct {
	uint16_t sr;
	uint16_t Unused0;
	uint16_t dr;
	uint16_t Unused1;
	uint16_t brr;
	uint16_t Unused2;
	uint16_t cr1;
	uint16_t Unused3;
	uint16_t cr2;
	uint16_t Unused4;
	uint16_t cr3;
	uint16_t Unused5;
	uint16_t gtpr;
} USART, *PUSART;

static void print_char(char c, unsigned char id) {
	while ((USART(id)->sr & 0x80) == 0)
		;
	USART(id)->dr = (uint16_t) c;
	if (c == '\n')
		print_char('\r', id);
}

/* IMPLEMENTATION */

void print_usart(char *s, unsigned char id) {
	while (*s)
		print_char(*s++, id);
}

void printc(char *s) {
	print_usart(s, 0);
}
