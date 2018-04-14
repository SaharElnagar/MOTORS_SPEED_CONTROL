#define TARGET_IS_TM4C123_RA1
#define PART_TM4C123GH6PM
#include <stdint.h>
#include "rom.h"
#include <stdbool.h>
#include "hw_memmap.h"
#include "gpio.h"
#include "rom_map.h"
#include "sysctl.h"
#include "qei.h"
#include "MOTOR_ENCODER.h"

uint32_t speed0,speed1 ;
void QEI0_Handler(void){
  speed0=ROM_QEIVelocityGet(QEI0_BASE);    
  ROM_QEIIntClear(QEI0_BASE,QEI_INTTIMER); // clear interrupt
}
void QEI1_Handler(void){
   speed1=ROM_QEIVelocityGet(QEI1_BASE);
   ROM_QEIIntClear(QEI1_BASE,QEI_INTTIMER); //clear interrupt
}


int main(){
 Init_Speed();


}
 void get_RPM(uint16_t* RPM){
	
  
    RPM[0]=(timer_tick_freq*60*speed0)/(gear_ratio*Max_Position);  // calculate RPM for motor 0
    RPM[1]=(timer_tick_freq*60*speed1)/(gear_ratio*Max_Position);  // calculate RPM for motor 1

	
	
}
void Init_Speed(void){

  ROM_SysCtlClockSet(SYSCTL_SYSDIV_1| SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); //clock 80 MHZ
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);	                     //Run Clock on port D
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);	                     //Run clock on port C
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);	                       //Run clock on QEI0
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);	                       //Run clock on QEI1
  ROM_GPIODirModeSet(GPIO_PORTD_BASE,GPIO_PIN_6,GPIO_DIR_MODE_IN );      // PD6 input
  ROM_GPIODirModeSet(GPIO_PORTD_BASE,GPIO_PIN_7,GPIO_DIR_MODE_IN );      // PD7 input
  ROM_GPIODirModeSet(GPIO_PORTC_BASE,GPIO_PIN_5,GPIO_DIR_MODE_IN );      // PC6 input
  ROM_GPIODirModeSet(GPIO_PORTC_BASE,GPIO_PIN_6,GPIO_DIR_MODE_IN );      // PC7 input
  ROM_GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_6);                        // use QEI0 ,phA0
  ROM_GPIOPinTypeQEI(GPIO_PORTD_BASE,GPIO_PIN_7);                        // use QEI1 ,phB0
  ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_5);                        // use QEI0 ,phA1
  ROM_GPIOPinTypeQEI(GPIO_PORTC_BASE,GPIO_PIN_6);                        // use QEI1 ,phB1
  ROM_QEIConfigure(QEI0_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_SWAP,Max_Position);       // capture A,B , max_pos=12
  ROM_QEIConfigure(QEI1_BASE,QEI_CONFIG_CAPTURE_A_B|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_RESET|QEI_CONFIG_NO_SWAP,Max_Position);       // capture A,B , max_pos=12
  ROM_QEIVelocityConfigure(QEI0_BASE,QEI_VELDIV_1,Timer_Period);   // capture pulses every 1s
  ROM_QEIVelocityConfigure(QEI1_BASE,QEI_VELDIV_1,Timer_Period);   // capture pulses every 1s
  ROM_QEIVelocityEnable(QEI0_BASE);                                //Enable Velocity capture mode
  ROM_QEIVelocityEnable(QEI1_BASE);                                //Enable Velocity capture mode	
  ROM_QEIIntEnable(QEI0_BASE,QEI_INTTIMER);                        //Enable Interrupt every timer tick
  ROM_QEIIntEnable(QEI1_BASE,QEI_INTTIMER);                        //Enable Interrupt every timer tick
  ROM_QEIEnable(QEI0_BASE);                                        //Enable QEI0
  ROM_QEIEnable(QEI1_BASE);                                        //Enable QEI1			
  ROM_IntEnable(QEI0_INT_NUM);                                     //Enable QEI0 interrupt number in NVIC -->13
  ROM_IntEnable(QEI1_INT_NUM);                                     //Enable QEI1 interrupt number in NVIC -->38
  ROM_IntPrioritySet(QEI0_INT_NUM,priority1);                       // priority 1 for QEI0 interrupt
  ROM_IntPrioritySet(QEI0_INT_NUM,priority1);                       // priority 1 for QEI1 interrupt
}







void SystemInit(){}
	