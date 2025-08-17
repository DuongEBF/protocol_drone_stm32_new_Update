/**
  ******************************************************************************
  * @file    hyp_osThread.h
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_application.c
  *          firmware library
  *
  ******************************************************************************
  * @Copyright
  * COPYRIGHT NOTICE: (c) 2025 HYPMOTION. All rights reserved.
  *
  * The information contained herein is confidential
  * property of Company. The use, copying, transfer or
  * disclosure of such information is prohibited except
  * by express written agreement with Company.
  *
  ******************************************************************************
*/
#ifndef COMMON_HYP_OSTHREAD_H_
#define COMMON_HYP_OSTHREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
#include "cmsis_os.h"

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
typedef struct __T_HYP_OSTHREAD_INFO
{
	osThreadId		Id;

}hyp_osThread_inFo_t;

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* COMMON_HYP_OSTHREAD_H_ */

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
