#include "com/github/kobaeugenea/smartclock/util/FreeRTOSConfig.h"

#include <Arduino.h>
#include <tcpip_adapter.h>
#include "com/github/kobaeugenea/smartclock/service/component/DisplayService.h"
#include "com/github/kobaeugenea/smartclock/service/WifiService.h"
#include "com/github/kobaeugenea/smartclock/job/WebUI.h"

#include <esp_log.h>

void startJobs() {
  WebUI.startJob();
}

void initComponents() {
  DisaplyService.init();
}

void initServices() {
  WifiService.init();
  DateSerivce.init();
}


extern "C" void app_main() {
  initArduino();
  tcpip_adapter_init();
  startJobs();
  initServices(); //wifi should be initialized after WebUI as Services use settings!
  initComponents();

  uint8_t currentDisaplyNum = 0;
  Date date;
  
  while (true)
  {
    date = DateSerivce.getCurrentDate();
    DisaplyService.showDate(currentDisaplyNum, date);
  }

  
}