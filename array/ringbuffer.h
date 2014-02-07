#ifndef _ringbuffer_h
#define _ringbuffer_h

#include <string.h>

typedef struct {
    char *buffer;
    int length;
    int start;
    int end;
} RingBuffer;

RingBuffer *RingBuffer_create(int length);

void RingBuffer_destroy(RingBuffer *buffer);
int RingBuffer_read(RingBuffer *buffer, char *target, int amount);
int RingBuffer_write(RingBuffer *buffer, char *data, int length);
//int RingBuffer_empty(RingBuffer *buffer);
//int RingBuffer_full(RingBuffer *buffer);
//

#define RingBuffer_available_data(B) ()

#endif
