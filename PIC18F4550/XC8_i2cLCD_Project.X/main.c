#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */

#include "ppl_utils.h"
#include "ppl_i2clcd.h"
#include "ppl_i2c.h"
#include <stdio.h>   /* For sprintf definitions */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

void main(void){    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    
    unsigned char I2C_Send[21] = "LCD_I2C_PCA8574";
    char s[10];

    //--- INITIALISE THE I2C MODULE FOR MASTER MODE WITH 400KHz ---
    ppl_i2c_init(MASTER, SLEW_ON);
    //-------------------------------------------------------------

    //--- INITIALISE THE i2cLCD MODULE ---
    ppl_i2clcd_init();
    //------------------------------------

    ppl_i2clcd_putcmd(LCD_CLEAR, LCD_2CYCLE);  // LCD Clear
    ppl_i2clcd_putcmd(LCD_HOME, LCD_2CYCLE);   // LCD Home

    ppl_i2clcd_putch('a');

    ppl_delay(100);

    ppl_i2clcd_puts("Initializing...");

    ppl_delay(100);

    ppl_i2clcd_putcmd(LCD_CLEAR, LCD_2CYCLE);  // LCD Clear
    ppl_i2clcd_putcmd(LCD_HOME, LCD_2CYCLE);   // LCD Home


    while(true){
        ppl_i2clcd_gotoxy(0,0);
        ppl_i2clcd_puts(I2C_Send);
        
        PORTAbits.RA3 = 0;
        ppl_delay_ms(200);
        PORTAbits.RA3 = 1;
        ppl_delay_ms(200);

        /*ppl_i2clcd_gotoxy(0,1);
        ppl_i2clcd_puts("Hello:");        

        ppl_i2clcd_gotoxy(6,1);
        ppl_i2clcd_putch(' ');
        ppl_i2clcd_putch('J');
        ppl_i2clcd_putch('V');
        ppl_i2clcd_putch('S');
        
        ppl_i2clcd_gotoxy(12,1);
        sprintf(s, "%d", 456);        
        ppl_i2clcd_puts(s); */
    } 
}