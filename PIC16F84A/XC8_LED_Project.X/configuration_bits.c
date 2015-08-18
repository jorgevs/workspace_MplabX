/******************************************************************************/
/* Main Files to Include                                                      */
/******************************************************************************/
#include <xc.h>         /* XC8 General Include File */
/******************************************************************************/
/* Configuration Bits                                                         */

// PIC18F4550 Configuration Bit Settings


// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)