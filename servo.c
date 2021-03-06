/**
 * @file servo.c
 * @brief This is code to control the robot's servo
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 */
#include "servo.h"
const unsigned int period_length = 0x4E200;//holds TOP value
unsigned int match=0x48c10;//holds match value
unsigned int counter=0x48c10;
//48ff8

/**
* Initialize servo motor
* @author Team B4  S2018 ISU
* @date 4/25/2018
*/
 void servo_init(){
     SYSCTL_RCGCGPIO_R |= 0x2; //enables clock to port B
     GPIO_PORTB_DEN_R |= 0x20; //sets PB5 to digital
     GPIO_PORTB_DIR_R |= 0x20; //sets PB5 to output
     GPIO_PORTB_AFSEL_R |= 0x20; //enables alternate function on PB
     GPIO_PORTB_PCTL_R |=  0x700000; //sets PB5 to use timer1

     SYSCTL_RCGCTIMER_R |= 0x2; //enables clock to timer1
     TIMER1_CTL_R &= ~0x100; //disables timer 1
     TIMER1_CFG_R |= 0x4; // sets to use as 16-bit timer
     TIMER1_TBMR_R |= 0xA; //set to periodic
     TIMER1_TBPR_R = period_length >> 16; //sets upper 8 bits of TOP value
     TIMER1_TBILR_R = period_length & 0xFFFF; //sets lower 16 bits of TOP value
     TIMER1_TBPMR_R = match >> 16; //sets upper 8 bits of match value 0x4 => 90 degrees
     TIMER1_TBMATCHR_R = match & 0xFFFF; //sets lower 16 bits of match value 0x8440 => 90 degrees
     //set clock to countdown?
     TIMER1_CTL_R |= 0x100; //enables timer 1B
 }

/**
*
* Turns the servo motor a specific degrees
* @author Team B4  S2018 ISU
* @date 4/25/2018
* @param degrees the integer value between 0-180
* @return a position 
*/
 int move_servo(int degree)
 {
     unsigned long pulse_width;
     pulse_width = degree*166+7000;
     TIMER1_CTL_R &= ~0x100; //disables timer 1B
     counter = period_length-pulse_width;
     TIMER1_TBPMR_R = (period_length-pulse_width) >> 16; //sets upper 8 bits of match value
     TIMER1_TBMATCHR_R = (period_length-pulse_width) & 0xFFFF; //sets lower 16 bits of match value
     TIMER1_CTL_R |= 0x100; //enables timer 1B
     timer_waitMillis(((1.5/180)*degree) + 70);
     return 1;
 }
 
 /**
*
* gets the number of countes
* @author Team B4  S2018 ISU
* @date 4/25/2018
* @return an int number  
*/
 unsigned int getCounter()
 {
     return counter;
 }

