#include <xc.h>
#include <i2c.h>

#include "ppl_utils.h"


void ppl_i2c_init(unsigned char masterMode, unsigned char slewMode);

void ppl_i2c_writeByte(unsigned char data);

unsigned char ppl_i2c_readByte(void);