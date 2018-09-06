/**
 * @file sonar.h
 * @brief This is sonar sensor library file
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 * */

#ifndef SONAR_H_
#define SONAR_H_
#include <stdint.h>
#include <Timer.h>
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"
#include "math.h"

int overflow;

void TIMER3B_Handler();
void sonar_init();
void sonar_send_pulse();
int sonar_recieve_edge();
int sonar_distance_delta();
int sonar_sonar_delta2cmFlat(int delta);
int sonar_delta2cmRound(int delta);
int sonar_distance_cm();





#endif /* SONAR_H_ */
