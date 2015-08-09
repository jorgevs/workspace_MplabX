#include <xc.h>
#include "../../XC8_PPL_LIBRARIES.X/ppl_utils.h"

#define _XTAL_FREQ 20000000

#define TRUE          1
#define FALSE         0


void main(void) {
    TRISB = 1;
    PORTB = 1;

    TRISA = 0;
    PORTA = 0;

    TRISD = 0;
    PORTD = 0;

    
    PORTAbits.RA1 = 0;
    PORTAbits.RA2 = 0;
    PORTDbits.RD7 = 0;
    PORTDbits.RD6 = 0; 
    
    while(TRUE){
    
        if(PORTBbits.RB0){            
            PORTAbits.RA1 = 1;
            PORTAbits.RA2 = 1;            
            PORTDbits.RD7 = 1;
            PORTDbits.RD6 = 1;            
            
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            ppl_delay_ms(250);
            
            PORTAbits.RA1 = 0;
            PORTAbits.RA2 = 0;
            PORTDbits.RD7 = 0;
            PORTDbits.RD6 = 0;            
        }
    }
}