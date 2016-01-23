#include "ppl_utils.h"
#include "ppl_sound.h"

void do_delay(int ms_delay, int num_ms, int us_delay, int num_us)  {
 int i;

 for(i=0;i<num_ms;i++)
  ppl_delay_ms(250);
  ppl_delay_ms(ms_delay);
 for(i=0;i<num_us;i++)
  ppl_delay_us(250);
  ppl_delay_us(us_delay);
}


void generate_tone(long frequency, long duration) {
   long total_delay_time;                      // in microseconds
   long total_ms_delay_time, total_us_delay_time;
   int num_us_delays, num_ms_delays, ms_delay_time, us_delay_time;
   long num_periods;

   total_delay_time = (1000000/frequency)/2-10; // calculate total delay time (10 for error)

   total_ms_delay_time = total_delay_time/1000; // total delay time of ms
   num_ms_delays = total_ms_delay_time/250;     // number of 250ms delays needed
   ms_delay_time = total_ms_delay_time%250;     // left over ms delay time needed

   total_us_delay_time = total_delay_time%1000; // total delay time of us (ms already acounted for)
   num_us_delays = total_us_delay_time/250;     // number of 250us delays needed
   us_delay_time = total_us_delay_time%250;     // left over us delay time needed

   num_periods = ((long)duration*1000)/(1000000/frequency);

   while((num_periods--) != 0){
      do_delay(ms_delay_time, num_ms_delays, us_delay_time, num_us_delays);
      LATAbits.LA2 = HIGH;
      //output_high(TONE_PIN);
      do_delay(ms_delay_time, num_ms_delays, us_delay_time, num_us_delays);
      //output_low(TONE_PIN);
      LATAbits.LA2 = LOW;
   }
}