/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/
/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/4

/* ppl_utils.h uses this constant */
#define _XTAL_FREQ      8000000

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
