///*
// * sonar.c
// *
// *  Created on: Mar 18, 2018
// *      Author: mjruden
// */
//
//#include <sonar.h>
//#include "driverlib/interrupt.h"
//#include "math.h"
//
//volatile int value_Rise = 0;// these will be changed by the ISR
//volatile int value_Fall = 0;
//volatile int track = 0;
//volatile int state = 0;
//volatile int width = 0;
//volatile int oldvalue = 0;
//
//
//    void TIMER3B_Handler() {
//
//        // this was really important otherwise to many false edges are captured
//        if( state == 2){
//
//            TIMER3_ICR_R |= 0b010000000000;
//            return;
//        }
//
//        int value = TIMER3_TBR_R;// get value from reg quickly
//
//        // Stores the old value of the register
//        oldvalue = value;
//
//        if( track == 0){
//
//            value_Rise = value;// get value
//            state = 1;// waiting for falling edge
//
//        }
//
//        else if (track == 1){
//
//            value_Fall = value;
//            state = 2;// falling edge recieved waiting for pulse
//
//        }
//
//        track = abs(track - 1); //toggle
//        TIMER3_ICR_R |= 0b010000000000;// clears the timeout interrupt flag, by writting tenth bit to one, we can clear at the beginning also
//
//    }
//
//
//    void sonar_init() {
//
//        SYSCTL_RCGCTIMER_R = 0b001000;
//        TIMER3_CTL_R &=  0b111011111111;// disable enable bit before making changes
//        TIMER3_CTL_R |= 0b110000000000;// set to trigger on rise and fall
//
//        // Input edge count mode, 16bit mode
//        TIMER3_CFG_R |= 0x4;
//
//
//        TIMER3_TBMR_R |= 0b0100;// set to edge time mode
//        TIMER3_TBMR_R |= 0x3;  // Set to capture mode
//
//        // Set timer prescaler and load init value to max
//        TIMER3_TBPR_R = 0xFF;
//        TIMER3_TBILR_R = 0xFFFF;
//
//        // Enable Timer B
//        TIMER3_IMR_R |= 0x400;
//
//        // TIMER3_MIS_R : The 10th bit shows the status of unmasked interrupt in timer B.
//        // TIMER3_ICR_R : The 10th bit is the interrupt flag for timer B. Write 1 to clear
//        // insert NVIC enable
//        NVIC_EN1_R = 0b10000;// enable nvic register en1 bit 4
//        IntRegister(INT_TIMER3B, TIMER3B_Handler);
//        IntMasterEnable();// enable interrupts
//
//        // GPIO init
//        SYSCTL_RCGCGPIO_R = 0b000010;
//        // enable digital functionality of port B
//        GPIO_PORTB_DEN_R = 0xFF;
//        GPIO_PORTB_PCTL_R |= 0x7000;// set alt function mux
//
//        TIMER3_CTL_R |= 0b000100000000;// re enable timer
//
//    }
//
//    void sonar_send_pulse() {
//
//        TIMER3_IMR_R &= ~(0x400);// disable
//
//        GPIO_PORTB_AFSEL_R &= 0b11110111;// clear 3rd bit
//
//        // set PB3 as output
//        GPIO_PORTB_DIR_R |= 0b00001000;
//
//        // set PB3 to high
//        GPIO_PORTB_DATA_R |= 0b00001000;
//
//        // wait at least 5 microseconds based on data sheet
//        timer_waitMicros(5);
//
//        // set PB3 to low
//        GPIO_PORTB_DATA_R &= ~(0b00001000);
//
//        // set PB3 as input
//        GPIO_PORTB_DIR_R &= ~(0b00001000);
//
//        GPIO_PORTB_AFSEL_R |= 0x08;
//
//        TIMER3_IMR_R |= 0x400;// re enable timer
//
//        state = 0;// waiting for rising edge, reset to look for ints
//
//    }
//
//    /**
//     * Detects the edge of from the sonar
//     *
//     * @return
//     *      The distance in delta form
//     */
//    int sonar_recieve_edge() {
//
//        // Waits for the positive and negative edge to be received
//        while (state != 2){
//            // wait
//        }
//
//        if ( TIMER3_TBR_R < oldvalue){
//
//            // Increase the oveflow count
//            overflow++;
//
//            return (((value_Fall + (pow(2.0,24.0)-1)-value_Rise))/2);
//
//        }
//
//        return ((value_Rise - value_Fall));
//
//    }
//
//    /*
//     * Sounds out a pulse from the sonar and returns the distance
//     * in delta form.
//     *
//     * @return
//     *      The distance in delta form
//     */
//    int sonar_distance_delta() {
//
//        // Send a pulse using sonar
//        sonar_send_pulse();
//
//        int delta = sonar_recieve_edge();
//
//        // Get the rising edge from the bounce back
//        return delta;
//
//    }
//
//    /**
//     * Converts the delta between edges into centimeters.
//     * Used for flat surfaces
//     *
//     * @param
//     *      Delta to convert to centimeters.
//     * @return
//     *      Delta in centimeters.
//     */
//    int sonar_delta2cmFlat(int delta) {
//
//        return (int) 34300.0 * (delta*1.0) * (1/(16*pow(10.0,6.0)));
//
//    }
//
//    /**
//     * Converts the delta between edges into centimeters.
//     * Used for round objects
//     *
//     * @param
//     *      Delta to convert to centimeters.
//     * @return
//     *      Delta in centimeters.
//     */
//    int sonar_delta2cmRound(int delta) {
//        return (int) ((.0011*(delta*1.0))-6.909);
//    }
//
//    /**
//     * Sends out a pulse and waits for the return. Calculates out the time required for the signal to travel back
//     * and outputs the distance in centimeters.
//     *
//     * @return
//     *      Distance in centimeters.
//     */
//    int sonar_distance_cm() {
//
//        int delta = sonar_distance_delta();
//
//        // Calculates the distance in centimeters and returns the value
//        return sonar_delta2cmRound(delta);
//
//    }
//
