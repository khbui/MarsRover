/**
 * @file uart.h
 * @brief This is the uart communication library file
 * @author Team B4  S2018 ISU
 * @date 4/25/2018
 */

#ifndef UART_H_
#define UART_H_

#include "Timer.h"
#include "WiFi.h"
#include <inc/tm4c123gh6pm.h>

void uart_init(void);
void uart_sendChar(char data);
int uart_receive(void);
void uart_sendStr(const char *data);

#endif /* UART_H_ */
