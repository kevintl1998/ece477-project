#include "hardware/ws2812b/WS2812B_led_queue.h"


void WSLED_QueueInit(WSLED_Queue* q, ColorData* arr, uint32_t max_size) {
    q->arr = arr;
    q->max_size = max_size;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

ColorData* WSLED_QueueNextColor(WSLED_Queue* q) {
    // keeps decrementing hold_cycles until it has reached 0
    // then pop that color off of the queue
    ColorData* d = WSLED_QueuePeek(q);
    if (d == QUEUE_NULL) return QUEUE_NULL;
    if (d->hold_cycles > 0) {
        d->hold_cycles--;
        // returns null because the update function will not update the
        // led values if the return value from this function is null
        return QUEUE_NULL;
    } else {
    	WSLED_QueuePop(q);
        return WSLED_QueueNextColor(q);
    }
//    if(d->hold_cycles <= 0) {
//        WaitQueuePop(q);
//        return WaitQueuePop(q);
//    }
}

int WSLED_QueueAdd(WSLED_Queue* q, uint8_t r, uint8_t g, uint8_t b, uint32_t hold_cycles) {
    if(WSLED_WaitQueueFull(q)) {
        return QUEUE_FAIL;
    }
    q->size++;
    ColorData* data = &(q->arr[q->head]);
    q->head = (++q->head) % q->max_size;
    data->r = r;
    data->g = g;
    data->b = b;
    data->hold_cycles = hold_cycles;
    return QUEUE_SUCCESS;
}

int WSLED_QueueEmpty(WSLED_Queue* q) {
    return q->size == 0;
}

int WSLED_QueueFull(WSLED_Queue* q) {
    return q->size == q->max_size;
}

ColorData* WSLED_QueuePop(WSLED_Queue* q) {
    if(WSLED_QueueEmpty(q)) {
        return QUEUE_NULL;
    }
    q->size--;
    ColorData* item = &(q->arr[q->tail]);
    q->tail = (++q->tail) % q->max_size;
    return item;
}

ColorData* WSLED_QueuePeek(WSLED_Queue* q) {
//    return WaitQueueEmpty(q) ? QUEUE_NULL : &(q->arr[q->tail]);
    if(WSLED_QueueEmpty(q)) {
        return QUEUE_NULL;
    }
    ColorData* temp = &(q->arr[q->tail]);
    return temp;
}
