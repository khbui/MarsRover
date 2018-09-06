/**
 * @file IRSensor.h
 * @brief This is the IR sensor library file (Another version)
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 * */
#ifndef IRSENSOR_H_
#define IRSENSOR_H_
#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include <math.h.>


//this will initialize our sensor
void IR_sensor_init(void);
int IR_get_distance_quantized();
int IR_get_distance_cm();
int IR_quantized2cm(int quantized);


#endif /* IRSENSOR_H_ */
