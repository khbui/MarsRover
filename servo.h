/**
 * @file servo.h
 * @brief This is the servo library file
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 * */
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "lcd.h"

void servo_init();
int move_servo(int degree);
unsigned int getCounter();
