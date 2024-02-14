#include <Audio.h>
#include "MyDsp.h"
int myNotes[] = {0, 84, 0, 79, 0, 76, 0, 81, 0, 83, 0, 82, 81, 0, 79, 88, 91, 93, 0, 89, 91, 0, 88, 0, 84, 86, 83};
float myNotes_r[] = {2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 4/3, 4/3, 4/3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int counter_n = 0;
int len_n = sizeof(myNotes) / sizeof(myNotes[0]);
int time_n_s;
int time_n_e;
int pulse = 600;

MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.4);
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
      myDsp.setMute(0.05);
    } else {
      myDsp.setFreq(pow(2,(myNotes[counter_n]-69)/12.0)*440.0);
      myDsp.setMute(1);
    }
    
    time_n_s = millis();
  }
}
