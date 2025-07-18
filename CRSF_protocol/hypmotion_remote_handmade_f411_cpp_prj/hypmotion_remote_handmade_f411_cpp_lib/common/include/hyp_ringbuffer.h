/**
  ******************************************************************************
  * @file    hypmotion_ringbuffer.h
  * @author  HYPMOTION Firmware Team
  * @version V1.0.0
  * @date    ${date}
  * @brief   This file contains all the functions prototypes for the hypmotion_ringbuffer.c
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

#ifndef HYPMOTION_RINGBUFFER_H_
#define HYPMOTION_RINGBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

/*INCLUDE--------------------------------------------------------*/
#include <stdint.h>
#include <string.h>

/*DEFINE--------------------------------------------------------*/
#define BUFFER_SIZE 256


/*STRUCTURE--------------------------------------------------------*/
typedef struct {
    uint8_t buffer[BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} RingBuffer;


/*FUNCTION--------------------------------------------------------*/
void RingBuffer_Init(RingBuffer *ringBuffer);

uint16_t RingBuffer_Write(RingBuffer *ringBuffer, const uint8_t *data, uint16_t len);

uint16_t RingBuffer_Read(RingBuffer *ringBuffer, uint8_t *data, uint16_t len);

uint16_t RingBuffer_Available(RingBuffer *ringBuffer);

uint16_t RingBuffer_Space(RingBuffer *ringBuffer);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /*HYPMOTION_RINGBUFFER_H_*/

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
