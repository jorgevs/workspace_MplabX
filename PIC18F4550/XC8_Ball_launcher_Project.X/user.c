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
    
    TRISB = 1;
    PORTB = 1;

    TRISA = 0;
    PORTA = 0;

    TRISD = 0;
    PORTD = 0;   
}

