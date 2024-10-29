#include <FastLED.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_NeoPixel.h>

Adafruit_ADS1115 ads;
// Define the number of LEDs and the data pin for the output (if using NeoPixels)
#define NUM_LEDS 300
#define DATA_PIN 13 // Pin to the WS2812/NeoPixel strip (if using digital LEDs)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(300, 13, NEO_GRB + NEO_KHZ800); //If you notice your LEDs are the wrong colors, you might need to change to NEO_RGB, NEO_GBR, etc. You have to play around to find the right one.
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 2;
int positionStep = 0;
float divisor = float(215)/float(255);

#define SWITCH_PIN 12

void setup() {
  
  Serial.begin(115200);

  //If you are getting "Failed to initialize", then most likely your ADS is not at address 0x48. You'll need to look up code online to find the address of your ADS1115
  if (!ads.begin(0x48)) {
      Serial.println("Failed to initialize ADS.");
      while (1);
    }

    ads.setDataRate(RATE_ADS1115_128SPS); //Any higher than this rate seemed to cause too much blinking

  pixels.begin();
  pixels.clear();
  pixels.setBrightness(100);
  pixels.show();
}

void loop() {
  unsigned long currentMillis = millis();
  int inputSwitch = digitalRead(SWITCH_PIN);
  if ((currentMillis - startMillis >= period)) 
  {
      if(inputSwitch == 0) {
        int16_t adc0, adc1, adc2, adc3;
        float volts0, volts1, volts2, volts3;

        adc0 = ads.readADC_SingleEnded(0);
        adc1 = ads.readADC_SingleEnded(1);
        adc2 = ads.readADC_SingleEnded(2);
        adc3 = ads.readADC_SingleEnded(3);

        int blue = map(adc2, 17400, 20200, 255, 0);
        if(blue > 255)
          blue = 255;
        if(blue < 5)
          blue = 0;  
        int red = map(adc1, 17400, 20200, 255, 0);
        if(red > 255)
          red = 255;
        if(red < 5)
          red = 0;  
        int green = map(adc3, 11400, 20200, 255, 0);
        if(green > 255)
          green = 255;
        if(green < 5)
          green = 0;  

        for (int i = 0; i < NUM_LEDS; i++) {
          
          pixels.setPixelColor(i, red, green, blue);
        }
        Serial.println("-----");
        Serial.print("Red: "); Serial.print(adc1); Serial.print(" --- "); Serial.print(red);Serial.print(" Green: "); Serial.print(adc3); Serial.print(" Blue: "); Serial.print(adc2);
        pixels.show();
      }
      else if(inputSwitch == 1){
          colorChange(currentMillis);
      }

  startMillis = currentMillis;
  }
    
}

void colorChange(long time) {
    //input code to create whatever preprogrammed pattern you want here
}
