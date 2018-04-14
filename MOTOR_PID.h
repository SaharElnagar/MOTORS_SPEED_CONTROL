
#ifndef _PID_H_
#define _PID_H_
#include "MOTOR_PID.h"
#include "Motor_PWM.h"
#include "Motor_ENCODER.h"
#define   k   0.45
#define   b    85
#define   Kd  -0.01046
#define   Ki   504.4347
#define   Kp   3.8774






void set_speed(uint16_t* speed_in_m_hr);
void set_Actual_Speed(uint16_t* act_speed);
void PID_System(void);
uint16_t get_Actual_Speed(void);

#endif  //_PID_H_