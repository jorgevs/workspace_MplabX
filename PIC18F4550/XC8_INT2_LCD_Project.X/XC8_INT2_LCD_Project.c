#include <xc.h>
#include "../../XC8_PPL_LIBRARIES.X/ppl_utils.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2clcd.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2c.h"

#define _XTAL_FREQ 48000000

#define TRUE          1
#define FALSE         0

int maxDelay = 200;
char s[10];
char emptyString[10] = "          ";

void interrupt slower(void){
    PORTAbits.RA1 = 0;
    ppl_delay_ms(maxDelay);
    PORTAbits.RA1 = 1;
    ppl_delay_ms(maxDelay);
    
    //check if the interrupt is caused by the pin RB0    
    if(INTCON3bits.INT2F == 1){
        maxDelay = maxDelay - 25;
        if(maxDelay < 0){
            maxDelay = 200;
        }        
        INTCON3bits.INT2F = 0;
  
        
        ppl_i2clcd_gotoxy(10,1);
        ppl_i2clcd_puts(emptyString);
        
        ppl_i2clcd_gotoxy(10,1);
        sprintf(s, "%d", maxDelay);        
        ppl_i2clcd_puts(s);        
    }
}


void main(void) {
    TRISBbits.RB0 = 1; //set RB0 as Input

    INTCON3bits.INT2E = 1;   //enable Interrupt2 (RB0 as interrupt)    
    INTCON2bits.INTEDG0 = 1; //cause interrupt at raising edge
    INTCON3bits.INT2F = 0;   //reset interrupt flag
    INTCONbits. GIE = 1;     // Global interrupt enable
   
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

    ppl_i2clcd_puts("Initializing...");

    ppl_delay(200);

    ppl_i2clcd_putcmd(LCD_CLEAR, LCD_2CYCLE);  // LCD Clear
    ppl_i2clcd_putcmd(LCD_HOME, LCD_2CYCLE);   // LCD Home

       
    ppl_i2clcd_gotoxy(0,0);
    ppl_i2clcd_puts("Int2 to LCD");        
        
    ppl_i2clcd_gotoxy(0,1);
    ppl_i2clcd_puts("maxDelay: ");
        
    ppl_i2clcd_gotoxy(10,1);
    ppl_i2clcd_puts(emptyString);
        
    ppl_i2clcd_gotoxy(10,1);
    sprintf(s, "%d", maxDelay);        
    ppl_i2clcd_puts(s);
    
    
    while(TRUE){                               
        PORTAbits.RA2 = 0;
        ppl_delay_ms(maxDelay);
        PORTAbits.RA2 = 1;
        ppl_delay_ms(maxDelay);        
    }
}