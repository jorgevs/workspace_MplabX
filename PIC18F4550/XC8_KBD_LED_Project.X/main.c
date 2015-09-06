#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"
#include "ppl_kbd.h"
#include <stdio.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */
char keypress;

void main(void){
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();    
    
    while(TRUE){                               
        keypress = kbd_getc();

        switch(keypress){
            case '1': LATAbits.LA0 = 1;
                      ppl_delay_ms(200);
                      break;
            case '2': LATAbits.LA1 = 1;
                      ppl_delay_ms(200);
                      break;
            case '3': LATAbits.LA2 = 1;
                      ppl_delay_ms(200);
                      break;
            case '4': LATAbits.LA3 = 1;
                      ppl_delay_ms(200);
                      break;
            case '5': LATAbits.LA4 = 1;
                      ppl_delay_ms(200);
                      break;
            case '6': LATAbits.LA5 = 1;
                      ppl_delay_ms(200);
                      break;
            case '7': LATAbits.LA6 = 1;   //The oscillator config is FOSC = INTOSCIO_EC so that: Internal oscillator, port function on RA6, EC used by USB (INTIO)
                      ppl_delay_ms(200);
                      break;                              
        }
        LATA = 0;       
    }
}