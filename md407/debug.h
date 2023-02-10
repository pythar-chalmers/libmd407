#pragma once

#define _USART_BASE 0x40011000
#define USART(n)    ((PUSART) _USART_BASE + 0x1400 * n)

void printc(char* s);
void print_usart(char* s, unsigned char id);
