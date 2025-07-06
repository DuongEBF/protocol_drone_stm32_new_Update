#ifndef _RING
#define _RING
#include <stdint.h>

typedef enum{
    RING_FAIL = -1,
    RING_OK = 0,
}ring_stt_e;

typedef struct
{
    uint32_t write;
    uint32_t read;
    uint32_t size;
    uint8_t* buf;
}RINGBUF;
ring_stt_e RINGBUF_Init(RINGBUF* ring, uint8_t* buf, uint32_t max_size);
ring_stt_e RINGBUF_Put(RINGBUF* ring, uint8_t data);
ring_stt_e RINGBUF_Get(RINGBUF* ring, uint8_t* data);
#endif