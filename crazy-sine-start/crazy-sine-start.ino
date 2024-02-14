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
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(myDsp,0,out,0);
AudioConnection patchCord1(myDsp,0,out,1);
AudioControlSGTL5000 sgtl5000_1;

void setup() {
  AudioMemory(8);
  audioShield.enable();
  audioShield.volume(0.2);
  myDsp.setGaine(0.2);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(40);
}

void loop() {
  note = notes[random(counter, counter + marge)];
  myDsp.setFreq(pow(2,(note-69)/12.0)*440.0);
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
