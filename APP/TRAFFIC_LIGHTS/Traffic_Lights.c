/*
 * Traffic_Lights.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Interface
 */
#include "LED.h"

#define TICK_TIME 2


typedef unsigned char u8 ;
typedef unsigned int  u32 ;
typedef enum {
	G ,
	Y ,
	R ,
}enu_states_t;


void Traffic_Lights_Runnable(void)
{
	static u8 time = 0 ;
	enu_states_t static state = G ;
	time += TICK_TIME ;
	u8 prev = 50 ;
	switch(state)

	{
	case G :
			LED_Set_State(GREEN, LED_STATE_ON);
			LED_Set_State(YELLOW, LED_STATE_OFF);
			LED_Set_State(RED, LED_STATE_OFF);

			if(time == 6)
			{
				prev = G ;
				state = Y ;
				time = 0 ;
			}
			else {/* DO NOTHING */}
		break;

	case Y :
		LED_Set_State(GREEN, LED_STATE_OFF);
		LED_Set_State(YELLOW, LED_STATE_ON);
		LED_Set_State(RED, LED_STATE_OFF);

		if(time == 2)
		{
			if(prev==G)
			{
				prev = Y ;
				state = R ;
				time = 0 ;
			}
			else
			{
				state = G ;
				prev = Y ;
				time = 0 ;
			}
		}
		else {/* DO NOTHING */}
		break;

	case R :
		LED_Set_State(GREEN, LED_STATE_OFF);
		LED_Set_State(RED, LED_STATE_OFF);
		LED_Set_State(YELLOW, LED_STATE_ON);

		if(time == 10)
					{
						prev = R ;
						state = Y ;
						time = 0 ;
					}
		else {/* DO NOTHING */}
		break;

	default :
		break;
	}


}






