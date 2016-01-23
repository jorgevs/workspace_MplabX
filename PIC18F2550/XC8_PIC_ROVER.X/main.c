#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>
#include <pic18f2550.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */

#include "ppl_utils.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

void main(void){    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    #define LEFT_CODE     0b00001000
    #define FORWARD_CODE  0b00000100
    #define BACK_CODE     0b00000010
    #define RIGHT_CODE    0b00000001
    
    #define LEFT_CMD      0b00001011
    #define FORWARD_CMD   0b00001010
    #define BACK_CMD      0b00000101
    #define RIGHT_CMD     0b00001110
    
    
    
    //TESTING...
    LATCbits.LC0 = LOW;
    
    LATAbits.LA5 = LOW;    
    ppl_delay_ms(500);
    LATAbits.LA5 = HIGH;
    
    LATB = 0x0F;
    
    while(true){
        
        //Reads the VT value
        if(PORTAbits.RA4){
            
            //TESTING...
            LATCbits.LC0 = HIGH;
            
            //Reads the command received
            char code = (PORTA & 0X0F);
            
            if (code == LEFT_CODE) {
                LATB = LEFT_CMD;
            } else if (code == RIGHT_CODE) {
                LATB = RIGHT_CMD;
            } else if (code == FORWARD_CODE) {
                LATB = FORWARD_CMD;
            } else if (code == BACK_CODE) {
                LATB = BACK_CMD;
            }else{
                LATB = 0x0F;
            }
        }else{
            //TESTING...
            LATCbits.LC0 = LOW;
        }
    }   
}