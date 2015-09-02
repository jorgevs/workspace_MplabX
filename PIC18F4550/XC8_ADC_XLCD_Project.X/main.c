#include <xc.h>        /* XC8 General Include File */
#include <stdint.h>    /* For uint8_t definition */
#include <stdbool.h>   /* For true/false definition */

#include "system.h"    /* System funct/params, like osc/peripheral config */
#include "user.h"      /* User funct/params, such as InitApp */
#include "ppl_utils.h"

#include <adc.h>
#include <stdio.h>

// The purpose of this library is to use the portD for the LCD instead of PortB 
// as specified in the normal <xlcd.h> library
#include "ppl_xlcd.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

unsigned int ADCResult=0;
float voltage=0;
char s[10];

void main(void){
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    while(true){
        //---sample and convert----
        for(int i=0; i<16 ;i++){
            ConvertADC();
            while(BusyADC());
            ADCResult += (unsigned int)ReadADC();
        }
        ADCResult /= 16;
        voltage = (ADCResult * 5.0) / 1024; // convert ADC count into voltage
        
        
        // Clear display
        WriteCmdXLCD(0x01);
        // Shift cursor to beginning of first line
        SetDDRamAddr(0x00);
        putrsXLCD("ADC Project");

        // Shift cursor to beginning of second line
        SetDDRamAddr(0x40);
        putrsXLCD("voltage: ");
        sprintf(s, "%f", voltage);
        putrsXLCD(s);
        
        ppl_delay_ms(250);
    }
    CloseADC(); //turn off ADC

}