

#include "MOTOR_PID.h"

uint16_t desired_speed,actual_speed ;

void set_desired_speed(uint16_t speed_in_m_hr){


desired_speed= speed_in_m_hr;
                         
  
	                           
}


void PID_System(void){
	uint16_t current_RPM[2],current_error[2],de[2];
	static uint16_t last_error[2],ie[2]={0,0},desired_pwm,desired_RPM,speed=0,current_speed[2] ;

	/*
	 checks if the desired pwm has changed
	 changes last_error to start new PID calculations
   */
 if(speed!=desired_speed) {
    speed=desired_speed;
	  desired_RPM=(desired_speed*100)/(diameter*pi*60); // convert motor0 speed to RPM
    desired_pwm=(desired_RPM+b)/k ;  
    last_error[0]=desired_pwm;
	  last_error[1]=desired_pwm;
}
	
  get_RPM(current_RPM);
/*
calculate current speed in m/hr
*/
  current_speed[0]=(current_RPM[0]*pi*60*diameter)/(100);
  current_speed[1]=(current_RPM[1]*pi*60*diameter)/(100);
  set_Actual_Speed(current_speed);

  current_error[0]=desired_pwm-((current_RPM[0]+b)/k);
  current_error[1]=desired_pwm-((current_RPM[1]+b)/k);

  de[0]=last_error[0]-current_error[0] ;
	de[1]=last_error[1]-current_error[1] ;
	ie[0]=ie[0]+current_error[0];
  ie[1]=ie[1]+current_error[1];
	last_error[0]=current_error[0];
	last_error[1]=current_error[1];

	current_error[0]=(uint16_t)(Kp*current_error[0]+Ki*ie[0]+Kd*de[0]);
	current_error[1]=(uint16_t)(Kp*current_error[1]+Ki*ie[1]+Kd*de[1]);
	
	Motor_PWM_Speed_Control(current_error[0],current_error[1]);
  
}

void set_Actual_Speed(uint16_t* act_speed){
if(act_speed[0]>=act_speed[1]) actual_speed=act_speed[0];
if(act_speed[1]>=act_speed[0]) actual_speed=act_speed[1];
}


uint16_t get_Actual_Speed(void){

	return actual_speed ;
}

