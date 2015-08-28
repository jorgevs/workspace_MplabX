#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

void main(void) {
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    PORTAbits.RA2 = 0;
    PORTDbits.RD6 = 0;
    
    while(TRUE){
    
        if(PORTBbits.RB0){                        
            PORTAbits.RA2 = 1;            
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
            
            PORTAbits.RA2 = 0;
            PORTDbits.RD6 = 0;
        }
    }
}