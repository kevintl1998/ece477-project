#ifndef WS2812B_LED_QUEUE_H
#define WS2812B_LED_QUEUE_H

#include <stdint.h>


#define DATA_BUFFER_SIZE 4

#define QUEUE_FAIL    1
#define QUEUE_SUCCESS 0
#define QUEUE_NULL    (void*)0x0

typedef struct ColorData {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint32_t hold_cycles;
    uint32_t total_hold_cycles;
} ColorData;

typedef struct WSLED_Queue {
    ColorData* arr;
    uint32_t size;
    uint32_t max_size;
    uint32_t head;
    uint32_t tail;
} WSLED_Queue;


void WSLED_QueueInit(WSLED_Queue* q, ColorData* arr, uint32_t max_size);

// This function is not atomic. This must be read by ONLY 1 interrupt or the main process
ColorData* WSLED_QueueNextColor(WSLED_Queue* q);


// adds item to queue
// return QUEUE_SUCCESS if successful, else return QUEUE_FAIL
// NOTE: adding a color to the wait queue with a hold_cycle < 1 will cause it to be skipped
// This function is atomic meaning that it can be called from anywhere (any interrupt/the main process)
int WSLED_QueueAdd(WSLED_Queue* q, uint8_t r, uint8_t g, uint8_t b, uint32_t hold_cycles);


#endif
