/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "canard.h"
#include "canard_internals.h"
#include "string.h"
#include "uavcan.protocol.NodeStatus.h"
#include "uavcan.protocol.GetNodeInfo_res.h"
#include "uavcan.equipment.power.BatteryInfo.h"
#include "uavcan.protocol.SoftwareVersion.h"
#include "uavcan.protocol.HardwareVersion.h"
#include "stdlib.h"
#include "stdio.h" 
#include "stdbool.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */
uint8_t canard_memory_pool[1024];
CanardInstance canard;

uint8_t heartbeat_tid = 0;
uint8_t battery_tid = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK) {
        CanardCANFrame frame;
        frame.id = rxHeader.ExtId;
        if (rxHeader.IDE == CAN_ID_EXT)
            frame.id |= (1UL << 31); 

        frame.data_len = rxHeader.DLC;
        memcpy(frame.data, rxData, rxHeader.DLC);
        frame.iface_id = 0;

        canardHandleRxFrame(&canard, &frame, HAL_GetTick() * 1000ULL);
    }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


bool should_accept(const CanardInstance* ins, uint64_t* out_sig, uint16_t data_type_id,
                   CanardTransferType transfer_type, uint8_t source_node_id) 
{	
    if (data_type_id == UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_ID && transfer_type == CanardTransferTypeRequest) 
		{
        *out_sig = UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_SIGNATURE;
        return true;
    }
    return false;
}
void on_reception(CanardInstance* ins, CanardRxTransfer* transfer)
{
    if (transfer->data_type_id == UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_ID &&
        transfer->transfer_type == CanardTransferTypeRequest)
    {
        struct uavcan_protocol_GetNodeInfoResponse resp;
        memset(&resp, 0, sizeof(resp));

        const char* node_name = "75";

        resp.status.uptime_sec = HAL_GetTick() / 1000;
        resp.status.health = UAVCAN_PROTOCOL_NODESTATUS_HEALTH_OK;
        resp.status.mode = UAVCAN_PROTOCOL_NODESTATUS_MODE_OPERATIONAL;
        resp.status.sub_mode = 0;
        resp.status.vendor_specific_status_code = 0;

        resp.software_version.major = 1;
        resp.software_version.minor = 0;
        resp.hardware_version.major = 1;
        resp.hardware_version.minor = 0;

        resp.name.len = strlen(node_name);
        memcpy(resp.name.data, node_name, resp.name.len);

        uint8_t buffer[UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_MAX_SIZE] = {0};
        uint32_t len = uavcan_protocol_GetNodeInfoResponse_encode(&resp, buffer);

        uint8_t tid = transfer->transfer_id;
        canardRequestOrRespond(ins,
            transfer->source_node_id,
            UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_SIGNATURE,
            UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_ID,
            &tid,
            CANARD_TRANSFER_PRIORITY_LOW,
            CanardResponse,
            buffer,
            len
        );
    }
}

void tx_frame(void)
{
	CanardCANFrame* txf = NULL;
	while ((txf = canardPeekTxQueue(&canard)) != NULL)
	{
			if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) > 0)
			{
					CAN_TxHeaderTypeDef txHeader;
					memset(&txHeader, 0, sizeof(txHeader));
					txHeader.IDE = CAN_ID_EXT;
					txHeader.ExtId = txf->id & 0x1FFFFFFF;
					txHeader.RTR = CAN_RTR_DATA;
					txHeader.DLC = txf->data_len;
					txHeader.TransmitGlobalTime = DISABLE;

					uint32_t txMailbox;
					if (HAL_CAN_AddTxMessage(&hcan, &txHeader, (uint8_t*)txf->data, &txMailbox) == HAL_OK)
					{
							canardPopTxQueue(&canard);
					}
					else
					{
							break; 
					}
			}
			else
			{
					break; 
			}
	}
	HAL_Delay(1);
}

void send_heartbeat(CanardInstance* ins, uint8_t* transfer_id)
{
    struct uavcan_protocol_NodeStatus status = {
        .uptime_sec = HAL_GetTick() / 1000,
        .health = UAVCAN_PROTOCOL_NODESTATUS_HEALTH_OK,
        .mode = UAVCAN_PROTOCOL_NODESTATUS_MODE_OPERATIONAL,
        .sub_mode = 0,
        .vendor_specific_status_code = 0
    };
    uint8_t buffer[UAVCAN_PROTOCOL_NODESTATUS_MAX_SIZE] = {0};
    uint32_t len = uavcan_protocol_NodeStatus_encode(&status, buffer);

    canardBroadcast(ins,
        UAVCAN_PROTOCOL_NODESTATUS_SIGNATURE,
        UAVCAN_PROTOCOL_NODESTATUS_ID,
        transfer_id,
        CANARD_TRANSFER_PRIORITY_LOW,
        buffer,
        len
    );
}
void send_battery_info(void)
{
    struct uavcan_equipment_power_BatteryInfo msg = {0};

    // Tùy pack mà gán dúng tên:
    const char* name = "hypmotion_pack_pin_2"; // ho?c _2, _3 tùy chip
    msg.temperature =   25; // float
    msg.voltage =   26.211;      // float
    msg.current = 2.124;           // float
    msg.state_of_charge_pct = 54;         // uint8_t (0-100)
    msg.state_of_health_pct = 100;                // ho?c tính n?u có
    msg.status_flags = 0;                         // Xem hdsd d? báo tr?ng thái

    msg.model_name.len = strlen(name);
    memcpy(msg.model_name.data, name, msg.model_name.len);

    // ... gán các tru?ng còn l?i n?u mu?n, ho?c d? = 0

    uint8_t buffer[UAVCAN_EQUIPMENT_POWER_BATTERYINFO_MAX_SIZE];
    uint32_t len = uavcan_equipment_power_BatteryInfo_encode(&msg, buffer);

    canardBroadcast(&canard,
        UAVCAN_EQUIPMENT_POWER_BATTERYINFO_SIGNATURE,
        UAVCAN_EQUIPMENT_POWER_BATTERYINFO_ID,
        &battery_tid,
        CANARD_TRANSFER_PRIORITY_LOW,
        buffer,
        len
    );
}
void filer_config(void)
{
		//------------filer-------------//
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0;
	sFilterConfig.FilterIdLow  = 0;
	sFilterConfig.FilterMaskIdHigh = 0;
	sFilterConfig.FilterMaskIdLow  = 0;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	HAL_CAN_ConfigFilter(&hcan, &sFilterConfig);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
	HAL_CAN_Start(&hcan);
	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	canardInit(&canard,
           canard_memory_pool,
           sizeof(canard_memory_pool),
           on_reception,
           should_accept,
           NULL);
	canardSetLocalNodeID(&canard, 12);
	filer_config();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		tx_frame();
		static uint32_t last_hb = 0;
		if(HAL_GetTick() - last_hb >= 1000)
		{
			send_heartbeat(&canard, &heartbeat_tid);
			last_hb = HAL_GetTick();
		}
		static uint32_t last_batt = 0;
		if (HAL_GetTick() - last_batt >= 100)
		{
			send_battery_info();
			last_batt = HAL_GetTick();
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 4;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
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
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
