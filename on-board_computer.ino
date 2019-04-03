#include "U8glib.h"

U8GLIB_ST7920_128X64_1X u8g(11, 10, 9);  // SPI Com: SCK = E = D11, MOSI = R/W = D10, CS = RS = D9


void setup() {
 

}

void loop() {
  
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_ncenB14r);
  //  u8g.drawStr( 5, 22, "Hello World!");
//    u8g.setFont(u8g_font_fur14r);
    u8g.drawStr( 2, 42, "Witaj Swiecie!");
    
  } while( u8g.nextPage() );

  

  delay(1500);
}
