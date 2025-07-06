#include "ring.h"


ring_stt_e RINGBUF_Init(RINGBUF* ring, uint8_t* buf, uint32_t max_size){
    if(!buf || max_size == 0)
        return RING_FAIL;
    ring->write = 0;
    ring->read = 0;
    ring->buf = buf;
    ring->size = max_size;
    return RING_OK;
}


ring_stt_e RINGBUF_Put(RINGBUF* ring, uint8_t data){
    uint16_t temp = ring->write;
    temp++;
    if(temp >= ring->size){ 
        temp = 0;
    }
    if(temp == ring->read){ //full
        return RING_FAIL;
    }
    ring->buf[ring->write] = data;
    ring->write = temp;
    return RING_OK;
}

ring_stt_e RINGBUF_Get(RINGBUF* ring, uint8_t* data){
    if(ring->write == ring->read){ //empty
        return RING_FAIL;
    }
    *data = ring->buf[ring->read];
    ring->read++;
    if(ring->read >= ring->size){
        ring->read = 0;
    }
    return RING_OK;
}