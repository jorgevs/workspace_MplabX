#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */
#include <stdio.h>

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

// The purpose of this library is to use the portD for the LCD instead of PortB 
// as specified in the normal <xlcd.h> library
#include "ppl_xlcd.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
int maxDelay = 200;
char s[10];
char emptyString[10];

void interrupt slower(void){
    PORTAbits.RA1 = 0;
    ppl_delay_ms(200);
    PORTAbits.RA1 = 1;
    ppl_delay_ms(200);
    
    //check if the interrupt is caused by the pin RB2
    if(INTCON3bits.INT2F == 1){
        maxDelay = maxDelay - 25;
        if(maxDelay < 0){
            maxDelay = 200;
        }        
        INTCON3bits.INT2F = 0;
  
        // Clear display
        WriteCmdXLCD(0x01);
        // Shift cursor to beginning of first line
        SetDDRamAddr(0x00);
        putrsXLCD("Int2 to XLCD");

        // Shift cursor to beginning of second line
        SetDDRamAddr(0x40);
        putrsXLCD("maxDelay: ");
        sprintf(s, "%d", maxDelay);   
        putrsXLCD(s);
    }
}

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    TRISBbits.RB2 = 1; //set RB2 as Input

    INTCON3bits.INT2E = 1;   //enable Interrupt2 (RB2 as interrupt)    
    INTCON2bits.INTEDG0 = 0; //cause interrupt at falling edge
    INTCON3bits.INT2F = 0;   //reset interrupt flag
    INTCONbits. GIE = 1;     // Global interrupt enable
    

    // Clear display
    WriteCmdXLCD(0x01);
    // Shift cursor to beginning of first line
    SetDDRamAddr(0x00);
    putrsXLCD("Int2 to XLCD");

    // Shift cursor to beginning of second line
    SetDDRamAddr(0x40);
    putrsXLCD("maxDelay: ");
    sprintf(s, "%d", maxDelay);   
    putrsXLCD(s);
    
    
    while(TRUE){                               
        PORTAbits.RA3 = 0;
        ppl_delay_ms(maxDelay);
        PORTAbits.RA3 = 1;
        ppl_delay_ms(maxDelay);        
    }
}