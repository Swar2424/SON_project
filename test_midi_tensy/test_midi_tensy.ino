#include <Audio.h>
#include "MyDsp.h"


MyDsp myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioMixer4 mixer1;
AudioControlSGTL5000 audioShield;
AudioEffectFreeverb freeverb1;
AudioConnection patchCord0(in, 0, freeverb1, 0);
AudioConnection patchCord1(freeverb1, 0, mixer1, 0);
AudioConnection patchCord2(myDsp, 0, mixer1, 1);
AudioConnection patchCord3(mixer1,0,out,0);
AudioConnection patchCord4(mixer1,0,out,1);
AudioControlSGTL5000 sgtl5000_1;

int ledPin = 13;
int canaux[5] = {0, 0, 0, 0, 0};
int len = sizeof(canaux) / sizeof(canaux[0]);

void OnNoteOn(byte channel, byte note, byte velocity) {
  bool placed = false;
  for (int i = 0; i<len && placed == false; i++){
    if (canaux[i] == 0) {
      canaux[i] = note;
      myDsp.setFreq(i, pow(2,(note-69)/12.0)*440.0);
      myDsp.setMute(i, 1);
      placed = true;
    }
  }
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  for (int i = 0; i<len ; i++){
    if (note == canaux[i]) {
      myDsp.setMute(i, 0);
      canaux[i] = 0;
    }
  }
}

void setup() {
  AudioMemory(8);
  freeverb1.damping(0.5);
  freeverb1.roomsize(0.7);
  audioShield.enable();
  audioShield.volume(0.3);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(45);
  for (int i=0 ; i<len ; i++) {
     myDsp.setMute(i, 0);
  }
  myDsp.setGaine(0.1);
  pinMode(ledPin, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
}

void loop() {
  usbMIDI.read();
}
