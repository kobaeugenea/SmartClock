#include "job/kea_sc_Ota.h"
#include <U8g2lib.h>

void startJobs() {
  kea_sc_OtaStart();
}

extern "C" void app_main() {
  initArduino();
  startJobs();

  u8g2_t u8g2;
  u8g2_Setup_max7219_64x8_1(&u8g2, U8G2_R0, u8x8_byte_arduino_4wire_sw_spi, u8x8_gpio_and_delay_arduino);
  u8x8_SetPin_4Wire_SW_SPI(u8g2_GetU8x8(&u8g2), 18, 23, 5, U8X8_PIN_NONE, U8X8_PIN_NONE);
  u8g2_InitDisplay(&u8g2);
  u8g2_ClearDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);
  u8g2_SetContrast(&u8g2, 160);
  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_victoriabold8_8r);
  u8g2_DrawStr(&u8g2, 0, 7, "LOVE");
  u8g2_SetDisplayRotation(&u8g2, U8G2_R2);
  u8g2_DrawStr(&u8g2, 0, 7, "U!!!");
  u8g2_SendBuffer(&u8g2);
}