#include "ppl_utils.h"

void ppl_delay(unsigned long x) {
    int numCycles = x / 100;
    for (int i = 0; i < numCycles; i++) {
        _delay(100);
    }
}

// Convert BCD (Binary-Coded Decimal) to normal Decimal numbers
uint8_t ppl_convertBCDToDec(uint8_t bcd_value) {
    return ( (bcd_value / 16 * 10) + (bcd_value % 16));
}

// Convert normal Decimal numbers to BCD (Binary-Coded Decimal)
uint8_t ppl_convertDecToBCD(uint8_t decimal_value) {
    return ( (decimal_value / 10 * 16) + (decimal_value % 10));
}