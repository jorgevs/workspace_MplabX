#include <xc.h>
#include "ppl_utils.h"
#include "ppl_kbd.h"

/********************************************************************
*       Function Name:  BusyXLCD                                    *
*       Return Value:   char: busy status of LCD controller         *
*       Parameters:     void                                        *
*       Description:    This routine reads the busy status of the   *
*                       Hitachi HD44780 LCD controller.             *
********************************************************************/

int kbd_getc(){
    char key = 0, row;
    for( row = 0b00000001; row < 0b00010000; row <<= 1 ){
        {   // turn on row output
            row1port = (row & 0x0001)>>0;
            row2port = (row & 0x0002)>>1;
            row3port = (row & 0x0004)>>2;
            row4port = (row & 0x0008)>>3;
            ppl_delay_ms(1);
        }
        // read colums - break when key press detected
        if( col1port )break;  key++;
        if( col2port )break;  key++;
        if( col3port )break;  key++;
        //if( col4port )break;  key++;
    }
    row1port = 0;
    row2port = 0;
    row3port = 0;
    row4port = 0;
    
    if (key != old_key){
      old_key = key;
      return keyPadMatrix[key];
    }else{
        return keyPadMatrix[ 0x0C ];
    }
}
/*--------------------------------------------------------------------------------*/
