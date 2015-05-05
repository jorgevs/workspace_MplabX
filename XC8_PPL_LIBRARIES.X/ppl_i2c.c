#include "ppl_i2c.h"

void ppl_i2c_init(unsigned char masterMode, unsigned char slewMode) {
    CloseI2C(); // Close I2C if was operating earlier
    OpenI2C(masterMode, slewMode);
    SSPADD = 0x0A; //400kHz Baud clock(9) @8MHz
    IdleI2C();
}

void ppl_i2c_writeByte(unsigned char data) {
    signed char status;
    unsigned char tempBuffer;

    IdleI2C();
    StartI2C();

    tempBuffer = SSPBUF; //read any previous stored content in buffer to clear buffer full status
    do {
        status = WriteI2C(data); //write the I2C data
        //check if bus collision happened
        if (status == -1) {
            tempBuffer = SSPBUF; //upon bus collision detection clear the buffer,
            SSPCON1bits.WCOL = 0; // clear the bus collision status bit
        }
    } while (status != 0); //write untill successful communication

}

unsigned char ppl_i2c_readByte(void) {
    return getcI2C();
}