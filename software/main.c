#include "control.h"
#include "light.h"
#include "diagnostic.h"
#include "stm32f1xx_hal.h"

void Init(void);
void Sleep();

void main(void)
{
    Init();

    controlCommand receiveCommand;
    while(1)
    {
        receiveCommand = Control_GetCommand();

        switch (receiveCommand)
        {
            case LIGHT_ON_FAST:
                break;
             case LIGHT_ON_SLOW:
                break;
             case LIGHT_OFF_FAST:
                break;
             case LIGHT_OFF_SLOW:
                break;
             case LIGHT_SET_BRIGHTNESS:
                break;
             case LIGHT_GET_VOLTAGE_CURRENT:
                break;
             case LIHGHT_GET_STATE:
                break;
            default:
                break;
        }

        /*go to sleep*/
    }
}

void Init()
{
    /*system mcu init*/


    ControlInit();
    LightInit();
    DiagnosticInit();
}