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
#include "ppl_kbd.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

char keypress;

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