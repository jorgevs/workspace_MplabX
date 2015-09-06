#include <xc.h>
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
    init_KBD();
    
    TRISA = 0;
    LATA = 0;
}

void init_KBD(void){              //Initialize KBD
    TRISB   = 0xF0;            //Use PORTB for Keypad
    LATB    = 0x00;
    PORTB   = 0x00;
    
    INTCON2bits.NOT_RBPU = 1;  // Pull-ups disabled
}