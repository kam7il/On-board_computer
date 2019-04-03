#include "U8glib.h"
#include <DS3231.h>

U8GLIB_ST7920_128X64_4X u8g(11, 10, 9);

DS3231  rtc(A4, A5);

void setup() {
  rtc.begin();

}

void loop() {
  u8g.firstPage();
  do {
    u8g.drawLine(0, 13, 128, 13);
    u8g.drawLine(0, 51, 128, 51);
    u8g.setFont(u8g_font_fub11);
    u8g.drawStr( 0, 11, rtc.getTimeStr());
    u8g.drawStr( 62, 11, rtc.getDateStr());
  } while ( u8g.nextPage() );

}
