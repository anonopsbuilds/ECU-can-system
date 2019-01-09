#include "control.h"
#include "stm32f1xx_hal.h"

CAN_HandleTypeDef hcan;
CAN_TxHeaderTypeDef pTxHeader;
CAN_RxHeaderTypeDef pRxHeader;
		

void Error_Handler(void);
static void MX_CAN_Init(void);
static void MX_CAN_FlterInit(void);

/**
  * @brief CAN init function 
  * @param None
  * @retval None
  */
void Control_Init(void)
{
    MX_CAN_Init();
    HAL_CAN_Init(&hcan);
    MX_CAN_FlterInit();

		if(HAL_CAN_Start(&hcan) != HAL_OK)
		{
			Error_Handler();
		}
		
		pTxHeader.StdId = DEVICE_MY_ID;			//my id
		pTxHeader.IDE=CAN_ID_STD;						//standart of extendet id
		pTxHeader.RTR=CAN_RTR_DATA;					//message - data
		pTxHeader.DLC=CONTROL_MSG_LENGHT;		//receive message legth(max 8 for standart packet)
		
		pRxHeader.StdId = 0xff;
		pRxHeader.IDE=CAN_ID_STD;
		pRxHeader.RTR = CAN_RTR_DATA;
		pRxHeader.DLC = CONTROL_MSG_LENGHT;	//transmit message legth(max 8 for standart packet)
}

/**
  * @brief CAN receiving data 
  * @param None
  * @retval received control command (from enum controlCommand)
  */
controlCommand Control_GetCommand(void)
{
    controlCommand received_command;
		uint8_t rxData[CONTROL_MSG_MAX_LENGHT];
		uint32_t RxMailbox;
		HAL_StatusTypeDef status;
	
		rxData[0] = 0;
	
		status = HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &pRxHeader, rxData);
		received_command = rxData[0];

    return received_command;
}

/**
  * @brief CAN Sending data 
  * @param data - array containing the payload of the Tx frame, max 8 byte
  * @retval None
  */
void Control_SendData(uint8_t * data)
{
		uint32_t TxMailbox;
		HAL_StatusTypeDef status;
	
    status = HAL_CAN_AddTxMessage(&hcan, &pTxHeader, data, &TxMailbox);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 2;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;			
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Filter Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_FlterInit(void)
{
	CAN_FilterTypeDef canFilterConfig;
	canFilterConfig.FilterIdHigh = TRANSMITTER_ID << 5;           //receive message only from TRANSMITTER_ID
	canFilterConfig.FilterIdLow = TRANSMITTER_ID << 5;
	canFilterConfig.FilterMaskIdHigh = 0x2460;		              //mask for incoming message
  canFilterConfig.FilterMaskIdLow = 0x2460;
	canFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;		//in fifo0 or in fifo1, can use isr for each fifo
	canFilterConfig.FilterBank = 0;															//max is 14 banks
	canFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
  canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  canFilterConfig.FilterActivation = ENABLE;
	canFilterConfig.SlaveStartFilterBank = 14;
  HAL_CAN_ConfigFilter(&hcan, &canFilterConfig);
}