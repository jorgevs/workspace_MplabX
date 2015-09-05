#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

#include <xlcd.h>

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

void main(void){
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    putrsXLCD("Hello World");          //Display "Hello World"
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    SetDDRamAddr(0x40);            //shift cursor to beginning of second line
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    putrsXLCD("LCD Display");      //Display "LCD display"

    while(true){
        LATAbits.LA3 = 0;
        ppl_delay_ms(250);
        LATAbits.LA3 = 1;
        ppl_delay_ms(250);
    }
}
