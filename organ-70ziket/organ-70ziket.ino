#include <Audio.h>
#include "MyDsp.h"
int myNotes[] = {67, 0, 69, 0, 72, 74, 77, 0, 77, 0, 70, 67, 0};
float myNotes_r[] = {7/4.0, 1/4.0, 7/4.0, 1/4.0, 1/4.0, 1/4.0, 1/8.0, 1/8.0, 1/8.0, 1/8.0, 1/2.0, 9/4.0, 1/4.0};
int counter_n = 0;
int len_n = sizeof(myNotes) / sizeof(myNotes[0]);
int time_n_s;
int time_n_e;
int pulse = 2400;

MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);

void setup() {
  AudioMemory(2);
  audioShield.enable();
  myDsp.setFreq(pow(2,(myNotes[0]-69)/12.0)*440.0);
  audioShield.volume(0.2);
  myDsp.setGaine(0.2);
  time_n_s = millis();
}

void loop() {
  time_n_e= millis();
 
  if (time_n_e - time_n_s >= myNotes_r[counter_n]*pulse/4) {
    counter_n++;
    if (counter_n == len_n) {
      counter_n = 0;
    }
    
    if (myNotes[counter_n] == 0) {
      
    } else {
      myDsp.setFreq(pow(2,(myNotes[counter_n]-69)/12.0)*440.0);
      myDsp.setMute(1);
    }
    
    time_n_s = millis();
  }
}
