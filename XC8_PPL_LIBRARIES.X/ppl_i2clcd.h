#include <xc.h>
#include "ppl_utils.h"

// LCD Command
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02

#define LCD_1CYCLE 0x00     // 8 BITS COMMUNICATION
#define LCD_2CYCLE 0x01     // 4 BITS COMMUNICATION

// I2C Bus Control Definition
#define I2C_WRITE_CMD 0x00
#define I2C_READ_CMD 0x01

// P7,P6,P5,P4 = Data, P3=Backlight (BL), P2=E, P1=RW, P0=RS
#define LCD_BL 0b00001000
#define LCD_EN 0b00000100
#define LCD_RW 0b00000010

#define LCD_RS_DATA 0b00000001
#define LCD_RS_INST 0b00000000

#define LCD_LINE_TWO 0x40    // LCD RAM address for the second line

#define PCA8574_ADDR 0x20
#define SLAVE_PCA8574_ADDR (PCA8574_ADDR << 1)


void ppl_i2clcd_gotoxy(int x, int y);

void ppl_i2clcd_writePCA8574(unsigned char data);

void ppl_i2clcd_putcmd(unsigned char data, unsigned char cmdtype);

void ppl_i2clcd_putch(unsigned char data);

void ppl_i2clcd_puts(const char *s);

void ppl_i2clcd_init();
