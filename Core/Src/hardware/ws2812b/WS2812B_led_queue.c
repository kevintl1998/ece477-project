#include "hardware/ws2812b/WS2812B_led_queue.h"
#include "stm32f0xx.h"

#define _WSLED_IS_QUEUE_EMPTY(q) q->size == 0
#define _WSLED_IS_QUEUE_FULL(q)  q->size == q->max_size
#define _WSLED_QUEUE_PEEK(q) 	 q->size == 0 ? QUEUE_NULL : &(q->arr[q->tail])

ColorData* WSLED_QueuePop(WSLED_Queue* q);


void WSLED_QueueInit(WSLED_Queue* q, ColorData* arr, uint32_t max_size) {
    q->arr = arr;
    q->max_size = max_size;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

// DOES NOT ENFORCE ATOMIC READ ACCESS TO THE LED QUEUE
ColorData* WSLED_QueueNextColor(WSLED_Queue* q) {
	// does not need to be atomic because it will only be used by the dma transfer complete interrupt
    // keeps decrementing hold_cycles until it has reached 0
    // then pop that color off of the queue
    ColorData* d = _WSLED_QUEUE_PEEK(q);
    if (d == QUEUE_NULL) return QUEUE_NULL;
    if (d->hold_cycles > 0) {
        d->hold_cycles--;
        // returns null after sending the value once because the update function will not update the
        // led values if the return value from this function is null
        // this is done to save cpu cycles
        return d->hold_cycles + 1 == d->total_hold_cycles ? d : QUEUE_NULL;
    } else {
    	WSLED_QueuePop(q);
        return WSLED_QueueNextColor(q);
    }
}

// ENFORCES ATOMIC WRITE ACCESS TO THE LED QUEUE
int WSLED_QueueAdd(WSLED_Queue* q, uint8_t r, uint8_t g, uint8_t b, uint32_t hold_cycles) {
	__disable_irq(); // this function must be atomic in case there are multiple interrupts calling it
    if(_WSLED_IS_QUEUE_FULL(q)) {
    	__enable_irq();
        return QUEUE_FAIL;
    }
    ColorData* data = &(q->arr[q->head]);
    q->head = (++q->head) % q->max_size;
    data->r = r;
    data->g = g;
    data->b = b;
    data->hold_cycles = hold_cycles;
    data->total_hold_cycles = hold_cycles;
    q->size++;
    __enable_irq();
    return QUEUE_SUCCESS;
}


ColorData* WSLED_QueuePop(WSLED_Queue* q) {
    if(_WSLED_IS_QUEUE_EMPTY(q)) {
        return QUEUE_NULL;
    }
    ColorData* item = &(q->arr[q->tail]);
    q->tail = (++q->tail) % q->max_size;
    q->size--;
    return item;
}

//ColorData* WSLED_QueuePeek(WSLED_Queue* q) {
//    return q->size == 0 ? QUEUE_NULL : &(q->arr[q->tail]);
//}
