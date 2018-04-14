/*
 * motor_pwm.h
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */


#ifndef MOTOR_MOTOR_PWM_H_
#define MOTOR_MOTOR_PWM_H_

#include "tm4c123gh6pm.h"
#include <stdint.h>
//#define SYSTEM_CLOCK_16_MHZ
#define SYSTEM_CLOCK_80_MHZ

void Motor_PWM_Init(void);

void Motor_PWM_Speed_Control(uint16_t duty0,uint16_t duty1);

#endif /* MOTOR_MOTOR_PWM_H_ */
