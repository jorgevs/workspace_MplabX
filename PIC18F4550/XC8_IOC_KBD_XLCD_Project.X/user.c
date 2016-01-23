#include <xc.h>
#include "user.h"

// The purpose of this library is to use the portD for the LCD instead of PortB 
// as specified in the normal <xlcd.h> library
#include "ppl_xlcd.h"
#include "ppl_kbd.h"

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

    init_XLCD();                    //Call the Initialize LCD display function
    init_KBD();
}

void init_XLCD(void){              //Initialize LCD display
    OpenXLCD(FOUR_BIT & LINES_5X7);  //configure LCD in 4-bit Data Interface mode
                                   //and 5x7 characters, multiple line display
    
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    WriteCmdXLCD(0x06);            // move cursor right, don?t shift display
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    WriteCmdXLCD(0x0C);            //turn display on without cursor
 }

void init_KBD(void){              //Initialize KBD
    TRISB   = 0xF0;            //Use PORTB for Keypad (0b11110000))
    LATB    = 0xF0;
    PORTB   = 0x00;
    
    INTCON2bits.RBPU = 0;  // Pull-ups enabled
}