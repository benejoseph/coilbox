#include <Adafruit_NeoPixel.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <I2S.h>

#include "sinusoid_samples.h"

#define ON_BOARD_RGB_PIN (D4)
#define BEACON_PERIOD_MILLIS (5000)
#define VOLUME_DOWN_BITS (2)

int led = LED_BUILTIN;
Adafruit_NeoPixel on_board_rgb_led = Adafruit_NeoPixel(1, ON_BOARD_RGB_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_LIS3DH accel = Adafruit_LIS3DH();
unsigned int count = 0;

I2S i2s(OUTPUT);

bool is_playing_sound = false;

void PlayI2S(const int16_t *data, uint32_t len, uint32_t rate) {
  is_playing_sound = true;

  // start I2S at the sample rate with 16-bits per sample
  if (!i2s.begin(rate)) {
    Serial.println("Failed to initialize I2S!");
    delay(500);
    i2s.end();
    return;
  }
  
  for(uint32_t i=0; i<len; i++) {
   // uint16_t sample = (uint16_t)data[i] * 32;
    // write the same sample twice, once for left and once for the right channel
    int32_t signed_sample = static_cast<int32_t>(data[i]);
    signed_sample >>= VOLUME_DOWN_BITS;
    i2s.write(signed_sample);
    i2s.write(signed_sample);
  }
  i2s.end();
  is_playing_sound = false;
}


void setup() {
  pinMode(PIN_EXTERNAL_POWER, OUTPUT);

  // Some boards work best if we also make a serial connection
  Serial.begin(115200);

  // set LED to be an output pin
  pinMode(led, OUTPUT);
  on_board_rgb_led.begin();
  accel.begin(0x18);
  
  accel.setRange(LIS3DH_RANGE_16_G); 
  accel.setDataRate(LIS3DH_DATARATE_25_HZ);
}

void loop() {
  
  
  delay(50);                // wait for a half second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  uint32_t r = 0;
  uint32_t g = 0;
  uint32_t b = 0;

  if (is_playing_sound) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    r = 0;
    b = 255;
  }

  on_board_rgb_led.setPixelColor(0, on_board_rgb_led.Color(r,g,b));
  on_board_rgb_led.show();


 
}

void setup1(void) {
  i2s.setBCLK(PIN_I2S_BIT_CLOCK);
  i2s.setDATA(PIN_I2S_DATA);
  i2s.setBitsPerSample(16);
}

void loop1() {
  Serial.printf("Core #2 Playing audio");
  digitalWrite(PIN_EXTERNAL_POWER, HIGH);
  PlayI2S(kSamples, kNumSamples, kSampleRateHz);
  digitalWrite(PIN_EXTERNAL_POWER, LOW);
  delay(BEACON_PERIOD_MILLIS);
}

