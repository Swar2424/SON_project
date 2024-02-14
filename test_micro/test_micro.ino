#include <Audio.h>

AudioInputI2S            in;
AudioOutputI2S           out;
AudioConnection          patchCord1(in, 0, out, 0);
AudioConnection          patchCord2(in, 0, out, 1);
AudioControlSGTL5000     sgtl5000_1;



void setup() {
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(36);
  delay(1000);
}

void loop() {
  // do nothing
}
