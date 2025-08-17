#include "queue_struct.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stdint.h"
queue_t* create_queue(int capacity){
    queue_t* qt = (queue_t*)malloc(1*sizeof(queue_t));
    qt->front = 0;
    qt->rear = -1;
    qt->used = 0;
    qt->capacity = capacity;
    qt->array = (buf_data_t*)malloc(capacity*sizeof(buf_data_t));
    return qt;
}


static bool isEmpty(queue_t* queue){
    return (queue->used == 0);
}
static bool isFull(queue_t* queue){
    return (queue->used == queue->capacity);
}


queue_stt_e enqueue(queue_t* queue, uint8_t* data, int len){
    if(isFull(queue)){ //neu full thi k add nua
        return QUEUE_FAIL;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    memcpy(queue->array[queue->rear].buf, data, len);
    queue->array[queue->rear].len = len;
    queue->used++;
    return QUEUE_OK;
}


queue_stt_e dequeue(queue_t* queue, uint8_t* data, int* len){
    if(isEmpty(queue)){
        return QUEUE_FAIL;
    }
    memcpy(data, queue->array[queue->front].buf, queue->array[queue->front].len);
    *len = queue->array[queue->front].len;
    queue->front = (queue->front + 1) % queue->capacity;
    queue->used--;
    return QUEUE_OK;
}

void free_queue(queue_t* queue) {
    if (queue == NULL) return;

    // Giải phóng mảng bên trong nếu đã được cấp phát
    if (queue->array != NULL) {
        free(queue->array);
    }

    // Giải phóng struct queue_t
    free(queue);
}