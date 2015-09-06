#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

#include <stdio.h>

// The purpose of this library is to use the portD for the LCD instead of PortB 
// as specified in the normal <xlcd.h> library
#include "ppl_xlcd.h"

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

char const keyPadMatrix[] =
{
    '1','2','3',
    '4','5','6',
    '7','8','9',
    '*','0','#',
    0xFF
};
char key, old_key;
char keypress, keyboard='0';

int kbd_getc();
void xlcdPrintCharacter(char character);

void main(void){
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();    
    
    while(TRUE){                               
        keypress = kbd_getc();
        xlcdPrintCharacter(keypress);
        ppl_delay_ms(200);
    }
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

void xlcdPrintCharacter(char character){
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command    
    WriteCmdXLCD(0x01);            // Clear display
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command    
    SetDDRamAddr(0x00);             // Shift cursor to beginning of first line
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    putrsXLCD("KEYBOARD 4X3");

    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    SetDDRamAddr(0x40);            // Shift cursor to beginning of second line
    
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    putcXLCD(character);
}