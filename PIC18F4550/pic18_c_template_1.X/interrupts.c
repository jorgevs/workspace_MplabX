#include <xc.h>         /* XC8 General Include File */

/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
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

