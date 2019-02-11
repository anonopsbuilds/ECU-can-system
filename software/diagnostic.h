#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H
#define SCALING_ADC 4095       // default 4096
#define VOLTAGE_ADC 3300       // voltage power ADC, default 3.3 voltage
#define RANGE_VOLTAGE 18       // max input 18 volt
#define RANGE_CURRENT 18       // max 18 ampers
#include <stdint.h>

void DiagnosticInit(void);
void Diagnostic_GetVoltAndCurr(uint8_t *voltage, uint8_t *current);

#endif /* DIAGNOSTIC_H_ */



