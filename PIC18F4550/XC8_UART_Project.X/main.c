#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */

#include "ppl_utils.h"
#include <plib/usart.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

void main(void){    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    unsigned char Rxdata[25];
    unsigned char Txdata[] = "MICROCHIP_USART";
    unsigned char config=0, spbrg=0, c=0, cadena[10];
    int i=0;
    
    CloseUSART(); //turn off usart if was previously on    

    //-----configure USART -----
    config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW;        
    //-----SPBRG needs to be changed depending upon oscillator frequency-------
    spbrg = 12; //At 8Mhz of oscillator frequency & baud rate of 9600 ((8000000/9600)/64)-1= 77
    OpenUSART(config, spbrg); //API configures USART for desired parameters
    
    //------USART Transmission ----
    while(BusyUSART()); //Check if Usart is busy or not
    putsUSART((char *)Txdata); //transmit the string    
    putcUSART('\n');
    //putrsUSART( "test" );
        
    while(true){
        while(c != 13){
            while(RCIF == 0);
            c = ReadUSART();
            cadena[i] = c;
            i++;               
            //WriteUSART((char *)cadena);
        }
            
        while(BusyUSART()); //Check if Usart is busy or not
        putsUSART(cadena); //echo back the data recieved back to host      
        c=0;
        cadena[0] = '\n';
        i=1;
    }        
    CloseUSART();        
}