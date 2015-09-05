#include <xc.h>         /* XC8 General Include File */
#include "user.h"
#include "ppl_xlcd.h"
#include <adc.h>

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/
/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void){
    /* TODO Initialize User Ports/Peripherals/Project here */
    
    /* Setup analog functionality and port direction */
    /* Initialize peripherals */
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    /* Enable interrupts */
    
    init_ADC();                    //Call the Initialize ADC function    
    init_XLCD();                    //Call the Initialize LCD display function    
}

void init_XLCD(void){              //Initialize LCD display
    OpenXLCD(FOUR_BIT & LINES_5X7);  //configure LCD in 4-bit Data Interface mode
                                   //and 5x7 characters, multiple line display
    
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command    
    WriteCmdXLCD(0x06);            // move cursor right, don?t shift display
    while(BusyXLCD());             //Check if the LCD controller is not busy before writing any command
    WriteCmdXLCD(0x0C);            //turn display on without cursor
 }

void init_ADC(void){
    unsigned char channel=0x00, config1=0x00, config2=0x00, config3=0x00, portconfig=0x00;
    
    //-- clear adc interrupt and turn off adc if in case was on prerviously---
    CloseADC();
    
    //--initialize adc---
    /**** ADC configured for:
    * FOSC/2 as conversion clock
    * Result is right justified
    * Aquisition time of 20 AD
    * Channel 0 for sampling
    * ADC interrupt on
    * ADC reference voltage from VDD & VSS
    */
    config1 = ADC_FOSC_2 | ADC_RIGHT_JUST | ADC_2_TAD;
    config2 = ADC_CH0 | ADC_INT_ON | ADC_REF_VDD_VSS;
    portconfig = ADC_15ANA;
    
    //OpenADC(config1, config2, portconfig);
    OpenADC(ADC_FOSC_2 & ADC_RIGHT_JUST & ADC_20_TAD, ADC_CH0 & ADC_INT_ON & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, ADC_0ANA);
    //---initialize the adc interrupt and enable them---
    ADC_INT_ENABLE();    
}