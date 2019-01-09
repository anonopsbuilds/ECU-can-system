#ifndef CONTROL_H
#define CONTROL_H
/*
    data in one packet has 8 byte max
*/

#include <stdint.h>

#define DEVICE_MY_ID            0x124
#define TRANSMITTER_ID          0x123
#define CONTROL_MSG_LENGHT	    1
#define CONTROL_MSG_MAX_LENGHT  8

typedef enum {NONE, LIGHT_ON_FAST, LIGHT_ON_SLOW, LIGHT_OFF_FAST, LIGHT_OFF_SLOW, LIGHT_SET_BRIGHTNESS, 
                LIGHT_GET_VOLTAGE_CURRENT, LIGHT_GET_STATE}controlCommand;

void Control_Init(void);
controlCommand Control_GetCommand(void);
void Control_SendData(uint8_t * data);

#endif  /* CONTROL_H_ */
								