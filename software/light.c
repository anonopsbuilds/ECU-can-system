#include "light.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"

TIM_HandleTypeDef htim3;      //for HAL used TIM3 
TIM_HandleTypeDef htim4;      //for HAL used TIM4 

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);

uint16_t tmp = 0;
uint8_t channel_1 = 0;        //set channel pwm
uint8_t channel_2 = 0;        //set channel pwm
uint8_t channel_3 = 0;        //set channel pwm
 
typedef struct 
	{
		uint8_t brightness;        // yaskravist 
    light_state state;         // stan led
	  switch_speed speed;        // speed off/on
	} light;
 
  light light_distant;
	light light_parking;
	light light_dipped;

void Light_On(type_light light, switch_speed speed)  // led on
	{
		switch(light)
		{
			case LIGHT_DISTANT :
				light_distant.speed = speed; 
			  light_distant.state = LIGHT_ON;
				if(speed == FAST_SWITCH)                      
				{				
				  MX_TIM3_Init();                            //pwm init
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);  //start pwm CHANNEL_1
					TIM3->CCR1 = PWM_MAX;                      //max light
				}
				else                                         //(speed == SLOW_SWITCH)   
				{
					channel_1 = 1;
					if(channel_2==0 && channel_3 ==0)
						{
							MX_TIM3_Init();
							MX_TIM4_Init();
							HAL_TIM_Base_Start(&htim4);
							HAL_TIM_Base_Start_IT(&htim4);
						}
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); 					  
				}
				break; 
			case LIGHT_PARKING :
				light_parking.speed = speed; 
			  light_parking.state = LIGHT_ON;
				if(speed == FAST_SWITCH)
				{
					MX_TIM3_Init();
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);  //start pwm CHANNEL_2
					TIM3->CCR2 = PWM_MAX;
				}	
				else                                         //(speed == SLOW_SWITCH)   
				{
					channel_2 = 1;	
					if(channel_1==0 && channel_3 ==0)
					{
					MX_TIM3_Init();
					MX_TIM4_Init();
					HAL_TIM_Base_Start(&htim4);
					HAL_TIM_Base_Start_IT(&htim4);
					}
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);  	
				}				
				break;	
			case LIGHT_DIPPED :
				light_dipped.speed = speed; 
			  light_dipped.state = LIGHT_ON;	
				if(speed == FAST_SWITCH)
				{ 
					MX_TIM3_Init();
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);  //start pwm
					TIM3->CCR3 = PWM_MAX;
				}	
				else                                         //(speed == SLOW_SWITCH)   
				{
					channel_3 = 1;
					if(channel_1==0 && channel_2 ==0)
						{
							MX_TIM3_Init();
							MX_TIM4_Init();
							HAL_TIM_Base_Start(&htim4);
							HAL_TIM_Base_Start_IT(&htim4);
						}
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);	
				}								
				break;
		}		
	}
	
void Light_Off(type_light light, switch_speed speed)    //off led
	{
	 switch(light)
		{
			case LIGHT_DISTANT :
				light_distant.speed = speed; 
			  light_distant.state = LIGHT_ON;
				if(speed == FAST_SWITCH)
				{				
					TIM3->CCR1 = 0;	
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);      //stop pwm CHANNEL_1	
				}
				else
				{
					HAL_TIM_Base_Start(&htim4);
					HAL_TIM_Base_Start_IT(&htim4);
					channel_1 = 2;				
				}
				break;
			case LIGHT_PARKING :
				light_parking.speed = speed; 
			  light_parking.state = LIGHT_ON;
				if(speed == FAST_SWITCH)
				{
					TIM3->CCR2 = 0;	 
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);      //stop pwm CHANNEL_2	
				}	
				else
				{
					HAL_TIM_Base_Start(&htim4);
					HAL_TIM_Base_Start_IT(&htim4);
					channel_2 = 2;			
				}					
				break;
			case LIGHT_DIPPED :
				light_dipped.speed = speed; 
			  light_dipped.state = LIGHT_ON;	
				if(speed == FAST_SWITCH)
				{
					TIM3->CCR3 = 0;	
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);      //stop pwm CHANNEL_3
				}
				else
				{
				  HAL_TIM_Base_Start(&htim4);
					HAL_TIM_Base_Start_IT(&htim4);
					channel_3 = 2;			
				}
				break;
		}			
	}
	
	void Light_SetBrightness(type_light light, uint8_t brightness)
	{
	/// text programm
		
		
	}
	
	
	
	
	
	uint8_t	Light_GetBrightness(type_light light)         // otrumy iaskravist
	{
		uint8_t brightness;
		switch(light)
			{
				case LIGHT_DISTANT :
					brightness = light_distant.brightness;
					break;
				case LIGHT_PARKING :
					brightness = light_parking.brightness;
					break;
				case LIGHT_DIPPED :
					brightness = light_dipped.brightness;
					break;
			}		
			return brightness;
	}
	
	light_state Light_GetState(type_light light)        // otrumy stan
	{
		light_state state;
		switch(light)
		{
			case LIGHT_DISTANT :
				state = light_distant.state;
				break;
			case LIGHT_PARKING :
				state = light_parking.state;
				break;
			case LIGHT_DIPPED :
				state = light_dipped.state;
				break;
		}	
		return state;
	}
	
////// timer init 
	static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim3);

}
	
/* TIM4 init function */
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 3042*TIME;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}



