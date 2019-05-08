#include "U8glib.h"
#include <DS3231.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

U8GLIB_ST7920_128X64_4X u8g(11, 10, 9);
//RS - D9 
//R/W - D10
//E - D11

DS3231  rtc(A4, A5);

#define ONE_WIRE_BUS 8                  // DS POD D8
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin, false);
static const double DOM_LAT = 51.712428, DOM_LON = 19.448561;

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

const uint8_t honda[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xE0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xC0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFE, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x03, 0xE0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x7F, 0xC0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFE, 0x00, 0x0F, 0xFF, 0x80, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFC, 0x00, 0x3F, 0xFF, 0xFE, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 0xFC, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF8, 0x00, 0x7F, 0xFF, 0xFF, 0xF8, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF0, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFE, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFC, 0x00, 0x7F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x7F, 0xFF, 0xF8, 0x01, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x1F, 0xFE, 0x00, 0x00, 0x00,
  0x00, 0x07, 0xFF, 0xFF, 0x80, 0x3F, 0xFF, 0xFF, 0xF0, 0x00, 0x07, 0xFF, 0xFC, 0x00, 0x00, 0x00,
  0x00, 0x3F, 0xFF, 0xF0, 0x07, 0xFF, 0xFF, 0xFC, 0x00, 0x03, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00,
  0x03, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00,
  0x0F, 0xFF, 0xE0, 0x1F, 0xFF, 0xFF, 0xC0, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00,
  0x3F, 0xFE, 0x01, 0xFF, 0xFF, 0xF0, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0xE0, 0x3F, 0xFF, 0xFC, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x07, 0xFF, 0xFF, 0xE0, 0x01, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFE, 0x3F, 0xFF, 0xFF, 0xC0, 0x7F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFC, 0x7F, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x00,
  0xFC, 0x7F, 0xF8, 0x07, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0F, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00,
  0x7E, 0x3E, 0x03, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x3F, 0x80, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0xC7, 0xFF, 0xFF, 0xFC, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0xF1, 0xFF, 0xF8, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xFC, 0x7C, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x3F, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x1F, 0xE3, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0xF8, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xFE, 0x60, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x3F, 0xC7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x1F, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xF1, 0xFF, 0xC1, 0xFF, 0xF8, 0x3F, 0xFC, 0x1F, 0xF3, 0xFF, 0xFF, 0x00, 0x03, 0xF8, 0x00,
  0xFF, 0xF1, 0xFF, 0xC7, 0xFF, 0xFE, 0x3F, 0xFE, 0x1F, 0xF3, 0xFF, 0xFF, 0xE0, 0x07, 0xFC, 0x00,
  0x1F, 0x80, 0x3E, 0x0F, 0xE0, 0x7F, 0x87, 0xBF, 0x03, 0x80, 0x7C, 0x03, 0xF0, 0x0F, 0x1E, 0x00,
  0x1F, 0x80, 0x3E, 0x1F, 0xC0, 0x3F, 0x87, 0x9F, 0xC3, 0x80, 0x7C, 0x01, 0xF8, 0x1E, 0x0F, 0x00,
  0x1F, 0xFF, 0xFE, 0x1F, 0x80, 0x1F, 0x87, 0x8F, 0xE3, 0x80, 0x7C, 0x00, 0xF8, 0x3F, 0x1F, 0x80,
  0x1F, 0xFF, 0xFE, 0x1F, 0x80, 0x1F, 0x87, 0x87, 0xF3, 0x80, 0x7C, 0x00, 0xF8, 0x3F, 0xFF, 0xC0,
  0x1F, 0x80, 0x3E, 0x1F, 0xC0, 0x3F, 0x87, 0x83, 0xFF, 0x80, 0x7C, 0x01, 0xF8, 0x78, 0x03, 0xE0,
  0x1F, 0x80, 0x3E, 0x0F, 0xF0, 0xFF, 0x07, 0x81, 0xFF, 0x80, 0x7C, 0x03, 0xF0, 0xF0, 0x01, 0xF0,
  0xFF, 0xF1, 0xFF, 0xC3, 0xFF, 0xFC, 0x3F, 0xE0, 0xFF, 0x83, 0xFF, 0xFF, 0xC3, 0xFE, 0x07, 0xFC,
  0xFF, 0xF1, 0xFF, 0xC0, 0xFF, 0xF0, 0x3F, 0xE0, 0x7F, 0x83, 0xFF, 0xFF, 0x83, 0xFE, 0x07, 0xFC
};

const uint8_t termometr[] PROGMEM = {
  0x07, 0x00, 0x0D, 0x80, 0x08, 0x80, 0x08, 0x80, 0x08, 0x9E, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80,
  0x08, 0x80, 0x08, 0x9E, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x08, 0x9E, 0x08, 0x80,
  0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x08, 0x9E, 0x08, 0x80, 0x08, 0x80, 0x1A, 0xC0, 0x32, 0x60,
  0x27, 0x20, 0x6F, 0xB0, 0x6F, 0xB0, 0x67, 0x30, 0x32, 0x60, 0x18, 0xC0, 0x0F, 0x80, 0x07, 0x00
};


const uint8_t aku05[] PROGMEM = {
  0x07, 0xE0, 0x07, 0xE0, 0x3F, 0xFC, 0x60, 0x06, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03,
  0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03,
  0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03,
  0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0xC0, 0x03, 0x7F, 0xFE, 0x3F, 0xFC
};


float temperature;
char temperatureString[6] = "-";
char wyswysokosc[6] = "-";
char wyspredkosc[6] = "-";
char wysdom[6] = "-";

float R1 = 4660; // Prawdziwa rezystancja R1 (4,7K)
float R2 = 1995; // Prawdziwa rezystancja R2 (2K)

float wartosc = 0;
float vout = 0.0;
float vin = 0.0;
int analogInput = 0; // POMIAR NAPIĘCIA NA A0
char napieciestr[6] = "-";
int wystemp = 0;
float wysnap = 0;
int wybor = 0;
int predkosc = 0;
float dodomu=0.0;
int wysokosc = 0;
int counter=0;
int counter2=0;

const int buttonPin = 2;
int buttonState = 0;

void setup() {
  rtc.begin();
  sensors.begin();
  sensors.setResolution(0, 10);
  pinMode(analogInput, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  ss.begin(GPSBaud);
  u8g.firstPage();
  do {
    u8g.drawBitmapP( 0, 0, 16, 64, honda);
  } while ( u8g.nextPage() );
  delay(3000);
}

void loop() {

  counter++;
  counter2++;
  
  if(counter>30)
  {
    sensors.requestTemperatures();
    temperature = sensors.getTempCByIndex(0);
    counter=0;
  }
  if(temperature<-9.9)
  {
    dtostrf(temperature, 2, 0, temperatureString);
  }
  else
  {
  dtostrf(temperature, 2, 1, temperatureString);
  }
  wystemp = temperature / 2;


  wartosc = analogRead(analogInput);
  vout = (wartosc * 4.93) / 1024.0; //4.74 = Wartość napięcia między AREF a GND
  vin = vout / (R2 / (R1 + R2));
  dtostrf(vin, 2, 1, napieciestr);
  wysnap = (vin * 11) - (110 + (vin * 1.9));

  wysokosc = gps.altitude.meters();
  dtostrf(wysokosc, 4, 0, wyswysokosc);
  predkosc = gps.speed.kmph();
  if (predkosc<3)
  {
    predkosc = 0;
  }
  dtostrf(predkosc, 3, 0, wyspredkosc);
  unsigned long distanceToDom =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      DOM_LAT, 
      DOM_LON);

  dodomu = distanceToDom/1000.0;
  if(dodomu<10.0)
  {
    dtostrf(dodomu, 4, 1, wysdom); 
  }
  else
  {
  dtostrf(dodomu, 4, 0, wysdom); 
  }
  
  
  u8g.firstPage();
  do {
    u8g.drawLine(0, 13, 128, 13);
    u8g.drawLine(0, 51, 128, 51);
    u8g.setFont(u8g_font_fub11);
    u8g.drawStr( 0, 11, rtc.getTimeStr());
    u8g.drawStr( 62, 11, rtc.getDateStr());
    u8g.setFont(u8g_font_fub17n);
    if (temperature > 38)
    {
      u8g.drawBitmapP( 0, 17, 2, 32, termometr);
      u8g.drawStr( 15, 40,  temperatureString);
      u8g.drawLine(6, 38, 6, 23);
    }
    else if (temperature < -5)
    {
      u8g.drawBitmapP( 0, 17, 2, 32, termometr);
      u8g.drawStr( 15, 40,  temperatureString);

    }
    else
    {
      u8g.drawBitmapP( 0, 17, 2, 32, termometr);
      u8g.drawStr( 15, 40,  temperatureString);
      u8g.drawLine(6, 38, 6, 38 - wystemp);
    }
    if (vin > 14.7)
    {
      u8g.drawBitmapP( 63, 17, 2, 32, aku05);
      u8g.drawStr( 81, 40, napieciestr);
      u8g.drawBox(68,41,6,4);
      u8g.drawBox(68,23,6,15);
    }
    else if (vin < 12)
    {
      u8g.drawBitmapP( 63, 17, 2, 32, aku05);
      u8g.drawStr( 81, 40, napieciestr);
    }
    else
    {
      u8g.drawBitmapP( 63, 17, 2, 32, aku05);
      u8g.drawStr( 81, 40, napieciestr);
      u8g.drawLine(67, 45, 67, 45 - wysnap);
      u8g.drawLine(68, 45, 68, 45 - wysnap);
      u8g.drawLine(69, 45, 69, 45 - wysnap);
      u8g.drawLine(70, 45, 70, 45 - wysnap);
      u8g.drawLine(71, 45, 71, 45 - wysnap);
      u8g.drawLine(72, 45, 72, 45 - wysnap);
      u8g.drawLine(73, 45, 73, 45 - wysnap);
      u8g.drawLine(74, 45, 74, 45 - wysnap);
    }

    buttonState = digitalRead(buttonPin);
     
     switch (wybor)
     {
       case 0:
       u8g.setFont(u8g_font_fub11);
       u8g.drawStr( 0, 64, "Predk: ");
       u8g.drawStr( 52, 64, wyspredkosc);
       u8g.drawStr( 89, 64, "km/h");
       if(buttonState == LOW && counter2>1)
       {
          wybor = 1;
          counter2=0;
       }
       break;
       case 1:
       u8g.setFont(u8g_font_fub11);
       u8g.drawStr( 12, 64, wyswysokosc);
       u8g.drawStr( 50, 62, "m n.p.m.");
       if(buttonState == LOW && counter2>1)
       {
          wybor = 2;
          counter2=0;
       }
       break;
       case 2:
       u8g.setFont(u8g_font_fub11);
       u8g.drawStr( 0, 64, "Do domu");
       u8g.drawStr( 70, 64, wysdom);
       u8g.drawStr( 106, 64, "km");
       if(buttonState == LOW && counter2>1)
       {
          wybor = 0;
          counter2=0;
       }
       break;
     }
  } while ( u8g.nextPage() );

  smartDelay(500);

}
