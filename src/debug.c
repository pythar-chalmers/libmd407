typedef struct USART {
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
} USART;

#define USART1  ((USART *) 0x40011000) 

static void print_char( char c ) {
	// write character to usart1
	while (( USART1->sr & 0x80)==0);
	USART1->dr = (unsigned short) c;
	if( c == '\n') {
		print_char('\r');
	}
}

void print(char* s){
	while (*s != '\0') {
		print_char(*(s++));
	}
}
