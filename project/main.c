#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "Switch.h"
#include "lcddraw.h"
#include "lcdutils.h"

int pattern=0;
int led=0;

int main(){
  configureClocks();
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();
  //buzzer_set_period(1000);
  or_sr(0x18);
}
int play_set_one = 0 ;
int play_set_two = 0 ;
int led_sec = 0;

void __interrupt_vec(WDT_VECTOR) WDT()
{

  led_sec++;
  if( led_sec >= pattern)
   {
     led_sec=0;
     if(led)
       toggle_green();
     else
       toggle_red();
   }
}
void set_one()
{
  buzzer_set_period(1500);
  fillRectangle(30,30,60,60, COLOR_RED);
  //  buzzer_set_period(50);
  // buzzer_set_period(0);
}
void set_two()
{
  buzzer_set_period(500);
  //buzzer_set_period(50);
  //buzzer_set_period(100);
}
void set_three()
{
  clearScreen(COLOR_BLACK);
  buzzer_set_period(0);

}

  

     
  


  
