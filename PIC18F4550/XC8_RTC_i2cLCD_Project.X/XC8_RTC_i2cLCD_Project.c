#include <xc.h>
#include "../../XC8_PPL_LIBRARIES.X/ppl_utils.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2clcd.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_ds3231.h"
#include "../../XC8_PPL_LIBRARIES.X/ppl_i2c.h"

#define _XTAL_FREQ 4800000


unsigned char I2C_Send[21] = "RTC_i2cLCD";

#define STR_BUFSIZE 16
char strbuf[STR_BUFSIZE + 1] = "                "; /* String buffer */

int8_t time1[8];
int8_t time2[8];
int8_t *time3;

char *mkNumString(int16_t number, uint8_t width, uint8_t lead, uint8_t radix) {
    uint8_t numdiv;
    uint8_t sign = lead;
    int8_t i;

    if (number < 0) {
        sign = '-';
        number = -number;
    }

    for (i = 0; i < width; i++)
        strbuf[i] = lead;
    strbuf[width] = '\0';
    i = width - 1;

    while (number > 0 || i == width - 1) {
        numdiv = number % radix;
        strbuf[i] = numdiv + 0x30;
        if (numdiv >= 10)
            strbuf[i] += 7;
        i--;
        number /= radix;
    }

    if (i >= 0)
        strbuf[i] = sign;

    return strbuf;
}

void main(void) {
    TRISA = 0;
    PORTA = 0;

    //--- INITIALISE THE I2C MODULE FOR MASTER MODE WITH 400KHz ---
    ppl_i2c_init(MASTER, SLEW_ON);
    //-------------------------------------------------------------

    //--- INITIALISE THE i2cLCD MODULE ---
    ppl_i2clcd_init();
    //------------------------------------

    ppl_i2clcd_putcmd(LCD_CLEAR, LCD_2CYCLE); // LCD Clear
    ppl_i2clcd_putcmd(LCD_HOME, LCD_2CYCLE); // LCD Home


    //Set an initial time
    time1[REG_SEC] = ppl_decToBcd(5);
    time1[REG_MIN] = ppl_decToBcd(16);
    time1[REG_HOUR] = ppl_decToBcd(7);
    time1[REG_DOW] = ppl_decToBcd(3);
    time1[REG_DATE] = ppl_decToBcd(4);
    time1[REG_MON] = ppl_decToBcd(5);
    time1[REG_YEAR] = ppl_decToBcd(15);
    ppl_setTime(time1);
    
    while (TRUE) {
    
        ppl_i2clcd_gotoxy(0, 0);

        time3 = ppl_getTime();
        //time3[8] = '\0' ;
        ppl_i2clcd_puts(time3);
        /*ppl_i2clcd_puts(mkNumString(ppl_getTime(REG_HOUR), 2, '0', 10));
        ppl_i2clcd_putch(":");
        ppl_i2clcd_puts(mkNumString(ppl_getTime(REG_MIN), 2, '0', 10));
        ppl_i2clcd_putch(":");
        ppl_i2clcd_puts(mkNumString(ppl_getTime(REG_SEC), 2, '0', 10));*/

        PORTAbits.RA2 = 0;
        ppl_delay_ms(2000);
        PORTAbits.RA2 = 1;
        ppl_delay_ms(2000);

        ppl_i2clcd_gotoxy(0, 1);
        ppl_i2clcd_puts("Hello...");
    }
}