#include <xc.h>

//#define set_port_kbd PORTB // Change if port is different
#define row1port LATBbits.LATB0
#define row2port LATBbits.LATB1
#define row3port LATBbits.LATB2
#define row4port LATBbits.LATB3
#define col1port PORTBbits.RB4
#define col2port PORTBbits.RB5
#define col3port PORTBbits.RB6
//#define col4port PORTBbits.RB7   //if a 4x4 keypad is used

char const keyPadMatrix[] =
{
    '1','2','3',
    '4','5','6',
    '7','8','9',
    '*','0','#',
    0xFF
};
char key, old_key;

int kbd_getc();
