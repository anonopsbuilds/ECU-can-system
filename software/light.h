#ifndef LIGHT_H
#define LIGHT_H
//htim3, TIM_CHANNEL_1 PA6  : LIGHT_DISTANT 
//htim3, TIM_CHANNEL_2 PA7	: LIGHT_PARKING
//htim3, TIM_CHANNEL_3 PB0	: LIGHT_DIPPED
//htim4  for SLOW_SWITCH LED
#include <stdint.h>
#define TIM4_TIME_OFF 512             //cycle tim4 for auto off default: 512
#define PWM_MAX 65535   						  //scale pwm 16bit default 65535
#define OVERFLOW_PROTECTION_PWM 65280 //PWM_MAX-PWM_SCALE  default: 65280
#define PWM_SCALE 256    						  //PWM_MAX/PWM_SCALE default: 256

#define TIME 2			     						  //time in secound 1s-5s
#define BRIGHTNESS_SCALE 255          //for Light_SetBrightness default:255

typedef enum {LIGHT_DISTANT, LIGHT_PARKING, LIGHT_DIPPED}type_light;
typedef enum {FAST_SWITCH, SLOW_SWITCH}switch_speed;
typedef enum {LIGHT_ON, LIGHT_OFF}light_state;

void Light_On(type_light light, switch_speed speed);
void Light_Off(type_light light, switch_speed speed);
void Light_SetBrightness(type_light light, uint8_t brightness);
uint8_t Light_GetBrightness(type_light light);
light_state Light_GetState(type_light light);

#endif  /* LIGHT_H_ */
