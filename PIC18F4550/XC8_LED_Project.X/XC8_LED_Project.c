#include <xc.h>
#include "../../XC8_PPL_LIBRARIES.X/ppl_utils.h"

#define _XTAL_FREQ 4800000

#define TRUE          1
#define FALSE         0


void main(void) {
    TRISA = 0;
    PORTA = 0;

    while(TRUE){
        PORTAbits.RA2 = 0;
        ppl_delay_ms(2000);
        PORTAbits.RA2 = 1;
        ppl_delay_ms(2000);
    }
}