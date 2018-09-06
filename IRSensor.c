/**
 * @file IRSensor.c
 * @brief This is source code of IR sensor
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 * */

#include <IRSensor.h>

/**
* Initialize IR sensor on robot.
* @author Team B4  S2018 ISU
* @date 4/25/2018
*/
    void IR_sensor_init(){

        // GPIO initialization , SS0 , ADC0
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
        SYSCTL_RCGCADC_R |= 0x1;
        GPIO_PORTB_AFSEL_R |= 0x01;
        GPIO_PORTB_DEN_R &= 0b11111110;
        GPIO_PORTB_AMSEL_R |= 0x01;
        GPIO_PORTB_ADCCTL_R = 0x00;

        ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
        ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;
        ADC0_SSMUX0_R |= 0x000A;
        ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);
        ADC0_SAC_R |= ADC_SAC_AVG_16X;// the lab report said to set this to 16
        ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

    }

/**
* Gets the quantized value from the IR sensor 
* @author Team B4  S2018 ISU
* @date 4/25/2018
* @return The distance in quantized value
*/
    int IR_get_distance_quantized() {

        //initiate SS0 conversion
        ADC0_PSSI_R=ADC_PSSI_SS0;

        // wait for ADC conversion to be complete
        while( (ADC0_RIS_R & ADC_RIS_INR0) == 0){
            // wait
        }

        // grab result
        int quantized = ADC0_SSFIFO0_R;

        ADC0_SSFIFO0_R = 0;

        return quantized;

    }

    /**
     * Gets the quantized value from the IR sensor, does the calculation to convert
     * the value from quantized to centimeters.
     * Calibrated for CyBot 2
     * @author Team B4  S2018 ISU
	 * @date 4/25/2018
     * @return
     *      The distance in centimeters
     */
    int IR_get_distance_cm() {

        // Gets the quantized value from sensor
        int quantized_value = IR_get_distance_quantized();

        // COnverts the quantized value to CM and returns
        return  IR_quantized2cm(quantized_value);

    }

    /**
     * Converts the quantized value to the centimeters.
     * Calibrated for CyBot 2
     * @author Team B4  S2018 ISU
	 * @date 4/25/2018
     * @return
     *      quantized value in centimeters
     */
    int IR_quantized2cm(int quantized) {
        return (int) 156574*( pow(quantized, -1.227) );
    }


