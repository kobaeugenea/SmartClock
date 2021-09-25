#include "com/github/kobaeugenea/smartclock/util/collection/Queue.h"
#include "com/github/kobaeugenea/smartclock/util/MemoryUtils.h"
 
static kea_sc_QueueData* init(uint8_t bufferSize) {
  kea_sc_QueueData* queueData = MemoryUtils.malloc(sizeof(kea_sc_QueueData));
  queueData->buf = MemoryUtils.malloc(bufferSize * sizeof(void *));
  return queueData;
}

static uint8_t count(kea_sc_QueueData* data) {
  return data->head - data->tail;
}

static uint8_t size(kea_sc_QueueData* data) {
  return data->size;
}

static bool isFull(kea_sc_QueueData* data) {
  return count(data) == size(data);
}

static bool isEmpty(kea_sc_QueueData* data) {
  return data->tail == data->head;
}

static uint8_t space(kea_sc_QueueData* data) {
  return size(data) - count(data);
}

static void push(kea_sc_QueueData* data, void* elem) {
  data->buf[data->head & (size(data)-1)] = elem;
  data->head++;
}

static void* front(kea_sc_QueueData* data) {
  return data->buf[data->tail & (size(data)-1)];
}

static void pop(kea_sc_QueueData* data) {
  data->tail++;
}

static void flush(kea_sc_QueueData* data) {
  data->tail = 0;
  data->head = 0;
}

kea_sc_Queue_n const kea_sc_Queue = {
  .init = init,
  .count = count,
  .size = size,
  .isFull = isFull,
  .isEmpty = isEmpty,
  .space = space,
  .push = push,
  .front = front,
  .pop = pop,
  .flush = flush
};