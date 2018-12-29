#ifndef LIGHT_H
#define LIGHT_H

#include <stdint.h>

typedef enum {LIGHT_DISTANT, LIGHT_PARKING, LIGHT_DIPPED}type_light;
typedef enum {FAST_SWITCH, SLOW_SWITCH}switch_speed;
typedef enum {LIGHT_ON, LIGHT_OFF}light_state;

void Light_On(type_light light, switch_speed speed);
void Light_Off(type_light light, switch_speed speed);
uint8_t Light_GetBrightness(type_light light);
light_state Light_GetState(type_light light);


#endif  /* LIGHT_H_ */