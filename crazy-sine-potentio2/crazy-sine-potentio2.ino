#include <Audio.h>
#include "MyDsp.h"
int notes;
int myNotes[] = {72, 74, 76, 79, 83, 84, 86, 88, 89, 91, 95, 98, 101};
//int myNotes[] = {84, 79, 76, 81, 83, 82, 81, 79, 88, 91, 93, 89, 91, 88, 84, 86, 83};
bool pressoir = false;
int counter = 0;
int len = sizeof(myNotes) / sizeof(myNotes[0]);


MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.5);
  myDsp.setGaine(1);
  pinMode(0, INPUT);
}

void loop() {
  int sensorValue = analogRead(A0);
  int note = map(sensorValue, 0, 1023, 0, len-1);
  int sensorValue2 = analogRead(A2);
  float volum = map(sensorValue2, 0, 1023, 0, 100)/100.0;
  int mute = digitalRead(0);
  
  if (mute == 0 && pressoir == true) {
     pressoir = false;
     delay(50);
  } else if (mute == 1 && pressoir == false) {
    pressoir = true;
    delay(50);
    counter = (counter + 1) % len;
   }
  myDsp.setFreq(pow(2,(myNotes[note]-69)/12.0)*440.0);
  myDsp.setGaine(volum);
}
