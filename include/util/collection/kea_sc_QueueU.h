#ifndef KEA_SC_QUEUEU_H
#define KEA_SC_QUEUEU_H
 
//size must be a power of two: 4,8,16,32...128
#define kea_sc_QueueData( size )\
  struct {\
    void* buf[size];\
    unsigned char tail;\
    unsigned char head;\
  } 
 
#define kea_sc_Qeueu_count(fifo)     (fifo.head-fifo.tail)
 
#define kea_sc_Qeueu_size(fifo)      ( sizeof(fifo.buf)/sizeof(fifo.buf[0]) )
 
#define kea_sc_Qeueu_isFull(fifo)   (kea_sc_Qeueu_count(fifo)==kea_sc_Qeueu_size(fifo))
 
#define kea_sc_Qeueu_isEmpty(fifo)  (fifo.tail==fifo.head)
 
#define kea_sc_Qeueu_space(fifo)     (kea_sc_Qeueu_size(fifo)-kea_sc_Qeueu_count(fifo))
 
#define kea_sc_Qeueu_push(fifo, byte) \
  {\
    fifo.buf[fifo.head & (kea_sc_Qeueu_size(fifo)-1)]=byte;\
    fifo.head++;\
  }
 
#define kea_sc_Qeueu_front(fifo) (fifo.buf[fifo.tail & (kea_sc_Qeueu_size(fifo)-1)])
 
#define kea_sc_Qeueu_pop(fifo)   \
  {\
      fifo.tail++; \
  }
 
#define kea_sc_Qeueu_flush(fifo)   \
  {\
    fifo.tail=0;\
    fifo.head=0;\
  } 
 
#endif