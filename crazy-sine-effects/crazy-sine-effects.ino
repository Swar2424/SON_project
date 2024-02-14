#include <Audio.h>
#include "MyDsp.h"
double myNotes[] = {72, 76, 79, 83, 84, 88, 91, 95};
double myNotes2[] = {79, 83, 86, 89, 91, 95, 98, 101};
double *notes = myNotes;
int pulse = 1500;
bool up_down = true;
int counter = 0;
int marge = 5;
double note;
int len = sizeof(myNotes) / sizeof(myNotes[0]);


MyDsp myDsp;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);

void setup() {
  AudioMemory(2);
  audioShield.enable();
  audioShield.volume(0.4);
  myDsp.setGaine(0.4);
}

void loop() {
  note = notes[random(counter, counter + marge)];
  //Serial.println(pow(2,(note-69)/12.0)*440.0);
  myDsp.setFreq(440.0);
  delay(random(2,5)*pulse/4);

  if (up_down) {
     counter++;
     if (counter == len-marge) {
      up_down = false;
      *notes = *myNotes2;
     }
  } else {
    counter--;
    if (counter == 0) {
      up_down = true;
      *notes = *myNotes;
     }
  }
}
