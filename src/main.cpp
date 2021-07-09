#include <Arduino.h>
#include "job/kea_sc_OtaJ.h"
#include "component/display/kea_sc_DisplayC.h"
#include "service/kea_sc_DateS.h"

void startJobs() {
  kea_sc_OtaJ_start();
}

void initComponents() {
  kea_sc_DisplayC_init();
}

extern "C" void app_main() {
  initArduino();
  startJobs();
  initComponents();

  kea_sc_DateS_Date date;
  kea_sc_DisplayC_Id displayId = kea_sc_DisplayC_getDisplayDisplayId(0);
  kea_sc_DisplayC_displayDate(displayId, date);
}