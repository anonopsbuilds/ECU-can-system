/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "stm32f1xx_it.h"
#include "light.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/         
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern uint8_t channel_1;           //set channel pwm, used light.c
extern uint8_t channel_2;           //set channel pwm, used light.c
extern uint8_t channel_3;           //set channel pwm, used light.c



static uint16_t tmp_CH1 = 0;        // for pwm ++ CH1
static uint16_t tmp_CH2 = 0;        // for pwm ++ CH2
static uint16_t tmp_CH3 = 0;        // for pwm ++ CH3
	
static uint8_t stop_CH1 = 0;        // lock pwm ++ CH1
static uint8_t stop_CH2 = 0;        // lock pwm ++ CH2
static uint8_t stop_CH3 = 0;        // lock pwm ++ CH3

static uint16_t control_timer = 0;  // for off/on timer
/******************************************************************************/
/*            Cortex-M3 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Prefetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles TIM3 global interrupt.
*/
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

	
	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	
	
  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
* @brief This function handles TIM4 global interrupt.
*/
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
 	
  
	/// write pwm CH1 and ++
	if (channel_1 == 1 && stop_CH1 !=1)
	{
		if(tmp_CH1 >= OVERFLOW_PROTECTION_PWM)        // 65535-256                 
		{
			stop_CH1 = 1;                               // stop ++ CH1
			tmp_CH1 = PWM_MAX;                          // set max light
			TIM3->CCR1 = tmp_CH1;	                      // write pwm
		}
		else
		{
		tmp_CH1+=PWM_SCALE;                           // light ++
		TIM3->CCR1 = tmp_CH1;                         // write pwm 
		control_timer = 0;                            // control work timer
		}
	}
	/// write pwm CH1 and ++	
	
	
	
	
	/// write pwm CH2 and ++	
	if (channel_2 == 1 && stop_CH2 !=1)
	{
		if(tmp_CH2  >= OVERFLOW_PROTECTION_PWM) 
		{
			stop_CH2 = 1;                               // stop ++ CH2
			tmp_CH2 = PWM_MAX;                          // set max light
			TIM3->CCR2 = tmp_CH2;	                      // write pwm
		}	
		else
		{
		tmp_CH2+=PWM_SCALE;                           // light ++
		TIM3->CCR2 = tmp_CH2;                         // write pwm 
		control_timer = 0;
		}
	}
	/// write pwm CH2 and ++	
	
	
	/// write pwm CH3 and ++	
	if (channel_3 == 1 && stop_CH3 !=1)
	{
		if(tmp_CH3  >= OVERFLOW_PROTECTION_PWM) 
		{
			stop_CH3 = 1;                               // stop ++ CH3
			tmp_CH3 = PWM_MAX;                          // set max light
			TIM3->CCR3 = tmp_CH3;	                      // write pwm
		}
		else
		{
		tmp_CH3+=PWM_SCALE;                           // light ++
		TIM3->CCR3 = tmp_CH3;                         // write pwm 
		control_timer = 0;
		}
	}
	/// write pwm CH3 and ++		
    
	
	/// write pwm CH1 and --	
	if (channel_1 == 2 && stop_CH1 ==1)
	{
		if(tmp_CH1  <= PWM_SCALE) 
		{
			stop_CH1 = 0;                               // stop -- CH1
			tmp_CH1 = 0;                                // set max light
			TIM3->CCR1 = tmp_CH1;	                      // write pwm
		}	
		else
		{
		tmp_CH1-=PWM_SCALE;                           // light --
		TIM3->CCR1 = tmp_CH1;                         // write pwm 
		control_timer = 0;
		}
	}
	/// write pwm CH1 and --	
	
	/// write pwm CH2 and --	
	if (channel_2 == 2 && stop_CH2 ==1)
	{
		if(tmp_CH2  <= PWM_SCALE) 
		{	
			stop_CH2 = 0;                                // stop -- CH2
			tmp_CH2 = 0;                          			 // set max light
			TIM3->CCR2 = tmp_CH2;	                       // write pwm
		}
			else
			{
			tmp_CH2-=PWM_SCALE;                          // light --
			TIM3->CCR2 = tmp_CH2;                        // write pwm 
			control_timer = 0;
			}
	}
	/// write pwm CH2 and --	
	
	
	
	/// write pwm CH3 and --
	if (channel_3 == 2 && stop_CH3 ==1)
	{
		if(tmp_CH3  <= PWM_SCALE) 
		{
			stop_CH3 = 0;                               // stop -- CH3
			tmp_CH3 = 0;                      		      // set max light
			TIM3->CCR3 = tmp_CH3;	                      // write pwm
		}	
		else
		{
		tmp_CH3-=PWM_SCALE;                           // light --
		TIM3->CCR3 = tmp_CH3;                         // write pwm 
		control_timer = 0;
		}
	}
	/// write pwm CH3 and --	
	
	
  control_timer++;                               // ++ for OVERFLOW
  if(control_timer >= TIM4_TIME_OFF)             // stop timer if not used
	{
		control_timer = 0;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_TIM_Base_Stop_IT(&htim4);                // stop interrupt
		HAL_TIM_Base_Stop(&htim4);	                 // stop timer
		
	}
	
	
	
	
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */

  /* USER CODE END TIM4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
