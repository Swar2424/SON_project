#include <Audio.h>
#include "MyDsp.h"


MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);

int ledPin = 13;
int canaux[3] = {0, 0, 0};

void OnNoteOn(byte channel, byte note, byte velocity) {
  bool placed = false;
  for (int i = 0; i<3 && placed == false; i++){
    if (canaux[i] == 0) {
      canaux[i] = note;
      myDsp.setFreq(i, pow(2,(note-69)/12.0)*440.0);
      myDsp.setMute(i, 1);
      placed = true;
    }
  }
  Serial.print(canaux[0]);  
  Serial.print(canaux[1]);  
  Serial.println(canaux[2]); 
}

void OnNoteOff(byte channel, byte note, byte velocity) {
  for (int i = 0; i<3 ; i++){
    if (note == canaux[i]) {
      myDsp.setMute(i, 0);
      canaux[i] = 0;
    }
  }
  Serial.print(canaux[0]);  
  Serial.print(canaux[1]);
  Serial.println(canaux[2]);
}

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.2);
  myDsp.setGaine(0, 0.2);
  myDsp.setGaine(1, 0.2);
  myDsp.setGaine(2, 0.2);
  myDsp.setMute(0, 0);
  myDsp.setMute(1, 0);
  myDsp.setMute(2, 0);
  pinMode(ledPin, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
}

void loop() {
  usbMIDI.read();
}
