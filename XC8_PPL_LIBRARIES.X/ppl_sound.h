#include <xc.h>
#include <stdint.h>        /* For uint8_t definition */

#ifndef  TONE_PIN
#define TONE_PIN  LATAbits.LA2
#endif

//            NOTE                 FREQUENCY
//                     Octave0  Octave1  Octave2  Octave3
long C_NOTE[4]  ={ 262,     523,    1047,    2093};
long Db_NOTE[4] ={ 277,     554,    1109,    2217};
long D_NOTE[4]  ={ 294,     587,    1175,    2349};
long Eb_NOTE[4] ={ 311,     622,    1245,    2489};
long E_NOTE[4]  ={ 330,     659,    1329,    2637};
long F_NOTE[4]  ={ 349,     698,    1397,    2794};
long Gb_NOTE[4] ={ 370,     740,    1480,    2960};
long G_NOTE[4]  ={ 392,     784,    1568,    3136};
long Ab_NOTE[4] ={ 415,     831,    1661,    3322};
long A_NOTE[4]  ={ 440,     880,    1760,    3520};
long Bb_NOTE[4] ={ 466,     923,    1865,    3729};
long B_NOTE[4]  ={ 494,     988,    1976,    3951};

void generate_tone(long frequency, long duration);
void do_delay(int ms_delay, int num_ms, int us_delay, int num_us);

