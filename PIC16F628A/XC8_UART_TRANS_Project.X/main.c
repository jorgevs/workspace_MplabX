#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */

#include "ppl_utils.h"

#define USE_OR_MASKS
#include "usart_pic16.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

void main(void){    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /*unsigned char Rxdata[25];
    unsigned char Txdata[] = "MICROCHIP_USART ";
    unsigned char config=0,spbrg=0,baudconfig=0,i=0;*/ 
    
    //Initialize USART with baud rate 9600
    USARTInit(9600);
    
    //Write intro text
    USARTWriteLine("***********************************************");
    USARTWriteLine("USART Test");
    USARTWriteLine("----------");
    USARTWriteLine("Type a character on keyboard");
    USARTWriteLine("it will reach the PIC MCU via the serial line");
    USARTWriteLine("PIC MCU will return the same character but ");
    USARTWriteLine("enclosed in a <>");
    USARTWriteLine("--");
    USARTWriteLine("For example if you type 'a' you will see <a>");
    USARTWriteLine("appear on serial terminal.");
    USARTWriteLine(" ");
    USARTWriteLine("This checks both way serial transfers.");
    USARTWriteLine("");
    USARTWriteLine("Copyright (C) 2008-2013");
    USARTWriteLine("www.eXtremeElectronics.co.in");
    USARTWriteLine("***********************************************");
    USARTGotoNewLine();
    USARTGotoNewLine();


    //------USART Transmission ----
    while(true){       
        //Get the amount of data waiting in USART queue
        uint8_t c = USARTDataAvailable();

        //If we have some data
        if(c != 0){
            //Read a character from the PC
            char data = USARTReadData();

            //And send it back
            USARTWriteChar('<');
            USARTWriteChar(data);
            USARTWriteChar('>');
        }
   
        PORTAbits.RA2 = 0;
        ppl_delay_ms(100);
        PORTAbits.RA2 = 1;
        ppl_delay_ms(100);
    }

}