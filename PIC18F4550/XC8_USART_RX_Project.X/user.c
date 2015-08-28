#include <xc.h>         /* XC8 General Include File */
#include "user.h"
#include <usart.h>

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
    init_USART();                    //Call the Initialize USART function    
}

void init_USART(void){              //Initialize USART
    unsigned char config=0, spbrg=0;
    
    CloseUSART(); //turn off usart if was previously on    
    //-----configure USART -----
    config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW;        
    //-----SPBRG needs to be changed depending upon oscillator frequency-------
    spbrg = 12; //At 8Mhz of oscillator frequency & baud rate of 9600 ((8000000/9600)/64)-1= 77
    OpenUSART(config, spbrg); //API configures USART for desired parameters 
}

void init_XLCD(void){              //Initialize LCD display
    
    OpenXLCD(FOUR_BIT&LINES_5X7);  //configure LCD in 4-bit Data Interface mode
                                   //and 5x7 characters, multiple line display
    
    while(BusyXLCD());             //Check if the LCD controller is not busy
                                   //before writing some commands
    
    WriteCmdXLCD(0x06);            // move cursor right, don't shift display
    WriteCmdXLCD(0x0C);            //turn display on without cursor
 }