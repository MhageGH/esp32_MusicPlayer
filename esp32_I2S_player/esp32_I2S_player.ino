#include "I2S.h"
#include <FS.h>
#include <SD.h>

const int offset = 0x2C;
char data[800];

void setup() {
  SD.begin();
  File file = SD.open("/sound.wav");  // 44100Hz, 16bit, stereo, linear PCM
  file.seek(offset);
  I2S_Init();
  while (file.readBytes(data, sizeof(data))) {
    I2S_Write(data, sizeof(data));
  }
  file.close();
}

void loop() {
}
