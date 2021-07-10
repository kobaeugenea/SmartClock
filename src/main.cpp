#include "util/kea_sc_FreeRTOSConfigU.h"

#include <Arduino.h>
#include "component/display/kea_sc_DisplayC.h"
#include "service/kea_sc_DateS.h"

void startJobs() {
}

void initComponents() {
  kea_sc_DisplayC_init();
}

extern "C" void app_main() {
  initArduino();
  startJobs();
  initComponents();

  kea_sc_DateS_Date date;
  date.sec = 12;
  date.min = 16;
  date.hour = 2;
  date.day = 1;
  date.month = kea_sc_DateS_Month_JUN;
  date.year = 2003;
  date.dayOfWeek = kea_sc_DateS_Weekday_THU;
  kea_sc_DisplayC_Id displayId = kea_sc_DisplayC_getDisplayDisplayId(0);
  kea_sc_DisplayC_displayDate(displayId, date);
}