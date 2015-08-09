#include <xc.h>
#include "../../XC8_PPL_LIBRARIES.X/ppl_utils.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2clcd.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2c.h"

#define _XTAL_FREQ 48000000

#define HIGH 1
#define LOW 0
#define R1 PORTBbits.RB0
#define R2 PORTBbits.RB1
#define R3 PORTBbits.RB2
#define R4 PORTBbits.RB3
#define C1 PORTBbits.RB4
#define C2 PORTBbits.RB5
#define C3 PORTBbits.RB6
#define C4 PORTBbits.RB7
#define SEG_EN1 LATCbits.LATC1
#define SEG_EN2 LATCbits.LATC0

unsigned char val;
int maxDelay = 200;


void update(unsigned char);
void seg_wrt();
 
void main(void){
    ADCON1 = 0x0F;      // Disable all analog channel
    TRISD = 0x00;       // PORT D Output
    TRISC = 0x00;       // PORT C output
    TRISB = 0xF0;       // PORT B upper nibble Input Lower Nibble Output
    LATD = 0X00;        // 7 Segment port.
    LATC = 0x00;        // all segment enables pins are off
    LATB = 0xF0;        // Initial value for keypad port
 
    RBPU = LOW;         // Enable Weak internal pull-ups in pin RB4 and RB5
    RBIE = HIGH;        // Enable PORT B interrupt
    RBIF = LOW;         // PORT B interrupt flag
    INTCONbits.GIE = HIGH;     // Global interrupt enable
 
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
    ppl_i2clcd_puts("Keypad");        
        
    ppl_i2clcd_gotoxy(0,1);
    ppl_i2clcd_puts("maxDelay: ");
                   
    
    while(TRUE){                               
        PORTAbits.RA2 = 0;
        ppl_delay_ms(maxDelay);
        PORTAbits.RA2 = 1;
        ppl_delay_ms(maxDelay);
        
        
        ppl_i2clcd_gotoxy(10,1);
        //sprintf(s, "%d", maxDelay);
        ppl_i2clcd_puts(val);
    }
}

void interrupt IOC_ISR(void){
    if(RBIF && RBIE){
    LATB = 0xf0;
        if(C1 == LOW){
            R1 = HIGH;
            if(C1 == HIGH)
                update(16);
            else {
                R2 = HIGH;
                if(C1 == HIGH)
                    update(15);
                else {
                    R3 = HIGH;
                    if(C1 == HIGH)
                        update(14);
                    else update(13);
        }
            }
    }
    if(C2 == LOW){
            R1 = HIGH;
            if(C2 == HIGH)
                update(12);
            else {
                R2 = HIGH;
                if(C2 == HIGH)
                    update(11);
                else{
                    R3 = HIGH;
                    if(C2 == HIGH)
                        update(10);
                    else update(9);
                }
            }
    }
    if(C3 == LOW){
            R1 = HIGH;
            if(C3 == HIGH)
                update(8);
            else {
                R2 = HIGH;
                if(C3 == HIGH)
                    update(7);
                  else{
                    R3 = HIGH;
                    if(C3 == HIGH)
                        update(6);
                    else update(5);
                }
            }
    }
 
    LATB = 0xF0;
    RBIF = LOW;
    }
 
}
 
// This function is not really needed /////////////////////////////////////////
void update(unsigned char data){
    val = data;
}
