#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

#include <stdio.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

//#define set_port_kbd PORTB // Change if port is different
#define row1port LATBbits.LATB0
#define row2port LATBbits.LATB1
#define row3port LATBbits.LATB2
#define row4port LATBbits.LATB3
#define col1port PORTBbits.RB4
#define col2port PORTBbits.RB5
#define col3port PORTBbits.RB6
//#define col4port PORTBbits.RB7   //if a 4x4 keypad is used

unsigned char  const Seven_Segment_MAP[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
char const keyPadMatrix[] =
{
    '1','2','3',
    '4','5','6',
    '7','8','9',
    '*','0','#',
    0xFF
};
char key,old_key;
char keypress,keyboard='0';

void kbd_init();
int kbd_getc();

void main(void){
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();    
    
    kbd_init();

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

void kbd_init(){
    TRISB   = 0xF0;            //Use PORTB for Keypad
    LATB    = 0x00;
    PORTB   = 0x00;
    
    INTCON2bits.NOT_RBPU = 1;  // Pull-ups disabled
    TRISA   = 0x00;            //Use PORTA to display
}

int kbd_getc(){
    char key = 0, row;
    for( row = 0b00000001; row < 0b00010000; row <<= 1 ){
        {   // turn on row output
            row1port = (row & 0x0001)>>0;
            row2port = (row & 0x0002)>>1;
            row3port = (row & 0x0004)>>2;
            row4port = (row & 0x0008)>>3;
            __delay_ms(1);
        }
        // read colums - break when key press detected
        if( col1port )break;  key++;
        if( col2port )break;  key++;
        if( col3port )break;  key++;
        //if( col4port )break;  key++;
    }
    row1port = 0;
    row2port = 0;
    row3port = 0;
    row4port = 0;
    
    if (key != old_key){
      old_key = key;
      return keyPadMatrix[key];
    }else{
        return keyPadMatrix[ 0x0C ];
    }
}

