/**
  ******************************************************************************
  * @file    hypmotion_ringbuffer.c
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

/*INCLUDE--------------------------------------------------------*/
#include "common/include/hyp_ringbuffer.h"


/*FUNCTION--------------------------------------------------------*/
void RingBuffer_Init(RingBuffer *ringBuffer)
{
    ringBuffer->head = 0;
    ringBuffer->tail = 0;
}


uint16_t RingBuffer_Write(RingBuffer *ringBuffer, const uint8_t *data, uint16_t len)
{
    uint16_t i;

    for (i = 0; i < len; i++)
    {
        uint16_t next = (ringBuffer->head + 1) % BUFFER_SIZE;

        if (next == ringBuffer->tail)
        {
            break; // Buffer full
        }

        ringBuffer->buffer[ringBuffer->head] = data[i];

        ringBuffer->head = next;
    }

    return i;
}


uint16_t RingBuffer_Read(RingBuffer *ringBuffer, uint8_t *data, uint16_t len)
{
    uint16_t i;

    for (i = 0; i < len; i++)
    {
        if (ringBuffer->tail == ringBuffer->head)
        {
            break; // Buffer empty
        }

        data[i] = ringBuffer->buffer[ringBuffer->tail];

        ringBuffer->tail = (ringBuffer->tail + 1) % BUFFER_SIZE;

    }

    return i;
}


uint16_t RingBuffer_Available(RingBuffer *ringBuffer)
{
    return (BUFFER_SIZE + ringBuffer->head - ringBuffer->tail) % BUFFER_SIZE;
}


uint16_t RingBuffer_Space(RingBuffer *ringBuffer)
{
    return (BUFFER_SIZE - RingBuffer_Available(ringBuffer) - 1);
}

/************************ (C) COPYRIGHT HYPMOTION *****END OF FILE****************/
