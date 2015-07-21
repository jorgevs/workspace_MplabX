#include <xc.h>
#include "../../XC8_PPL_LIBRARIES.X/ppl_utils.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2clcd.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2c.h"

#define _XTAL_FREQ 48000000

#define TRUE          1
#define FALSE         0

unsigned char I2C_Send[21] = "LCD_I2C_PCA8574";
char s[10];

void main(void) {
    TRISA = 0;
    PORTA = 0;

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


    while(TRUE){
        ppl_i2clcd_gotoxy(0,0);
        ppl_i2clcd_puts(I2C_Send);
        
        PORTAbits.RA2 = 0;
        ppl_delay_ms(200);
        PORTAbits.RA2 = 1;
        ppl_delay_ms(200);

        ppl_i2clcd_gotoxy(0,1);
        ppl_i2clcd_puts("Hello:");        

        ppl_i2clcd_gotoxy(6,1);
        ppl_i2clcd_putch(' ');
        ppl_i2clcd_putch('J');
        ppl_i2clcd_putch('V');
        ppl_i2clcd_putch('S');
        
        ppl_i2clcd_gotoxy(12,1);
        sprintf(s, "%d", 456);        
        ppl_i2clcd_puts(s); 
    }
}