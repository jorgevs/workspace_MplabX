#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

#include <usart.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
unsigned char Txdata[] = "MICROCHIP_USART";

void main(void){    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
        
    //------USART Transmission ----
    while(BusyUSART()); //Check if Usart is busy or not
    putsUSART((char *)Txdata); //transmit the string    
    putsUSART("\n\r");
    
    putcUSART('x');
    putcUSART('\n');
    putcUSART('a');
    putsUSART("\n\r");
    
    putsUSART("test\n\r");
       
    bool ban = true;
    while(true){
        if(ban == true){
            for(int i=0; i <10; i++){
                while(BusyUSART()); //Check if Usart is busy or not
                putsUSART("123456789\r\n"); //echo back the data recieved back to host
                putsUSART("11111\r\n"); //echo back the data recieved back to host
            }
            ban = false;
        }
    }        
    CloseUSART();
}