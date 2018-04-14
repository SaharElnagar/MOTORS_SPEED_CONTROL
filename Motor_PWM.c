/*
 * Motor_PWM.c
 *
 *  Created on: Feb 28, 2018
 *      Author: Mohab
 */
 
 /*
 
 Wiring :   Motor1_PWM ==> PB6  , Motor2_PWM ==> PB7
 */

#include "Motor_PWM.h"


#define PWM_FREQUENCY_TEST  400



void Motor_PWM_Speed_Control(uint16_t duty0,uint16_t duty1){
	
  PWM0_0_CMPB_R=duty0-2;      // DECIDE DUTY PB7	 //M0PWM1
	PWM0_0_CMPA_R=duty1-2 ;      // DECIDE DUTY PB6 	//M0PWM0
  PWM0_0_CTL_R=0X00000001 ;  // START PWM 
  PWM0_ENABLE_R=0X00000003;  // ENABLE PWM 
	
}



void Motor_PWM_Init(void){
	                  
                            //**** Init PWM0 & PWM1 on PB6 & PB7 ****//
	int delay;
  SYSCTL_RCGCPWM_R|=0x01;               // Enable PWM Clock
	delay=SYSCTL_RCGCPWM_R;
	SYSCTL_RCGCGPIO_R|=0X02;                    //Enable the clock to PORT B
	delay=SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_LOCK_R=0X4C4F434B;
	GPIO_PORTB_CR_R|=0XC0;
	GPIO_PORTB_DIR_R|=0XC0;                // Output signal
	GPIO_PORTB_DEN_R|=0XC0;                // Enable Digital
	GPIO_PORTB_AMSEL_R&=~0XC0;             // Disable Analog
	GPIO_PORTB_AFSEL_R|=0XC0;              // Alternative Function
	GPIO_PORTB_PCTL_R&=~0XFF000000;
	GPIO_PORTB_PCTL_R|= 0X44000000;
	GPIO_PORTB_DR8R_R |=0XC0;
 	PWM0_0_CTL_R=0 ;  	                  // COUNT DOWN MODE, disable during config

	PWM0_0_GENA_R |=0XC8 ;                // LOW ON LOAD , HIGH ON CMPA
	PWM0_0_GENB_R |=0XC08 ;               // LOW ON LOAD , HIGH ON CMPB

  #ifdef SYSTEM_CLOCK_16_MHZ	  //actually  PWMDIV = 64 from motor code
	/*PWM0_0_LOAD_R=8000-1 ;                // PWM FREQUENCY= 2000 HZ
   */
	PWM0_0_LOAD_R = 125-1;

  #endif
  #ifdef	SYSTEM_CLOCK_80_MHZ
	/*PWM0_0_LOAD_R=40000-1 ;                // PWM FREQUENCY= 2000 HZ
   */
	PWM0_0_LOAD_R = 625-1;

  #endif
	
}





