#include <Audio.h>
#include "FaustSynth.h"

FaustSynth faustSynth;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(faustSynth,0,out,0);
AudioConnection patchCord1(faustSynth,1,out,1);

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.4);
  faustSynth.setParamValue("gate", 1);
  faustSynth.setParamValue("curdel",5);
}


void loop() {
  faustSynth.setParamValue("freq",random(50,1000));
  delay(500);
}
