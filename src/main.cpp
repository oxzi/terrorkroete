#include <Arduino.h>

#include <HTTPClient.h>
#include <SPIFFS.h>
#include <SD.h>

#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"
#include "AudioFileSourcePROGMEM.h"

#include "bullenwagen.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorMP3 *mp3;
AudioOutputI2SNoDAC *out;

int8_t leds[5] = { 16, 17, 4, 2, 15 };
int8_t eyes[2] = { 5, 18 };
int8_t button = 21;

void flickering(void*);

void setup()
{
  for (int8_t i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }

  for (int8_t i = 0; i < sizeof(eyes); i++) {
    pinMode(eyes[i], OUTPUT);
    digitalWrite(eyes[i], HIGH);
  }

  pinMode(button, INPUT);

  xTaskCreatePinnedToCore(
    flickering, "flickering", 10000, NULL, 0, NULL, 0);

  in = new AudioFileSourcePROGMEM(bullenwagen_mp3, bullenwagen_mp3_len);
  mp3 = new AudioGeneratorMP3();
  out = new AudioOutputI2SNoDAC();

  mp3->begin(in, out);
}

void flickering(void *pvParams) {
  for (int8_t i = 0;; i = random(0, sizeof(leds))) {
    digitalWrite(leds[i], random(2));
    delay(random(10, 100));
  }
}

void loop()
{
  if (mp3->isRunning()) {
    mp3->loop();
  }
}
