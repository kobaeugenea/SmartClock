#ifndef KEA_SC_WIFISERVICE_H
#define KEA_SC_WIFISERVICE_H

typedef struct
{
    void (*const init)(void);
} kea_sc_WifiService_n;
extern kea_sc_WifiService_n const kea_sc_WifiService;

#ifndef KEA_SC_DISABLE_SHORT_NAME
#define WifiService kea_sc_WifiService 
#endif

#endif