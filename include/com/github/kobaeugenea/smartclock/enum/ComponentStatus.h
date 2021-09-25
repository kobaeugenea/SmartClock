#ifndef KEA_SC_COMPONENTSTATUS_H
#define KEA_SC_COMPONENTSTATUS_H
 
typedef enum {
    kea_sc_ComponentStatus_OK,
    kea_sc_ComponentStatus_NOT_FOUND,
    kea_sc_ComponentStatus_NOT_CREATED,
} kea_sc_ComponentStatus;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define ComponentStatus kea_sc_ComponentStatus
#define ComponentStatus_OK kea_sc_ComponentStatus_OK
#define ComponentStatus_NOT_FOUND kea_sc_ComponentStatus_NOT_FOUND
#define ComponentStatus_NOT_CREATED kea_sc_ComponentStatus_NOT_CREATED
#endif
 
#endif