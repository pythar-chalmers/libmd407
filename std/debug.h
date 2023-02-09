#pragma once

#define _USART_BASE 0x40011000
#define USART(n)    ((PUSART) _USART_BASE + 0x1400 * n)

void console_print(char* s);
void console_print_usart(char* s, unsigned char id);
