/**
 * @file ping.h
 * @brief This is ping sensor library file
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 * */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "Timer.h"



#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80

volatile enum {RISE, FALL, DONE} state;
volatile uint32_t risingEdge;
volatile uint32_t fallingEdge;
volatile uint32_t pulseLength;


void TIMER3B_Handler(void);
void ping_init();
void send_pulse();
float ping_getDistance();
