#include <xc.h>
#include <stdio.h>
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#ifndef _XTAL_FREQ
	#define _XTAL_FREQ      20000000
#endif

// NOTE: To use the macros below, YOU must have previously defined _XTAL_FREQ
#define ppl_delay_sg(x) ppl_delay((uint32_t)((x)*(_XTAL_FREQ/4.0)))
#define ppl_delay_ms(x) ppl_delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
#define ppl_delay_us(x) ppl_delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))



// Simple Delay Function, you might adjust the value for different clock speed
#define	delay_us(x) {unsigned char _dcnt; \
		    _dcnt = (x)/(24000000UL/_XTAL_FREQ)|1; \
		    while(--_dcnt != 0) continue; \
                    }

void delay_ms(unsigned int cnt);

void ppl_delay(unsigned long x);






#define TRUE  1
#define FALSE 0

#define HIGH  1
#define LOW   0

#define ON    1
#define OFF   0


// more type redefinitions
typedef unsigned char BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long DWORD;

typedef unsigned char UCHAR;
typedef unsigned int UINT;
typedef unsigned short USHORT;
typedef unsigned long ULONG;

typedef char CHAR;
typedef int INT;
typedef long LONG;

// Convert BCD (Binary-Coded Decimal) to normal Decimal numbers
uint8_t ppl_convertBCDToDec(uint8_t bcd_value);

// Convert normal Decimal numbers to BCD (Binary-Coded Decimal)
uint8_t ppl_convertDecToBCD(uint8_t decimal_value);