/**
  ******************************************************************************
  * @file    hypmotion_remote_application.h
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_remote_application.c
  *          firmware library
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) 2024 HYPMOTION. All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/

#ifndef API_INCLUDE_HYP_REMOTECONTROLLER_API_H_
#define API_INCLUDE_HYP_REMOTECONTROLLER_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/*INCLUDE------------------------------------------------------------------*/
#include "math.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

#include <module/include/hyp_button.h>
#include <bsp/include/hyp_ADC.h>
#include <module/include/hyp_joystick.h>
#include <protocol/include/hyp_mavlink.h>
#include <protocol/include/hypmotion_CRSF.h>
#include <bsp/include/hyp_UART.h>

/*STRUCTURE----------------------------------------------------------------*/

typedef struct __T_HYP_REMOTECONTROLLER_API
{
	hyp_joystick_t				joystick;

	hyp_mavlink_t				mavlink;

	hypmotion_crsf_protocol_t	crsf;

	hyp_bsp_uart_t				bsp_uart;

	E_HYP_ReturnCode			returnCode;

}hyp_remoteController_api_t;

/*FUNCTION----------------------------------------------------------------------*/
E_HYP_ReturnCode hyp_remoteController_api_initialize(hyp_remoteController_api_t *handle);

E_HYP_ReturnCode hyp_remoteController_api_process(hyp_remoteController_api_t *handle);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* API_INCLUDE_HYP_REMOTECONTROLLER_API_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
