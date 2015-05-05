#include "ppl_ds3231.h"

int8_t *ppl_getTime(void) {
    return ppl_readTime();
}

int8_t *ppl_readTime(void) {
    int8_t time[8];

    uint8_t temp;
    uint8_t i;

    IdleI2C();
    StartI2C();

    //write the I2C DS3231 address and write mode
    ppl_i2c_writeByte(SLAVE_DS3231_ADDR | I2C_WRITE_CMD);
    //write the REG_SEC register address
    ppl_i2c_writeByte(REG_SEC);

    IdleI2C();
    StartI2C();
    
    //write the I2C DS3231 address and read mode
    ppl_i2c_writeByte(SLAVE_DS3231_ADDR | I2C_READ_CMD);

    //*** Recieve data from slave ***
    for (i = REG_SEC; i < REG_YEAR; i++) {
        temp = ppl_i2c_readByte();
        time[i] = ppl_bcdToDec(temp);
    }
    temp = ppl_i2c_readByte();
    time[REG_YEAR] = ppl_bcdToDec(temp);    

    //send the end of transmission signal through nack
    NotAckI2C();
    //wait till ack sequence is complete
    while (SSPCON2bits.ACKEN != 0);

    StopI2C();
    return time;
}

void ppl_setTime(uint8_t *time) {
    uint8_t *tempTime;
    tempTime = time;
    ppl_writeTime(tempTime);
}

void ppl_writeTime(uint8_t *time) {
    IdleI2C();
    StartI2C();

    //write the I2C DS3231 address and write mode
    ppl_i2c_writeByte(SLAVE_DS3231_ADDR | I2C_WRITE_CMD);
    //write the REG_SEC register address
    ppl_i2c_writeByte(REG_SEC);

    //*** Receive data from slave ***
    uint8_t i;
    for (i = REG_SEC; i <= REG_YEAR; i++) {
        ppl_i2c_writeByte(ppl_decToBcd(time[i]));
    }
    StopI2C();
}