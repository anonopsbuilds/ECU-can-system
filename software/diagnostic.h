#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include <stdint.h>

void DiagnosticInit();
void Diagnostic_GetVoltAndCurr(uint8_t *voltage, uint8_t *current);

#endif /* DIAGNOSTIC_H_ */