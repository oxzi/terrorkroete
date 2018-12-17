#include <Arduino.h>

#include <HTTPClient.h>
#include <SPIFFS.h>
#include <SD.h>

#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"
#include "AudioFileSourcePROGMEM.h"

#include "bullenwagen.h"

void flickering(void*);

AudioFileSourcePROGMEM *in;
AudioGeneratorMP3 *mp3;
AudioOutputI2SNoDAC *out;

QueueHandle_t queue;

int8_t leds[5] = { 16, 17, 4, 2, 15 };
int8_t eyes[2] = { 5, 18 };
int8_t button = 21;

void setup() {
  for (int8_t i = 0; i < sizeof(leds); i++) {
    pinMode(leds[i], OUTPUT);
  }

  for (int8_t i = 0; i < sizeof(eyes); i++) {
    pinMode(eyes[i], OUTPUT);
    digitalWrite(eyes[i], HIGH);
  }

  pinMode(button, INPUT);

  queue = xQueueCreate(1, sizeof(bool));

  xTaskCreate(flickering, "flickering", 10000, NULL, 0, NULL);

  in = new AudioFileSourcePROGMEM(bullenwagen_mp3, bullenwagen_mp3_len);
  mp3 = new AudioGeneratorMP3();
  out = new AudioOutputI2SNoDAC();

  mp3->begin(in, out);
}

void flickering(void *param) {
  for (int8_t i = 0; uxQueueMessagesWaiting(queue) == 0; i = random(0, sizeof(leds))) {
    digitalWrite(leds[i], random(2));
    delay(random(15, 50));
  }

  for (int8_t i = 0; i < sizeof(leds); i++) {
    digitalWrite(leds[i], LOW);
  }

  for (;;);
}

void loop() {
  bool msg = true;

  if (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
    }
  } else {
    xQueueSend(queue, (void *)&msg, (TickType_t) 0);
  }
}
