
#include <DS3231.h>

DS3231  rtc(A4, A5);

void setup() {
  
  rtc.begin();
  rtc.setTime(16,23,00); //HH/MIN/SEC
  rtc.setDate(13,03,2019); //DD/MM/YEAR

}

void loop() {
  

}
