#include <msp430.h>
#include "libTimer.h"
#include "Switch.h"
#include "buzzer.h"
#include "lcddraw.h"
#include "lcdutils.h"


/*
#define LED_RED BIT0
#define LED_GREEN BIT6
#define LEDS (BIT0 | BIT6)

#define BSW BIT3
#define TSW1 BIT0
#define TSW2 BIT1
#define TSW3 BIT2
#define TSW4 BIT3
#define TOP_SWITCHS (TSW1 | TSW2 | TSW3 | TSW4)
*/


//extern int set_one;
//extern int set_two;
extern int pattern;
extern int led;



void switch_init()
{
  P1REN |= BSW;
  P1IE |= BSW;
  P1OUT |= BSW;
  P1DIR &= ~BSW;

  P2REN |= TOP_SWITCHES;
  P2IE |= TOP_SWITCHES;
  P2OUT |= TOP_SWITCHES;
  P2DIR &= ~TOP_SWITCHES;

}
void led_init()
{
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

#define PATTERN1 15
#define PATTERN2 30
#define PATTERN3 50
#define PATTERN4 100
#define PATTERN5 150

void Light_pattern(int num)
{
  switch(num)
  {
  case 0:
    pattern = PATTERN1;
    break;
  case 1:
    pattern = PATTERN2;
    break;
  case 2:
    pattern = PATTERN3;
    break;
  case 3:
    pattern = PATTERN4;
    break;
  default :
    pattern = PATTERN5;
    break;
  }
}
     
      
void switch_interrupt_handler()
{
  char p1val= P1IN;
  P1IES |= (p1val & BSW);
  P1IES &= (p1val | BSW);


  char p2val =P2IN;
  P2IES |= (p2val & TOP_SWITCHES);
  P2IES &= (p2val | TOP_SWITCHES);
}


void __interrupt_vec(PORT2_VECTOR)Port_2()
{
  if(P2IFG & TSW1)
  {
    P2IFG &= ~TSW1;
    Light_pattern(1);
    set_one();
    led=0;
    //switch_interrupt_handler();
  }
  else if(P2IFG & TSW2)
  {
    P2IFG &= ~TSW2;
    Light_pattern(2);
    led = 1;
    //switch_interrupt_handler();
  }
  else if(P2IFG & TSW3)
  {
    P2IFG &= ~TSW3;
    Light_pattern(3);
    set_three();
    led = 0;
    //switch_interrupt_handler();
  }
  else if(P2IFG & TSW4)
  {
    P2IFG &= ~TSW4;
    Light_pattern(4);
    set_two();
    led= 1;
    //switch_interrupt_handler();
  }
  //buzzer_set_period(0);

}

void __interrupt_vec(PORT1_VECTOR)Port_1()
{
  if(P1IFG & BSW)
  {
    P1IFG &= ~BSW;
    Light_pattern(0);
    led = 1;
    switch_interrupt_handler();
  }
}

void toggle_green()
{
  if(P1OUT & LED_GREEN)
    P1OUT &= ~LED_GREEN;
  else
    P1OUT |= LED_GREEN;
}
void toggle_red()
{
  if(P1OUT & LED_RED)
    redcontrol(0);
  else
    redcontrol(1);
}




  
  
  



  

