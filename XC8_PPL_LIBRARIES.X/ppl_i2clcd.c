#include "ppl_i2clcd.h"

/*
 * This function sets the cursor ina specified position of the LCD
 * Note that ppl_i2clcd_gotoxy(0,0) refers to the upper left corner of the screen
 */
void ppl_i2clcd_gotoxy(int x, int y) {
    unsigned char dataAddress;

    if (y != 0) {
        dataAddress = LCD_LINE_TWO;
    } else {
        dataAddress = 0;
    }
    dataAddress = dataAddress + x;
    ppl_i2clcd_putcmd(0x80 | dataAddress, LCD_2CYCLE);
}

/*
 * This function sends info to the PCA8574 through the I2C protocol, in the following order:
 *  Start - deviceAddress - value - Stop
 */
void ppl_i2clcd_writePCA8574(unsigned char value) {
    signed char status;
    unsigned char tempBuffer;

    IdleI2C();
    StartI2C();

    tempBuffer = SSPBUF; //read any previous stored content in buffer to clear buffer full status
    do {
        status = WriteI2C(SLAVE_PCA8574_ADDR | I2C_WRITE_CMD); //write the I2C LCD address
        //check if bus collision happened
        if (status == -1) {
            tempBuffer = SSPBUF; //upon bus collision detection clear the buffer,
            SSPCON1bits.WCOL = 0; // clear the bus collision status bit
        }
    } while (status != 0); //write untill successful communication

    tempBuffer = SSPBUF; //read any previous stored content in buffer to clear buffer full status
    do {
        status = WriteI2C(value); //write the value
        //check if bus collision happened
        if (status == -1) {
            tempBuffer = SSPBUF; //upon bus collision detection clear the buffer,
            SSPCON1bits.WCOL = 0; // clear the bus collision status bit
        }
    } while (status != 0); //write untill successful communication

    StopI2C();
}

/*
 * Generic function, used to send data or a command to the LCD through I2C protocol
 *
 * value - data that is sent
 *
 * numCycle - 0: One cycle write  - used for a 8 BITS COMMUNICATION
              1: Two cycle writes - used for a 4 BITS COMMUNICATION
 *                  LCD Data PCA8574:    P7, P6, P5, P4
 *                  LCD Control PCA8574: P3:Back Light, P2:E-Enable, P1:RW, P0:RS
 *
 * registerType - 0: Writes to the Instructions Regsiter
 *                1: Writes to the Data Regsiter
 */
void ppl_i2clcd_putGeneric(unsigned char value, unsigned char numCycle, unsigned char registerType) {
    unsigned char lcdValue;

    // Put the Upper 4 bits data
    lcdValue = (value & 0xF0) | LCD_BL | registerType;
    ppl_i2clcd_writePCA8574(lcdValue | LCD_EN);
    __delay_us(10);

    // Write Enable Pulse E: Hi -> Lo
    ppl_i2clcd_writePCA8574(lcdValue & ~LCD_EN);
    __delay_ms(10);

    if (numCycle) {
        // LCD Data PCA8574:    P7, P6, P5, P4
        // LCD Control PCA8574: P3:Back Light, P2:E-Enable, P1:RW, P0:RS

        // Put the Lower 4 bits data
        lcdValue = ((value << 4) & 0xF0) | LCD_BL | registerType;
        ppl_i2clcd_writePCA8574(lcdValue | LCD_EN);
        __delay_us(10);

        // Write Enable Pulse E: Hi -> Lo
        ppl_i2clcd_writePCA8574(lcdValue & ~LCD_EN);
        __delay_ms(10);
    }
}

/*
 * This funtion send a COMMAND to the LCD. Since it is a command, it must go to the
 * Instruction register, which is selected by RS
 */
void ppl_i2clcd_putcmd(unsigned char data, unsigned char numCycle) {
    // This function sends a CMD to the Intructions Register, RS = 0
    ppl_i2clcd_putGeneric(data, numCycle, LCD_RS_INST);
}

/*
 * This funtion send DATA to the LCD. Since it is DATA, it must go to the
 * Data register, which is selected by RS
 */
void ppl_i2clcd_putch(unsigned char data) {
    // This function sends DATA to the Data Register, RS = 1
    ppl_i2clcd_putGeneric(data, LCD_2CYCLE, LCD_RS_DATA);
}

/*
 * This funtion sends and array of DATA to the LCD.
 */
void ppl_i2clcd_puts(const char *s) {
    while (*s != 0) { // While not Null
        ppl_i2clcd_putch(*s);
        s++;
    }
}

/*
 * This function initializes the LCD.
 * Always has to be called before any other ppl_i2clcd function
 */
void ppl_i2clcd_init() {
    // Initialization commands for Hitachi HD44780U LCD Display
    // Wait for more than 15 ms after VCC rises to 4.5 V
    __delay_ms(30); // Let LCD power up

    // Following bytes are all Command bytes, i.e. address = 0x00
    ppl_i2clcd_putcmd(0x03 << 4, LCD_1CYCLE); // Write Nibble 0x03 three times (per HD44780U initialization spec)
    __delay_ms(10); // (per HD44780U initialization spec)
    ppl_i2clcd_putcmd(0x03 << 4, LCD_1CYCLE); // Write Nibble 0x03 three times (per HD44780U initialization spec)
    __delay_ms(10); // (per HD44780U initialization spec)
    ppl_i2clcd_putcmd(0x03 << 4, LCD_1CYCLE); // Write Nibble 0x03 three times (per HD44780U initialization spec)
    __delay_ms(10);



    // Function set: Set interface to be 4 bits long (only 1 cycle write).
    ppl_i2clcd_putcmd(0x02 << 4, LCD_1CYCLE); // Write Nibble 0x02 once - Set interface to be 4 bits long
    __delay_ms(10);



    // Function set: DL=0;Interface is 4 bits, N=1; 2 Lines, F=0; 5x8 dots font)
    ppl_i2clcd_putcmd(0x28, LCD_2CYCLE);
    __delay_ms(10);

    // Display Off: D=0; Display off, C=0; Cursor Off, B=0; Blinking Off
    ppl_i2clcd_putcmd(0x08, LCD_2CYCLE);
    __delay_ms(10);

    // Display Clear
    ppl_i2clcd_putcmd(LCD_CLEAR, LCD_2CYCLE); // Clear display
    __delay_ms(10);

    // Entry Mode Set: I/D=1; Increment, S=0; No shift
    ppl_i2clcd_putcmd(0x06, LCD_2CYCLE); // Set cursor to increment
    __delay_ms(10);

    //--------------------------------------------------------------------------
    // Display: D=1; Display on, C=1; Cursor On, B=0; Blinking Off
    ppl_i2clcd_putcmd(0x0C, LCD_2CYCLE); // Set cursor to increment
    __delay_ms(10);
}
