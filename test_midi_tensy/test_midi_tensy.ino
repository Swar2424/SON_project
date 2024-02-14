#include <Audio.h>
#include "MyDsp.h"


MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);

int ledPin = 13;
int canaux[4] = {0, 0, 0, 0};
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
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.2);

  for (int i=0 ; i<len ; i++) {
     myDsp.setMute(i, 0);
  }
  myDsp.setGaine(0.2);
  pinMode(ledPin, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
}

void loop() {
  usbMIDI.read();
}
