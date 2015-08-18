#include <xc.h>         /* XC8 General Include File */
#include "system.h"

void ConfigureOscillator(void){
    /* TODO Add clock switching code if appropriate.  */
    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */    
    OSCCONbits.IRCF2=1;
    OSCCONbits.IRCF1=1;
    OSCCONbits.IRCF0=1;
    
    OSCCONbits.SCS=1;    
}
