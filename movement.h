/**
 * @file movement.h
 * @brief This is library file for robot's movement
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 */
#include "open_interface.h"
#include <stdio.h>


char move_forward(oi_t *sensor, int millimeters);
void move_backward(oi_t *sensor, int millimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_counterclockwise(oi_t *sensor, int degrees);
