#include "control.h"
#include "light.h"
#include "diagnostic.h"
#include "stm32f1xx_hal.h"

void Init(void);

void main(void)
{
    Init();
    while(1)
    {
        
    }
}

void Init()
{
    /*system mcu init*/


    ControlInit();
    LightInit();
    DiagnosticInit();
}