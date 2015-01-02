#include "SparkTime/SparkTime.h"
#include "neopixel/neopixel.h"

UDP UDPClient;
SparkTime rtc;

unsigned long currentTime;
unsigned long lastTime = 0UL;
String timeStr;

#define PIXEL_PIN A7
#define PIXEL_COUNT 12
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


void setup() {
  rtc.begin(&UDPClient, "north-america.pool.ntp.org");
  rtc.setTimeZone(1); // gmt offset
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {

    currentTime = rtc.now();

    //OI
    uint32_t base=strip.Color(0,5,0);
    if(rtc.hour(currentTime) > 7 && rtc.hour(currentTime) < 19){
        base=strip.Color(0,0,5);
    }
    strip.setPixelColor(0, base);
    strip.setPixelColor(1, base);
    strip.setPixelColor(2, base);
    strip.setPixelColor(3, base);
    strip.setPixelColor(4, base);
    strip.setPixelColor(5, base);
    strip.setPixelColor(6, base);
    strip.setPixelColor(7, base);
    strip.setPixelColor(8, base);
    strip.setPixelColor(9, base);
    strip.setPixelColor(10, base);
    uint8_t h = (rtc.hour(currentTime))%12 - 1;
    uint8_t m = (rtc.minute(currentTime))/5;
    uint8_t s = (rtc.second(currentTime))/5;
    Serial.print(h);
    Serial.print(" ");
    Serial.print(m);
    Serial.print("\r\n");
    strip.setPixelColor(s, 5,0,20);
    if(s==h){
    strip.setPixelColor(h, 37,0,30);

    }else{
    strip.setPixelColor(h, 33,0,10);
    }
    strip.setPixelColor(m, 10,0,0);
    strip.show();
}
