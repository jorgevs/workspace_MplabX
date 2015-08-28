#include <xc.h>
#include "../../XC8_PPL_LIBRARIES.X/ppl_utils.h"

#define _XTAL_FREQ 8000000

#define TRUE          1
#define FALSE         0

int maxDelay = 200;

void interrupt slower(void){
    PORTAbits.RA1 = 0;
    ppl_delay_ms(maxDelay);
    PORTAbits.RA1 = 1;
    ppl_delay_ms(maxDelay);
    
    //check if the interrupt is caused by the pin RB2
    if(INTCON3bits.INT2F == 1){
        maxDelay = maxDelay - 25;
        if(maxDelay < 0){
            maxDelay = 200;
        }        
        INTCON3bits.INT2F = 0;
    }
}


void main(void) {
    TRISBbits.RB2 = 1;       //set RB2 as Input
    INTCON3bits.INT2E = 1;   //enable Interrupt2 (RB2 as interrupt)    
    INTCON2bits.INTEDG0 = 1; //cause interrupt at raising edge
    INTCON3bits.INT2F = 0;   //reset interrupt flag
    INTCONbits. GIE = 1;     // Global interrupt enable

    
    TRISA = 0;
    PORTA = 0;

    while(TRUE){                       
        PORTAbits.RA3 = 0;
        ppl_delay_ms(maxDelay);
        PORTAbits.RA3 = 1;
        ppl_delay_ms(maxDelay);
    }
}