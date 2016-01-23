#include <xc.h>         /* XC8 General Include File */
#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/
/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void){
    /* TODO Initialize User Ports/Peripherals/Project here */
    
    /* Setup analog functionality and port direction */
    /* Initialize peripherals */
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    /* Enable interrupts */

    
    // Enable all ports as Digital
    ADCON1 = 0b00001111;

    // Disable the internal pull-up on PORTB  
    INTCON2bits.RBPU = 1; 

    
    TRISAbits.RA0 = 1;  //4 Data bits from the HT-12D decoder
    TRISAbits.RA1 = 1;
    TRISAbits.RA2 = 1;
    TRISAbits.RA3 = 1;    
    TRISAbits.RA4 = 1;  //VT (ValidTransmission pin) used to identify if a valid code has been received
    TRISAbits.RA5 = 0;  //Enable pin in the HMR-915 (set LOW - wait for module initialization - set HI)
   
    TRISB = 0;
    
    TRISCbits.RC0 = 0;
}

