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
#include "common/mavlink.h"
#include "ring.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DMA_RX_SIZE 256
#define DMA_TX_SIZE 100
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
uint8_t rx_byte;
mavlink_message_t rx_msg;
mavlink_status_t status;
mavlink_heartbeat_t hb;
mavlink_command_long_t cmd;
RINGBUF ring;
RINGBUF ring_tx;
uint8_t ring_buf[256];
uint8_t ring_buf_tx[256];
uint8_t read_data;
uint32_t last_heartbeat_time = 0;
uint32_t heartbeat_period_ms = 0;
float heartbeat_freq_hz = 0;
int count = 0;
uint32_t now;
uint8_t dma_rx_buf[DMA_RX_SIZE];
uint8_t dma_tx_buf[DMA_TX_SIZE];
uint16_t old_pos = 0;
volatile uint8_t uart_tx_busy = 0;
uint8_t tick = 0;
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if (huart->Instance == USART1)
//	{
//		RINGBUF_Put(&ring, rx_byte);
//		HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
//	}
//}
void ring_buffer_send_data(void)
{
    if (uart_tx_busy) return;

    uint8_t data_to_send = 0;
		if(RINGBUF_Get(&ring_tx, &data_to_send) == RING_OK)
		{
			uint8_t tx_data[1] = {data_to_send};
			uart_tx_busy = 1;
			HAL_UART_Transmit_DMA(&huart2, tx_data, 1);
		}
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
      uart_tx_busy = 0;
			ring_buffer_send_data();
    }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


void send_heartbeat(void)
{
	mavlink_message_t msg;
	uint8_t tx_buf[100];
	uint16_t len;
	mavlink_msg_heartbeat_pack(
			1, 1, &msg,           // system_id, component_id
			MAV_TYPE_GENERIC,      // Lo?i thi?t b?
			MAV_AUTOPILOT_GENERIC, // Lo?i autopilot
			MAV_MODE_MANUAL_ARMED, // Ch? d? Manual và dã ARM
			0,                     // Custom mode
			MAV_STATE_ACTIVE       // Tr?ng thái Active
	);
	
	len = mavlink_msg_to_send_buffer(tx_buf, &msg);
	for (uint16_t i = 0; i < len; i++)
	{
			RINGBUF_Put(&ring_tx, tx_buf[i]);
	}
	ring_buffer_send_data();
}


void send_battery_status(void)
{
	mavlink_message_t msg;
	uint8_t tx_buf[100];
	uint16_t len;

	// Kh?i t?o thông tin pin
	mavlink_battery_status_t battery_status;
	battery_status.current_consumed = 500;      // 500 mAh dã tiêu th?
	battery_status.energy_consumed = 10000;     // 10 Wh dã tiêu th?
	battery_status.temperature = 250;           // 25.0°C
	battery_status.voltages[0] = 11500;         // 11.5V
	battery_status.voltages[1] = 11500;         // 11.5V
	battery_status.current_battery = 1000;      // 1A
	battery_status.id = 1;                      // ID pin
	battery_status.battery_function = 0;  // Ch?c nang chính
	battery_status.type = MAV_BATTERY_TYPE_LIPO;  // Lo?i pin LiPo
	battery_status.battery_remaining = 80;      // 80% pin còn l?i
	battery_status.time_remaining = 3600;       // 1 gi? còn l?i
	battery_status.charge_state = 1;  // Ðang x?
	battery_status.voltages_ext[0] = 0;         // Không có t? bào pin 11-14
	battery_status.mode = 0;                    // Ch? d? bình thu?ng
	battery_status.fault_bitmask = 0;           // Không có l?i

	// G?i thông tin pin qua MAVLink
	mavlink_msg_battery_status_pack(
			1, 1, &msg,
			battery_status.id,
			battery_status.battery_function,
			battery_status.type,
			battery_status.temperature,
			battery_status.voltages,  // M?ng di?n áp
			battery_status.current_battery,
			battery_status.current_consumed,
			battery_status.energy_consumed,
			battery_status.battery_remaining,
			battery_status.time_remaining,
			battery_status.charge_state,
			battery_status.voltages_ext,  // Ði?n áp t? bào 11-14
			battery_status.mode,
			battery_status.fault_bitmask
	);

	len = mavlink_msg_to_send_buffer(tx_buf, &msg);
	for (uint16_t i = 0; i < len; i++)
	{
			RINGBUF_Put(&ring_tx, tx_buf[i]);
	}
	ring_buffer_send_data();
	
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3) //10hz
	{
		send_battery_status();
	}
	if(htim->Instance == TIM2) //1hz
	{
		send_heartbeat();
	}
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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	RINGBUF_Init(&ring, ring_buf, sizeof(ring_buf));
	RINGBUF_Init(&ring_tx, ring_buf_tx, sizeof(ring_buf_tx));
	//HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_UART_Receive_DMA(&huart2, dma_rx_buf, DMA_RX_SIZE);
	HAL_TIM_Base_Start_IT(&htim3);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		uint16_t new_pos = DMA_RX_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx); //vi tri moi nhat DMA ghi den
    if(new_pos != old_pos)
    {
      if(new_pos > old_pos)
      {
       // DMA chua quay vòng
				for (uint16_t i = old_pos; i < new_pos; i++)
				RINGBUF_Put(&ring, dma_rx_buf[i]);
      }
      else
      {
         // DMA dã quay vòng
				for (uint16_t i = old_pos; i < DMA_RX_SIZE; i++)
					RINGBUF_Put(&ring, dma_rx_buf[i]);
				for (uint16_t i = 0; i < new_pos; i++)
					RINGBUF_Put(&ring, dma_rx_buf[i]);
      }

       old_pos = new_pos;
    }
		
		
		
		if(RINGBUF_Get(&ring, &read_data) ==  RING_OK)
		{
			if (mavlink_parse_char(MAVLINK_COMM_0, read_data, &rx_msg, &status))
			{
				switch(rx_msg.msgid)
				{
					case MAVLINK_MSG_ID_HEARTBEAT:
					{
						mavlink_msg_heartbeat_decode(&rx_msg, &hb);
						uint32_t now = HAL_GetTick();
						if (last_heartbeat_time != 0)
						{
							heartbeat_period_ms = (uint32_t)now - last_heartbeat_time;
				      if (heartbeat_period_ms > 0)
               heartbeat_freq_hz = 1000.0f / heartbeat_period_ms;
						}

						last_heartbeat_time = now;
						break;
					}
					case MAVLINK_MSG_ID_COMMAND_LONG:
					{
						mavlink_msg_command_long_decode(&rx_msg, &cmd);

						if (cmd.command == MAV_CMD_COMPONENT_ARM_DISARM)
						{
							if (cmd.param1 == 1)
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
							else
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
						}

						break;
					}
				}
			}
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 799;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 19999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 799;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

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
