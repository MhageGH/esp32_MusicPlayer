#include "I2S.h"
#include <FS.h>
#include <SD.h>

const int offset = 0x2C;
char data[800];
char stereoData[1600];

void setup() {
  SD.begin();
  File file = SD.open("/sound_s.wav");  // 44100Hz, 16bit, linear PCM
  file.seek(22);
  int ch = file.read();
  file.seek(offset);
  I2S_Init();
  while (file.readBytes(data, sizeof(data))) {
    if (ch == 2) I2S_Write(data, sizeof(data));
    else if (ch == 1) {
      for (int i = 0; i < sizeof(data); ++i) 
      {
        stereoData[4 * (i / 2) + i % 2] = data[i];
        stereoData[4 * (i / 2) + i % 2 + 2] = data[i];
      }
      I2S_Write(stereoData, sizeof(stereoData));
    }
  }
  file.close();
  for (int i = 0; i < sizeof(data); ++i) data[i] = 0; // to prevent buzzing
  for (int i = 0; i < 5; ++i) I2S_Write(data, sizeof(data));
}

void loop() {
}
