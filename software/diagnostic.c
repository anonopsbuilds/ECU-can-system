///
#include <diagnostic.h>
#include "stm32f1xx_hal.h"

ADC_HandleTypeDef hadc1;                                                       // ADC 1

uint8_t data_adc;                                                              // for voltage 
uint8_t data_adc11;                                                            // for current

// initialization ADC 1 
/*
		ADC setting CubeMX
		
		Mode 													: independent mode
		Data alignment 								: Right alignment
		Scan conversion mode       		: Enabled
		Continuous Conversion Mode 		: Enabled
		Discontinuous Conversion Mode : Disabled
		Enable Regular Conversions 		: Disabled
		Number Of Conversions 				: 2
		External Trigger Source 			: Injected Conversion launched by software
    Injected Conversion Mode 			: None
*/
void DiagnosticInit(void)
{
   __HAL_RCC_GPIOA_CLK_ENABLE();
  ADC_InjectionConfTypeDef sConfigInjected;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Injected Channel 
    */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_0;
  sConfigInjected.InjectedRank = ADC_INJECTED_RANK_1;
  sConfigInjected.InjectedNbrOfConversion = 2;
  sConfigInjected.InjectedSamplingTime = ADC_SAMPLETIME_7CYCLES_5;
  sConfigInjected.ExternalTrigInjecConv = ADC_INJECTED_SOFTWARE_START;
  sConfigInjected.AutoInjectedConv = DISABLE;
  sConfigInjected.InjectedDiscontinuousConvMode = DISABLE;
  sConfigInjected.InjectedOffset = 0;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Injected Channel 
    */
  sConfigInjected.InjectedChannel = ADC_CHANNEL_1;
  sConfigInjected.InjectedRank = ADC_INJECTED_RANK_2;
  if (HAL_ADCEx_InjectedConfigChannel(&hadc1, &sConfigInjected) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
 
	  HAL_ADCEx_Calibration_Start(&hadc1);
}
// initialization ADC 1

// function read sens voltage and current
/*
    NEED CALIBRATION for current and voltage!!!
		full calibration is executed in work device
    function print voltage - volt, current - ampers
*/
void Diagnostic_GetVoltAndCurr(uint8_t *voltage, uint8_t *current)
{
		HAL_ADCEx_InjectedStart(&hadc1);                                           // start conversion
		HAL_ADC_PollForConversion(&hadc1,100);                                     // mode conversion
		data_adc = HAL_ADCEx_InjectedGetValue(&hadc1,ADC_INJECTED_RANK_1);         // channel 0 ADC
	  data_adc11 = HAL_ADCEx_InjectedGetValue(&hadc1,ADC_INJECTED_RANK_2);       // channe2 1 ADC
		HAL_ADCEx_InjectedStop(&hadc1);                                            // stop conversion	
		*voltage = ( data_adc * voltage_ADC / scalind_ADC);                        // return voltage
	  *current = ( data_adc11 * voltage_ADC / scalind_ADC);                      // return current 	
}
// function read sens voltage and current


