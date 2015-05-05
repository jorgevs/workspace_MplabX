#include "ppl_utils.h"

void ppl_delay(unsigned long x) {
    int numCycles = x / 100;
    for (int i = 0; i < numCycles; i++) {
        _delay(100);
    }
}

// Convert BCD (Binary-Coded Decimal) to normal Decimal numbers
/*uint8_t ppl_bcdToDec(uint8_t bcd_value) {
    //return ((bcd_value / 16 * 10) + (bcd_value % 16));
    //return (bcd_value - 6 * (bcd_value >> 4));
    return ((bcd_value >> 4) * 10 + (bcd_value & 0x0F));
}*/

// Convert normal Decimal numbers to BCD (Binary-Coded Decimal)
/*uint8_t ppl_decToBcd(uint8_t decimal_value) {
    //return ((decimal_value / 10 * 16) + (decimal_value % 10));
    //return (decimal_value + 6 * (decimal_value / 10));
    return (((decimal_value / 10) << 4) + (decimal_value % 10));
}*/

// Convert binary coded decimal to normal decimal numbers
uint8_t ppl_bcdToDec(uint8_t binary_value){
  uint8_t temp;
  uint8_t retval;

  temp = binary_value;
  retval = 0;
  while(1){
    if(temp >= 10){
      temp -= 10;
      retval += 0x10;
    }else{
      retval += temp;
      break;
    }
  }
  return(retval);
}

// Convert normal decimal numbers to binary coded decimal
uint8_t ppl_decToBcd(uint8_t bcd_value){
  uint8_t temp;

  temp = bcd_value;
  temp >>= 1;
  temp &= 0x78;
  return(temp + (temp >> 2) + (bcd_value & 0x0f));
}