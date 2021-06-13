#include <U8g2lib.h>

U8G2_MAX7219_64X8_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* cs=*/ 5, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);


extern "C" void app_main() {
  u8g2.begin();
  u8g2.setContrast(10*16);
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_victoriabold8_8r);	// choose a suitable font
  u8g2.drawStr(0,7,"Love");			// write something to the internal memory
  u8g2.setDisplayRotation(U8G2_R2);
  u8g2.drawStr(0,7,"you!");			// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
}