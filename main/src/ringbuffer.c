#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"
#include "ringbuffer.h"

RingBuffer *RingBuffer_create(int length)//make the struct
{
    RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
    buffer->length = length + 1;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = calloc(buffer->length, 1);

    return buffer;
}

void RingBuffer_destroy(RingBuffer *buffer)//end the pitiful life of the struct
{
    if(buffer) {
        free(buffer->buffer);
        free(buffer);
    }
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)//adds data to buffer
{
    if(RingBuffer_available_data(buffer) == 0) {//if full reset start and end to 0
        buffer->start = buffer->end = 0;
    }

    check(length <= RingBuffer_available_space(buffer), "Not enough space: %d requested, %d available", RingBuffer_available_data(buffer), length);//confirm enough room

    void *result = memcpy(RingBuffer_ends_at(buffer), data, length);//create space for data
    check(result != NULL, "Failed to write data into buffer.");

    RingBuffer_commit_write(buffer, length);//write data to buffer

    return length;
error:
    return -1;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)//read from buffer
{
    check_debug(amount <= RingBuffer_available_data(buffer),
        "Not enough in the buffer: has %d, needs %d",
        RingBuffer_availabe_data(buffer), amount);

    void *result = memcpy(target, RingBuffer_starts_at(buffer), amount);
    check(result != NULL, "Failed to write buffer into data.");

    RingBuffer_commit_read(buffer, amount);//see header file

    if(buffer->end == buffer->start) {
        buffer->start = buffer->end = 0;//reset to zero if needed
    }

    return amount;
error:
    return -1;
}

bstring RingBuffer_gets(RingBuffer *buffer, int amount)
{
    check(amount > 0, "Need more than 0 for gets, you gave: %d ", amount);
    check_debug(amount <= RingBuffer_availabe_data(buffer),
        "Not enough in the buffer.");//confirm enough room and that amount is actual amount

    bstring result = blk2bstr(RingBuffer_starts_at(buffer), amount);//creates copy of buffer of length amount returns NULL if error
    check(result != NULL, "Failed to create gets result.");
    check(blength(result) == amount, "Wrong result length.");

    RingBuffer_commit_read(buffer, amount);//header file for macro
    assert(RingBuffer_available_data(buffer) >= 0 && "Error in read commit.");

    return result;
error:
    return NULL;
}
