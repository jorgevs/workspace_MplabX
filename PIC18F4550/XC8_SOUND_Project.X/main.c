#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */

#include "ppl_utils.h"
#include "ppl_sound.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

#define SIZE 25

typedef struct note {
   long tone;
   long length;
} happy_bday[SIZE];
happy_bday hp = {{262,350}, {262,100}, {262,500}};

void main(void){
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();    
    
    TRISA   = 0x00;
        
   int i;
  
    while(TRUE){
        PORTAbits.RA1 = 0;
        ppl_delay_ms(200);
        PORTAbits.RA1 = 1;
        ppl_delay_ms(200);    
        PORTAbits.RA1 = 0;
        ppl_delay_ms(200);
        PORTAbits.RA1 = 1;
        ppl_delay_ms(200); 
        
        for(i=0; i<SIZE; ++i) {
            generate_tone(hp[i].tone, hp[i].length);
            ppl_delay_ms(75);
        }
    }
}
