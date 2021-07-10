#ifndef KEA_SC_DISAPLYC_H
#define KEA_SC_DISAPLYC_H

#include "service/kea_sc_DateS.h"
#include "service/kea_sc_ComponentS.h"
#include "util/kea_sc_IdU.h"

typedef enum kea_sc_DisplayC_Type {
    kea_sc_DisplayC_Type_2X4MAX7219 = 0,
} kea_sc_DisplayC_Type;

typedef struct kea_sc_DisplayC_Id {
    uint8_t id;
    kea_sc_ComponentS_Id componentId;
    kea_sc_DisplayC_Type type;
    kea_sc_IdU_Status status;

} kea_sc_DisplayC_Id;

#ifdef __cplusplus
extern "C" {
#endif

//common displays methods
void kea_sc_DisplayC_init();
uint8_t kea_sc_DisplayC_getDisplaysCount();
kea_sc_DisplayC_Id kea_sc_DisplayC_getDisplayDisplayId(uint8_t n);
//end common displays methods

//work with particualr display
void kea_sc_DisplayC_displayDate(kea_sc_DisplayC_Id displayId, kea_sc_DateS_Date date);
//end work with particualr display

#ifdef __cplusplus
}
#endif

#endif