
#ifndef _SPEED_H_
#define _SPEED_H_

#define TARGET_IS_TM4C123_RA1
#define PART_TM4C123GH6PM
#include <stdint.h>

                /**********************defines*******************/

#define   Max_Position     12
#define   Timer_Period     80000000
#define   QEI0_INT_NUM     13
#define   QEI1_INT_NUM     38
#define   priority0         0
#define   priority1         1
#define   timer_tick_freq   1 //1Hz
#define   gear_ratio        75
#define   diameter          14
#define   pi                3.14

               /*******************Functions_ProtoTypes**************/
							 
							 
/*
 *Init system clock
 *Init QEI module 0&1
 */
void Init_Speed(void); 

/*
 *calculates motors speed in RPM
 */
 
 void get_RPM(uint16_t* RPM);


#endif
