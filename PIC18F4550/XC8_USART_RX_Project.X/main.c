#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

#include <usart.h>
#include <xlcd.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char RxData[10];

void main(void){    
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    
    /* Initialize I/O and Peripherals for application */
    InitApp();
            
    while(true){
        while(BusyUSART()); //Check if Usart is busy or not
        getsUSART(RxData, 9);
        
        SetDDRamAddr(0x00);             //shift cursor to beginning of first line
        putrsXLCD("Hello World");       //Display "Hello World"
        
        SetDDRamAddr(0x40);             //shift cursor to beginning of second line
        putrsXLCD((char*)RxData);      //Display the received string
    }        
    CloseUSART();
}
