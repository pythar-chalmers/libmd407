#pragma once

#define _USART_BASE 0x40011000
#define USART(n)    ((PUSART) _USART_BASE + 0x1400 * n)

void printc(char *s);
void print_usart(char *s, unsigned char id);

typedef struct {
	volatile unsigned short sr;
	volatile unsigned short Unused0;
	volatile unsigned short dr;
	volatile unsigned short Unused1;
	volatile unsigned short brr;
	volatile unsigned short Unused2;
	volatile unsigned short cr1;
	volatile unsigned short Unused3;
	volatile unsigned short cr2;
	volatile unsigned short Unused4;
	volatile unsigned short cr3;
	volatile unsigned short Unused5;
	volatile unsigned short gtpr;
} USART, *PUSART;

static void print_char(char c, unsigned char id) {
	while ((USART(id)->sr & 0x80) == 0)
		;
	USART(id)->dr = (unsigned short) c;
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
