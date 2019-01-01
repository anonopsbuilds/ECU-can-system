#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H
#define scalind_ADC 4096      // default 4096
#define voltage_ADC 3.3       // voltage power ADC, default 3.3 voltage
#include <stdint.h>

void DiagnosticInit(void);
void Diagnostic_GetVoltAndCurr(uint8_t *voltage, uint8_t *current);

#endif /* DIAGNOSTIC_H_ */
