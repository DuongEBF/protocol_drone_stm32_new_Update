/**
  ******************************************************************************
  * @file    hypmotion_CRSF.c
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) ${year} NST.
  * All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/

/*INCLUDE--------------------------------------------------------------------------*/
#include <protocol/include/hypmotion_CRSF.h>

/*VARIABLE--------------------------------------------------------------------------*/
//extern UART_HandleTypeDef huart3;
//
//extern DMA_HandleTypeDef hdma_usart3_rx;
//extern DMA_HandleTypeDef hdma_usart3_tx;

extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

static hypmotion_crsf_protocol_t 	*pCRSF;

/*FUNCTION-----------------------------------------------------------------------------------*/
/* @brief: This function used for calculate crc8
 * @return: crc8 bit
 * */
uint8_t crsf_crc8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0;

    for (uint8_t i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0xD5;
            else
                crc <<= 1;
        }
    }

    return crc;
}

/* @brief: This function used for decode CRSF pay load
 * @return: no return
 * */
void decode_crsf_channels(const uint8_t *frame, uint16_t *ch_val)
{
    const uint8_t *sb_byte = &frame[3]; // bắt đầu từ byte payload thực sự

    ch_val[0]  = ((sb_byte[0] 		| (sb_byte[1] << 8)) & 0x07FF);
    ch_val[1]  = ((sb_byte[1] >> 3 	| (sb_byte[2] << 5)) & 0x07FF);
    ch_val[2]  = ((sb_byte[2] >> 6 	| (sb_byte[3] << 2) | (sb_byte[4] << 10)) & 0x07FF);
    ch_val[3]  = ((sb_byte[4] >> 1 	| (sb_byte[5] << 7)) & 0x07FF);
    ch_val[4]  = ((sb_byte[5] >> 4 	| (sb_byte[6] << 4)) & 0x07FF);
    ch_val[5]  = ((sb_byte[6] >> 7 	| (sb_byte[7] << 1) | (sb_byte[8] << 9)) & 0x07FF);
    ch_val[6]  = ((sb_byte[8] >> 2 	| (sb_byte[9] << 6)) & 0x07FF);
    ch_val[7]  = ((sb_byte[9] >> 5 	| (sb_byte[10] << 3)) & 0x07FF);
    ch_val[8]  = ((sb_byte[11] 		| (sb_byte[12] << 8)) & 0x07FF);
    ch_val[9]  = ((sb_byte[12] >> 3 | (sb_byte[13] << 5)) & 0x07FF);
    ch_val[10] = ((sb_byte[13] >> 6 | (sb_byte[14] << 2) | (sb_byte[15] << 10)) & 0x07FF);
    ch_val[11] = ((sb_byte[15] >> 1 | (sb_byte[16] << 7)) & 0x07FF);
    ch_val[12] = ((sb_byte[16] >> 4 | (sb_byte[17] << 4)) & 0x07FF);
    ch_val[13] = ((sb_byte[17] >> 7 | (sb_byte[18] << 1) | (sb_byte[19] << 9)) & 0x07FF);
    ch_val[14] = ((sb_byte[19] >> 2 | (sb_byte[20] << 6)) & 0x07FF);
    ch_val[15] = ((sb_byte[20] >> 5 | (sb_byte[21] << 3)) & 0x07FF);
}

/* @brief: This function used for encode CRSF pay load
 * @return: no return
 * */
void encode_crsf_channels(const uint16_t *ch, uint8_t *frame)
{
    frame[0] = 0xC8;       		// CRSF header
    frame[1] = 24;        		// length = 1 (type) + 22 (payload) + 1 (CRC)
    frame[2] = 0x16;       		// type = RC Channels

    uint8_t *p = &frame[3];  	// payload pointer

    p[0]  = (uint8_t)(ch[0] & 0xFF);
    p[1]  = (uint8_t)((ch[0] >> 8) 	| (ch[1] << 3));
    p[2]  = (uint8_t)((ch[1] >> 5) 	| (ch[2] << 6));
    p[3]  = (uint8_t)(ch[2] >> 2);
    p[4]  = (uint8_t)((ch[2] >> 10) | (ch[3] << 1));
    p[5]  = (uint8_t)((ch[3] >> 7) 	| (ch[4] << 4));
    p[6]  = (uint8_t)((ch[4] >> 4) 	| (ch[5] << 7));
    p[7]  = (uint8_t)(ch[5] >> 1);
    p[8]  = (uint8_t)((ch[5] >> 9) 	| (ch[6] << 2));
    p[9]  = (uint8_t)((ch[6] >> 6) 	| (ch[7] << 5));
    p[10] = (uint8_t)(ch[7] >> 3);

    p[11] = (uint8_t)(ch[8] & 0xFF);
    p[12] = (uint8_t)((ch[8] >> 8) 	| (ch[9] << 3));
    p[13] = (uint8_t)((ch[9] >> 5) 	| (ch[10] << 6));
    p[14] = (uint8_t)(ch[10] >> 2);
    p[15] = (uint8_t)((ch[10] >> 10)| (ch[11] << 1));
    p[16] = (uint8_t)((ch[11] >> 7) | (ch[12] << 4));
    p[17] = (uint8_t)((ch[12] >> 4) | (ch[13] << 7));
    p[18] = (uint8_t)(ch[13] >> 1);
    p[19] = (uint8_t)((ch[13] >> 9) | (ch[14] << 2));
    p[20] = (uint8_t)((ch[14] >> 6) | (ch[15] << 5));
    p[21] = (uint8_t)(ch[15] >> 3);

    // Tính CRC cho phần [type + payload]
    frame[25] = crsf_crc8(&frame[2], 23);
}

char str[64];
void encode_string_channels(const uint16_t *ch)
{
	 snprintf(str, sizeof(str), "%u,%u,%u,%u\n", ch[0], ch[1], ch[2], ch[3]);
}

/* @brief: This function used for assign channel value
 * @return: no return
 * */
E_HYP_ReturnCode hypmotion_AssignCRSFvalueToChannels(hypmotion_crsf_protocol_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	hyp_joystick_t	*Joystick = handle->joystick;

	handle->ch[0] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_0, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[1] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_1, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[2] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_2, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[3] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_3, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[4] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_4, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[5] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_5, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[6] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_6, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[7] 	= map(Joystick->hypmotion_adc.adc_lowpass.adc_value_7, ADC_VALUE_MIN, ADC_VALUE_MAX, CRSF_VALUE_MIN, CRSF_VALUE_MAX);
	handle->ch[8] 	= map(Joystick->button.button_1, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);
	handle->ch[9] 	= map(Joystick->button.button_2, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);
	handle->ch[10] 	= map(Joystick->button.button_3, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);
	handle->ch[11] 	= map(Joystick->button.nv_js_east, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);
	handle->ch[12] 	= map(Joystick->button.nv_js_north, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);
	handle->ch[13]	= map(Joystick->button.nv_js_south, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);
	handle->ch[14] 	= map(Joystick->button.nv_js_west, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);
	handle->ch[15] 	= map(Joystick->button.nv_js_validation, 0, 1, CRSF_VALUE_MAX, CRSF_VALUE_MIN);


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/*===============================================================
 *  						FreeRTOS
 * =============================================================*/
void hyp_CRSFTask(void const *argument)
{
	for(;;)
	{
//		hypmotion_crsf_protocol_process(pCRSF);

		osDelay(1);
	}

}

/* @brief: This function used for init hypmotion crsf protocol
 * @return: hypmotion system return
 * */
E_HYP_ReturnCode hypmotion_crsf_protocol_initialize(hypmotion_crsf_protocol_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	/* Assign pointer FreeRTOS */
	pCRSF = handle;

	/* Assign function pointer */
//	handle->uartHandle = &huart3;
//	handle->hyp_uart_receiveDMA  = HAL_UART_Receive_DMA;
//	handle->hyp_uart_transmitDMA = HAL_UART_Transmit_DMA;

	hypmotion_bsp_uart_initialize(handle->uart);

	handle->uart->uartHandle		  	= &huart1;
	handle->uart->hyp_uart_receiveDMA  	= HAL_UART_Receive_DMA;
	handle->uart->hyp_uart_transmitDMA 	= HAL_UART_Transmit_DMA;

	/* Create MAVLink FreeRTOS Task */
	osThreadDef(CRSFTask, hyp_CRSFTask, osPriorityNormal, 0, 512);
	handle->ID.Id = osThreadCreate(osThread(CRSFTask), NULL);

	if(handle->ID.Id == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/* @brief: This function used for process hypmotion crsf protocol
 * @return: hypmotion system return
 * */
E_HYP_ReturnCode hypmotion_crsf_protocol_process(hypmotion_crsf_protocol_t *handle)
{
	if(handle == NULL) return HYP_SYSTEM_RETURN_CODE_POINTER_IS_NULL;

	/* Assign value to handle->ch */
	if(hypmotion_AssignCRSFvalueToChannels(handle) != HYP_SYSTEM_RETURN_CODE_SUCCESS)
	{
		return  HYP_SYSTEM_RETURN_CODE_ERROR;
	}

	/* encode ch[16] to crsf_frame[26] */
//	encode_crsf_channels(handle->ch, handle->crsf_frame);
	encode_string_channels(handle->ch);

	/* send crsf frame with 200Hz frequency */
	handle->time.timeSendCRSF = hyp_getTimeMS();

	if(handle->time.timeSendCRSF - handle->time.elapseTimeSendCRSF >= 4 &&
			__HAL_DMA_GET_COUNTER(handle->uart->uartHandle->hdmatx) == 0)
	{
		handle->time.elapseTimeSendCRSF = handle->time.timeSendCRSF;

//		handle->uart->hyp_uart_transmitDMA(handle->uart->uartHandle, handle->crsf_frame, sizeof(handle->crsf_frame));

		handle->uart->hyp_uart_transmitDMA(handle->uart->uartHandle, (uint8_t*)str, strlen(str));

	}


	return HYP_SYSTEM_RETURN_CODE_SUCCESS;
}

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
