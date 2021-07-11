#include "util/kea_sc_FreeRTOSConfigU.h"

#include <Arduino.h>
#include "component/display/kea_sc_DisplayC.h"
#include "service/kea_sc_DateS.h"
#include "service/kea_sc_WifiS.h"

void startJobs() {
}

void initComponents() {
  kea_sc_DisplayC_init();
}

void initServices() {
  kea_sc_WifiS_init();
  kea_sc_DateS_init();
}


extern "C" void app_main() {
  initArduino();
  startJobs();
  initComponents();
  initServices();

  kea_sc_DateS_Date date;
  
  kea_sc_DisplayC_Id displayId = kea_sc_DisplayC_getDisplayDisplayId(0);
  while (true)
  {
    date = kea_sc_DateS_getCurrentDate();
    kea_sc_DisplayC_displayDate(displayId, date);
  }

  
}