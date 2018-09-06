/**
 * @file movement.c
 * @brief This is code to control the robot's movement
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 */

#include "movement.h"
#include "uart.h"
#include <stdio.h>

/**
*Moves the robot forward a specified value of centimeters
* While moving it checks for cliff edge sensors, wheel drop sensors,
* line detector sensors, and bumper sensors, responding accordingly for each occurrence.
* @author Team B4  S2018 ISU
* @date 4/25/2018
* @param *sensor  oi_t struct pointer
* @param millimeters travel distance
* @return error code based on what was happening when the robot stopped moving.
*/


char move_forward(oi_t *sensor, int millimeters){
    int sum = 0;
    oi_setWheels(140,150);
    while (sum < millimeters) {
        oi_update(sensor);
        sum += sensor->distance;

        /*Hit objects*/
        if(sensor->bumpLeft){
            oi_setWheels(0,0);
            uart_sendChar(sum/10);
            return '1';
        }
        if(sensor->bumpRight){
            oi_setWheels(0,0);
            uart_sendChar(sum/10);
            return '2';
        }
        /*Border detect*/

        if(sensor->cliffFrontLeftSignal > 2650) //front left line detected
        {
            oi_setWheels(0,0);
            uart_sendChar(sum/10);
            return '3';
        }
        //front right line detected
        if(sensor->cliffFrontRightSignal > 2500)
        {

            oi_setWheels(0,0);
            uart_sendChar(sum/10);
            return '4';
        }
        //left line detected
        if(sensor->cliffLeftSignal > 2550)
        {

            oi_setWheels(0,0);
            uart_sendChar(sum/10);
            return '5';
        }
        //right line detected
       if(sensor->cliffRightSignal > 2550)
       {
           oi_setWheels(0,0);
           uart_sendChar(sum/10);
           return '6';
       }

       /*Cliff detect*/

       // cliff detected front left
       if (sensor->cliffFrontLeftSignal< 1500)
       {
           oi_setWheels(0,0);
           uart_sendChar(sum/10);
           return '7';
       }
       //cliff front right detected
       if (sensor->cliffFrontRightSignal < 1510)
       {
           oi_setWheels(0,0);
           uart_sendChar(sum/10);
           return '8';
       }
       // cliff detected left
       if (sensor->cliffLeftSignal < 1500)
       {
           oi_setWheels(0,0);
           uart_sendChar(sum/10);
           return '9';
       }
       //cliff detected right
       if (sensor->cliffRightSignal < 1500)
       {
           oi_setWheels(0,0);
           uart_sendChar(sum/10);
           return 'A';
       }

    }
    oi_setWheels(0, 0);
    return '0';
	}
}

/**
 * Moves robot backward a distance   to update and check values from the oi_t iRobot Create platform
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 * @param *sensor  oi_t struct pointer
 * @param millimeters travel distance
*/
void move_backward(oi_t *sensor, int millimeters){// add flags
       int sum = millimeters;
       oi_setWheels(-100, -100); // move backward; full speed
       while (sum>0) {
           oi_update(sensor);
           sum +=   sensor->distance;
       }
       oi_setWheels(0, 0); // stop
       uart_sendChar('0');
}
/**
 * Turn robot right an angle
 * @author Team B4  S2018 ISU
 *@date 4/25/2018
 *@param *sensor  oi_t struct pointer
* @param degree angle value
*/
void turn_clockwise(oi_t *sensor, int degrees){// right
    int angle = 0;
//    int cor = 3.575 * degrees /10;

    oi_setWheels(-50,50);//(r,l)

    while(angle < degrees){
  // bot two downstairs timer value = 350
  // bot 19 downstairs timer value = 350

        timer_waitMillis(350); // the time it takes to go ten degrees
        angle += 10;
    }

    oi_setWheels(0, 0);
    uart_sendChar('0');

}
/**
 *  Turn robot left an angle
 *  @author Team B4  S2018 ISU
 * @date 4/25/2018
* @param *sensor  oi_t struct pointer
* @param degree angle value
*/
void turn_counterclockwise(oi_t *sensor, int degrees){
    int angle = 0;

      oi_setWheels(50,-50);//(r,l)
      while(angle < degrees ){//returns negative degrees?
          timer_waitMillis(350); // the time it takes to go ten degrees
          angle += 10;
      }

      oi_setWheels(0, 0);
      uart_sendChar('0');
}
