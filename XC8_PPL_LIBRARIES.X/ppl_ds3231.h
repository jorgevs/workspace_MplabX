#include <xc.h>
#include <i2c.h>
#include "ppl_utils.h"
#include "ppl_i2c.h"

#define DS3231_ADDR	0x68
#define SLAVE_DS3231_ADDR (DS3231_ADDR << 1)

// I2C Bus Control Definition
#define I2C_WRITE_CMD   0x00
#define I2C_READ_CMD    0x01

#define REG_SEC		0x00
#define REG_MIN		0x01
#define REG_HOUR	0x02
#define REG_DOW		0x03
#define REG_DATE	0x04
#define REG_MON		0x05
#define REG_YEAR	0x06
#define REG_CON		0x0E
#define REG_STATUS	0x0F
#define REG_AGING	0x10
#define REG_TEMPM	0x11
#define REG_TEMPL	0x12

#define SEC_1970_TO_2000 946684800



int8_t *ppl_getTime(void);
int8_t *ppl_readTime(void);

void ppl_setTime(uint8_t *time);
void ppl_writeTime(uint8_t *time);

