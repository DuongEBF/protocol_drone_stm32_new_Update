#ifndef _QUEUE
#define _QUEUE
#include <stdbool.h>
#include "stdint.h"
#define MAXSIZE 20
#define MAX_ELEMENT 10
typedef enum{
    QUEUE_FAIL = -1,
    QUEUE_OK = 0,
}queue_stt_e;

typedef struct{
    int len;
    uint8_t buf[MAXSIZE];
}buf_data_t;


typedef struct
{
    int front; //chi so cua phan tu dau queue
    int rear; //chi so cua phan tu cuoi queue
    int used; //so phan tu dang co trong queue
    int capacity; //so phan tu toi da cua queue
    buf_data_t* array; //con tro, tro den mang cua queue
}queue_t;
queue_t* create_queue(int capacity);
static bool isEmpty(queue_t* queue);
static bool isFull(queue_t* queue);
queue_stt_e enqueue(queue_t* queue, uint8_t* data, int len);
queue_stt_e dequeue(queue_t* queue, uint8_t* data, int* len);
void free_queue(queue_t* queue);
#endif