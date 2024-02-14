#include <Audio.h>
#include "MyDsp.h"
int notes;
int pulse = 500;
int counter = 0;


MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,1,out,1);

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.3);
  myDsp.setGaine(0.4);
  pinMode(0, INPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  int note = map(sensorValue, 0, 1023, 60, 90);
  int sensorValue2 = analogRead(A2);
  float volum = map(sensorValue2, 0, 1023, 0, 100)/100.0;
  int mute = digitalRead(0);
  if (mute == 0) {volum = 0;}
  myDsp.setFreq(pow(2,(note-69)/12.0)*440.0);
  myDsp.setGaine(volum);
}
