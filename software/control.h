#ifndef CONTROL_H
#define CONTROL_H
/*
    data in one packet has 8 byte max
*/

#include <stdint.h>

typedef enum {LIGHT_ON_FAST, LIGHT_ON_SLOW, LIGHT_OFF_FAST, LIGHT_OFF_SLOW, LIGHT_SET_BRIGHTNESS, 
                LIGHT_GET_VOLTAGE_CURRENT, LIGHT_GET_STATE}controlCommand;

controlCommand Control_GetCommand(void);
void Control_SendData(uint8_t * data);


#endif  /* CONTROL_H_ */