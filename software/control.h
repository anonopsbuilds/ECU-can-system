#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

typedef enum {LIGHT_ON_FAST, LIGHT_ON_SLOW, LIGHT_OFF_FAST, LIGHT_OFF_SLOW, LIGHT_SET_BRIGHTNESS}command_one_lamp;
typedef enum {LIGHT_GET_VOLTAGE_CURRENT, LIHGT_GET_STATE}command_all_lamp;


#endif