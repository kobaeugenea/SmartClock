#ifndef KEA_SC_QUEUEU_H
#define KEA_SC_QUEUEU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
  //size must be a power of two: 4,8,16,32...128
  void **buf;
  uint8_t tail;
  uint8_t head;
  uint8_t size;
} kea_sc_QueueData;

typedef struct
{
  kea_sc_QueueData* (*const init)(uint8_t bufferSize);
  uint8_t (*const count)(kea_sc_QueueData *);
  uint8_t (*const size)(kea_sc_QueueData *);
  bool (*const isFull)(kea_sc_QueueData *);
  bool (*const isEmpty)(kea_sc_QueueData *);
  uint8_t (*const space)(kea_sc_QueueData *);
  void (*const push)(kea_sc_QueueData *, void *elem);
  void *(*const front)(kea_sc_QueueData *);
  void (*const pop)(kea_sc_QueueData *);
  void (*const flush)(kea_sc_QueueData *);
} kea_sc_Queue_n;
extern kea_sc_Queue_n const kea_sc_Queue;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define QueueData kea_sc_QueueData
#define Queue kea_sc_Queue
#endif

#endif