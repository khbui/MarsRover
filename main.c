/**
 * @file main.c
 * @brief Main function to start the program
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "lcd.h"
#include "Timer.h"
#include "adc.h"
#include "ping.h"
#include "uart.h"
#include "servo.h"
#include "open_interface.h"
#include "movement.h"
#include "IRSensor.h"
#include "sonar.h"

// bot 25
#define PI 3.14159265

struct {//holds data about detected objects
    int right_edge;
    int left_edge;
    int center;
    int distance;
    int angular_width;
    int linear_width;
}object[20];

int main(){
    //Declaration and initialization
    int i;
    int ping_dist[181];
    int adc_dist[181];
    int degree = 0;
    int obj_count = 0; // count objects
    int threshold = 90; // some value, not sure yet -> in lab9-intro-lecture
//    int width_threshold = 0;
//    int pulse_threshold = 50;// ignore values greater than 50 from pulse
    char temp;
//    sonar_init();
    //initialize registers
    lcd_init();
    ADC_init();
//    IR_sensor_init();
    servo_init();
    uart_init();
    ping_init();
//    sonar_init();
    lcd_printf("Connecting...");
//WiFi_start("12341234");
    IntRegister(INT_TIMER3B, TIMER3B_Handler);
        IntMasterEnable();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    oi_setWheels(0, 0);


    while(1){

       temp = uart_receive();

       lcd_printf("Receive:%c",temp);

        switch(temp) {
			/*Scan objects*/
            case 's':
            {
                //Scanning process                                
				for(i=0;i<=180;i++)                   
				{
					ping_dist[i] = ping_getDistance();
                    uint32_t value= ADC_read(10); // ir sensor
                    int distance = 105756*pow(value,-1.16);
					adc_dist[i] = distance;
					move_servo(++degree);
				}
				degree=0;
                //Counting object
                for(i=0; i<=180; i++){//finds edges
                    if( (adc_dist[i] < threshold && ping_dist[i] < threshold) && (i==0 || (adc_dist[i-1] >= threshold || ping_dist[i-1] >= threshold)) )// runs on object right edge
                        object[obj_count].right_edge = i;
                    if( (((adc_dist[i] > threshold) || (ping_dist[i] > threshold))&& (i!=0) && ((adc_dist[i-1] < threshold) && (ping_dist[i-1] < threshold))) || ((adc_dist[i] < threshold) && (ping_dist[i] < threshold)&& (i==180)) ){//runs on object left edge
                        object[obj_count].left_edge = i;
                        // get ping distance
//                      object[obj_count].distance = ping_dist[object[obj_count].right_edge+(object[obj_count].left_edge - object[obj_count].right_edge)/2];
                        // below is the calculation for width threshold. if less than this value and object is there. could be small or large
//                      width_threshold = 375.65 * pow(object[obj_count].distance,-.711);// 4 is the wiggle room
                        if((object[obj_count].left_edge - object[obj_count].right_edge) > 6) {//accepts object if less than width_thresh- wiggle room
//                                object[obj_count].center = object[obj_count].right_edge+(object[obj_count].left_edge - object[obj_count].right_edge)/2;// this is the center angle of object
                            obj_count++;//moves to collecting info for next object
                        }
                    }					
                }
                int smallest = 0;
                //Update all information
				for(i = 0; i < obj_count; i++){
					object[i].angular_width = object[i].left_edge - object[i].right_edge;//finds object angular width
					if(object[i].angular_width<object[smallest].angular_width){
						smallest = i;
						}
						object[i].center = object[i].right_edge + 0.5*object[i].angular_width;//finds object center
						object[i].distance = ping_dist[object[i].center];//find's object's distance
						//                                   int left_temp = ping_dist[ object[i].left_edge];
//                                    int right_temp = ping_dist[ object[i].right_edge];
                        double w = sqrt(2*pow(object[i].distance,2)-2*object[i].distance*object[i].distance*cos(object[i].angular_width *PI/180));
						object[i].linear_width = (int)w;
						
                }
                lcd_printf("No Objs: %d\nSmallest: %d\nDistance: %d\nWidth: %d",obj_count,smallest+1,object[smallest].distance,object[smallest].linear_width);
				move_servo(object[smallest].center);// the smallest radial width

                for(i = 0; i < obj_count; i++){// send angle
                    uart_sendChar(object[i].center);
                }

                for(i = 0; i < obj_count; i++){// send distance
                    uart_sendChar(object[i].distance);
                }
                obj_count=0;
                break;
            }
			/*Move forward*/
            case 'a':
            {
                char cd = 0;
                while(cd == 0) {
                    cd = uart_receive();
                }
                lcd_printf("entered case: %c" ,cd);
                int value = (((int) cd)-48) * 100;
                temp = move_forward(sensor_data, value);
                uart_sendChar( temp);
                break;
            }
			/*Move backward*/
            case 'b':
            {
                char cd = 0;
                while(cd == 0) {
                    cd = uart_receive();
                }
                int value = (((int) cd)-48) * 100;
                move_backward(sensor_data, value);
                break;
            }
			/*Turn left*/
            case 'l':
            {
                char cd = 0;
                while(cd == 0) {
                    cd = uart_receive();
                }
                int value = (((int) cd)-48) * 10;
                turn_counterclockwise(sensor_data, value);
                break;
            }
			/*Turn right*/
            case 'r':
            {
                char cd = 0;
                while(cd == 0) {
                    cd = uart_receive();
                }
                int value = (((int) cd)-48) * 10;
                turn_clockwise(sensor_data,value);
                break;
            }
			/*Play song and flash power light*/
            case 'p':
            {
                unsigned char names[27] = {48,53,57,60,65,21+48,24+48,21+48,1+48,5+48,8+48,13+48,17+48,20+48,25+48,20+48,3+48,6+48,12+48,15+48,19+48,22+48,27+48,27+48,27+48,27+48,29+48};
                unsigned char duration[27] = {10,10,10,10,10,10,30,30,10,10,10,10,10,10,30,30,10,10,10,10,10,10,30,10,10,10,50};
                oi_loadSong(1, 28, names, duration );
                oi_play_song(1);
                for( i = 0; i < 10; i++){
					oi_setLeds(1, 0, 255, 255);
					timer_waitMillis(250);
					oi_setLeds(1, 0, 0, 255);
					timer_waitMillis(250);
				}
                break;
            }
        }
    }
}

