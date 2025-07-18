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
#include <uavcan.protocol.debug.KeyValue.h>
#include "uavcan.protocol.SoftwareVersion.h"
#include "uavcan.protocol.HardwareVersion.h"
#include <uavcan.equipment.power.BatteryInfo.h>
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
#define Kp 100.0f
#define Ki 50.0f
#define Kb 1.0f
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

FDCAN_HandleTypeDef hfdcan1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
uint8_t canard_memory_pool[1024];
CanardInstance canard;

uint8_t node_id = 42;

FDCAN_RxHeaderTypeDef rxHeader;
FDCAN_TxHeaderTypeDef txHeader;

uint32_t temp_sp;

volatile uint16_t adc_temp[2];
uint16_t adc_filtered = 0;
volatile float temp;
float sampleTime = 0.1f;
uint16_t charging_current;


char bt_rx_buffer[32];
uint8_t bt_rx_index = 0;
uint8_t bt_rx_data;

volatile uint32_t heartbeat_count[3] = {0};
float heartbeat_freq[3] = {0};
uint8_t node_map[3] = {11, 12, 13};


uint16_t debug = 0;
uint16_t debug1 = 0;
uint16_t debug2 = 0;
uint16_t count;

typedef struct {
    char name[32];
    float voltage;
    float current;
    uint8_t soc;
    float temp;
    uint8_t node_id;
    uint32_t last_update;
    uint8_t online;
} PackInfo_t;

PackInfo_t packs[3]; // node_id 11,12,13
PackInfo_t packs[3] = {
    {.node_id = 11}, // pack pin 1
    {.node_id = 12}, // pack pin 2
    {.node_id = 13}  // pack pin 3
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
static void MX_FDCAN1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t filterIndex)
{
	uint8_t rxData[8];
	if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK)
			return;
	CanardCANFrame frame;
	frame.id = rxHeader.Identifier;
	if (rxHeader.IdType == FDCAN_EXTENDED_ID)
			frame.id |= (1UL << 31); // set extended bit
	frame.data_len = rxHeader.DataLength;
	if (frame.data_len > 8) frame.data_len = 8;

	memcpy(frame.data, rxData, frame.data_len);
	frame.iface_id = 0;

	canardHandleRxFrame(&canard, &frame, HAL_GetTick() * 1000ULL);
}

uint16_t lowpass_filter(uint16_t raw_value, uint16_t filter_value, uint8_t filter_alpha) 
{
	uint32_t temp = (uint32_t)filter_value * filter_alpha + raw_value;
	return temp / (1 + filter_alpha);
}

float LM70_CalculateTemperature(uint16_t adc_value)
{
	float Vref = 3.297f;
	float v_tao_mV = (adc_value / 4095.0f) * Vref * 1000.0f;
	float a = -1.809628e-09f;
	float b = -3.325395e-06f;
	float c = -1.814103e-01f;
	float d = 2.055894e+02f;

	float temp_c = a * v_tao_mV * v_tao_mV * v_tao_mV
							 + b * v_tao_mV * v_tao_mV
							 + c * v_tao_mV
							 + d;

	return temp_c;
}

int PI_Temp2Current(float T_setpoint, float T_measured)
{
	static float err_prev = 0;
	static float ui_prev = 0;
	static float e_reset = 0;

	float err, up, ui, u_total, anti_windup;
	float u_limited;
	int output_mA;

	err = T_setpoint - T_measured;

	up = Kp * err;
	anti_windup = Ki * err + Kb * e_reset;
	ui = ui_prev + anti_windup * sampleTime;


	ui_prev = ui;
	err_prev = err;

	u_total = up + ui;

	if (u_total > 5000.0f)
		u_limited = 5000.0f;
	else if (u_total < 500.0f)
		u_limited = 500.0f;
	else
		u_limited = u_total;

	// Anti-windup
	e_reset = u_limited - u_total;

	output_mA = ((int)(u_limited + 25.0f)) / 50 * 50;

	return output_mA;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		adc_filtered = lowpass_filter(adc_temp[0],adc_filtered,4);
		temp = LM70_CalculateTemperature(adc_filtered);
		charging_current = PI_Temp2Current(temp_sp, temp);
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool should_accept(const CanardInstance* ins, uint64_t* out_sig, uint16_t data_type_id,
                   CanardTransferType transfer_type, uint8_t source_node_id) {
		debug =  data_type_id;
	  debug1 = transfer_type;
    if (data_type_id == UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_ID &&
        transfer_type == CanardTransferTypeResponse) {
        *out_sig = UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_SIGNATURE;
        return true;
    }
		else if(data_type_id == UAVCAN_PROTOCOL_NODESTATUS_ID &&
						transfer_type == CanardTransferTypeBroadcast) {
				*out_sig = UAVCAN_PROTOCOL_NODESTATUS_SIGNATURE;
				return true;
		}
		if (data_type_id == UAVCAN_EQUIPMENT_POWER_BATTERYINFO_ID &&
		transfer_type == CanardTransferTypeBroadcast)
    {
        *out_sig = UAVCAN_EQUIPMENT_POWER_BATTERYINFO_SIGNATURE;
        return true;
    }
    return false;
}
									 

void on_reception(CanardInstance* ins, CanardRxTransfer* transfer)
{
	if (transfer->data_type_id == UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_ID &&
			transfer->transfer_type == CanardTransferTypeResponse)
	{
		struct uavcan_protocol_GetNodeInfoResponse resp;
		memset(&resp, 0, sizeof(resp));
		bool invalid = uavcan_protocol_GetNodeInfoResponse_decode(transfer, &resp);
		if (!invalid) 
		{
			char name[81] = {0};
			memcpy(name, resp.name.data, resp.name.len);
			name[resp.name.len] = '\0';
			temp_sp = atoi(name);
			HAL_TIM_Base_Start_IT(&htim3);
			memset(name, 0, sizeof(name));
		}
	}
	if (transfer->data_type_id == UAVCAN_PROTOCOL_NODESTATUS_ID &&
	transfer->transfer_type == CanardTransferTypeBroadcast)
	{

		for(int i=0; i<3; i++) 
		{
			if(transfer->source_node_id == node_map[i]) 
			{
				heartbeat_count[i]++;
				break;
			}
		}
	}
	if (transfer->data_type_id == UAVCAN_EQUIPMENT_POWER_BATTERYINFO_ID &&
	transfer->transfer_type == CanardTransferTypeBroadcast)
	{
		count++;
		struct uavcan_equipment_power_BatteryInfo msg;
		memset(&msg, 0, sizeof(msg));
		if (!uavcan_equipment_power_BatteryInfo_decode(transfer, &msg)) 
		{
			for(int i=0; i<3; i++) 
			{
				debug2 = transfer->source_node_id;
				if (packs[i].node_id == transfer->source_node_id) 
				{
					memcpy(packs[i].name, msg.model_name.data, msg.model_name.len);
					packs[i].name[msg.model_name.len] = 0;
					packs[i].voltage = msg.voltage;
					packs[i].current = msg.current;
					packs[i].soc = msg.state_of_charge_pct;
					packs[i].temp = msg.temperature;
					packs[i].last_update = HAL_GetTick();  // c?p nh?t th?i di?m nh?n cu?i
					packs[i].online = 1;                   // dang k?t n?i
				}
			}
		}
	}
}

void request_node_info(uint8_t dest_node_id, uint8_t* tid)
{
    uint8_t buffer[1] = {0};
    canardRequestOrRespond(
        &canard,
        dest_node_id,
        UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_SIGNATURE,
        UAVCAN_PROTOCOL_GETNODEINFO_RESPONSE_ID,
        tid,
        CANARD_TRANSFER_PRIORITY_LOW,
        CanardRequest,
        buffer,
        0
    );
}

void tx_frame(void)
{
    const CanardCANFrame* txf;
    while ((txf = canardPeekTxQueue(&canard)) != NULL)
    {

        if ((hfdcan1.Instance->TXFQS & FDCAN_TXFQS_TFQF) == 0) // TX FIFO not full
        {
            txHeader.Identifier = txf->id & 0x1FFFFFFF;
            txHeader.IdType = FDCAN_EXTENDED_ID;
            txHeader.TxFrameType = FDCAN_DATA_FRAME;
            txHeader.DataLength = txf->data_len;
            txHeader.FDFormat = FDCAN_CLASSIC_CAN;
            txHeader.BitRateSwitch = FDCAN_BRS_OFF;
            txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
            txHeader.MessageMarker = 0;

            if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &txHeader, (uint8_t*)txf->data) == HAL_OK)
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

void config_fdcan_filter_all(void)
{
    FDCAN_FilterTypeDef sFilterConfig;

    // Nh?n t?t c? Standard ID
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x000;
    sFilterConfig.FilterID2 = 0x000;
    if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    // Nh?n t?t c? Extended ID
    sFilterConfig.IdType = FDCAN_EXTENDED_ID;
    sFilterConfig.FilterIndex = 1;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x00000000;
    sFilterConfig.FilterID2 = 0x00000000;
    if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}


void parse_bluetooth_cmd(char *cmd)
{
		static uint8_t tid1 = 0, tid2 = 0, tid3 = 0;
		static uint32_t last_send_node_1 = 0;
		static uint32_t last_send_node_2 = 0;
		static uint32_t last_send_node_3 = 0;
    if(strncmp(cmd, "NODE1", 5) == 0)
    {
			request_node_info(11,&tid1);
		}
    else if(strncmp(cmd, "NODE2", 5) == 0)
    {
			request_node_info(12,&tid2);
    }
		else if(strncmp(cmd, "NODE3", 5) == 0)
    {
			request_node_info(13,&tid3);
    }
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		if(bt_rx_data != '\n' && bt_rx_index < sizeof(bt_rx_buffer) - 1)
		{
			bt_rx_buffer[bt_rx_index++] = bt_rx_data;
		}
		else
		{
			bt_rx_buffer[bt_rx_index] = 0; 
			bt_rx_index = 0;
			parse_bluetooth_cmd(bt_rx_buffer);
		}
		HAL_UART_Receive_IT(&huart3, &bt_rx_data, 1);
	}
}

void check_pack_online(void)
{
	uint32_t now = HAL_GetTick();
	for (int i = 0; i < 3; i++) 
	{
		if (packs[i].online && (now - packs[i].last_update > 500))
		{
			packs[i].online = 0;
			packs[i].soc = 0; // reset de loai khoi danh sach sac
		}
	}
}
int select_pack_for_charge(void)
{
	int selected = -1;
	uint8_t max_soc = 0;
	for (int i = 0; i < 3; i++) 
	{
		if (packs[i].online && packs[i].soc < 100 && packs[i].soc > max_soc) 
		{
			max_soc = packs[i].soc;
			selected = i;
		}
	}
	return selected;
}

void set_charging_pack(int index)
{
	HAL_GPIO_WritePin(GPIOD, EN_charge_pack1_Pin, (index == 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, EN_charge_pack2_Pin, (index == 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, EN_charge_pack3_Pin, (index == 2) ? GPIO_PIN_SET : GPIO_PIN_RESET);
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
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_FDCAN1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_FDCAN_Start(&hfdcan1);
	config_fdcan_filter_all();
	HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
	canardInit(&canard,
				 canard_memory_pool,
				 sizeof(canard_memory_pool),
				 on_reception,
				 should_accept,
				 NULL);
	canardSetLocalNodeID(&canard, node_id);
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_temp, 2);
	HAL_UART_Receive_IT(&huart3, &bt_rx_data, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		static uint32_t last_freq_update = 0;
		tx_frame();
    if (HAL_GetTick() - last_freq_update >= 1000)
    {
			for(int i=0; i<3; i++) {
					heartbeat_freq[i] = (float)heartbeat_count[i];
					heartbeat_count[i] = 0;
			}
			last_freq_update = HAL_GetTick();
    }
		check_pack_online();
		
		int charging_index = select_pack_for_charge();
		set_charging_pack(charging_index);
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.LowPowerAutoPowerOff = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc1.Init.SamplingTimeCommon1 = ADC_SAMPLETIME_160CYCLES_5;
  hadc1.Init.SamplingTimeCommon2 = ADC_SAMPLETIME_160CYCLES_5;
  hadc1.Init.OversamplingMode = DISABLE;
  hadc1.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_HIGH;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief FDCAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = DISABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 4;
  hfdcan1.Init.NominalSyncJumpWidth = 1;
  hfdcan1.Init.NominalTimeSeg1 = 13;
  hfdcan1.Init.NominalTimeSeg2 = 2;
  hfdcan1.Init.DataPrescaler = 1;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 1;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.StdFiltersNbr = 1;
  hfdcan1.Init.ExtFiltersNbr = 1;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */

  /* USER CODE END FDCAN1_Init 2 */

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
  htim3.Init.Period = 7999;
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
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CAN_BUS_ON_GPIO_Port, CAN_BUS_ON_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, EN_charge_pack1_Pin|EN_charge_pack2_Pin|EN_charge_pack3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CAN_BUS_ON_Pin */
  GPIO_InitStruct.Pin = CAN_BUS_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CAN_BUS_ON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : EN_charge_pack1_Pin EN_charge_pack2_Pin EN_charge_pack3_Pin */
  GPIO_InitStruct.Pin = EN_charge_pack1_Pin|EN_charge_pack2_Pin|EN_charge_pack3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
