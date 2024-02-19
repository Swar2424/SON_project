#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
echo(AUDIO_SAMPLE_RATE_EXACT,10000)
{
  echo.setDel(8000);
  echo.setFeedback(0.4);
  for (int i=0 ; i<N ; i++) {
    organL[i] = new MySine(AUDIO_SAMPLE_RATE_EXACT);
    smoothL[i] = new Smooth;
    smoothL[i]->setPole(0.999);
  }
}

MyDsp::~MyDsp(){}

// set sine wave frequency
void MyDsp::setFreq(int nb, float freq){
  if (CurrentInstru == 0) {
     organL[nb]->setFrequency(freq);
  } else {
     pianoL[nb]->setFrequency(freq);
  }  
}

void MyDsp::switchInstru(int instru) {
  modif = true;
  NewInstru = instru;
}


void MyDsp::setGaine(float gaine) {
  myGain = gaine;
}


void MyDsp::setMute(int nb, float mute) {
  myMute[nb] = mute;
  if (CurrentInstru == 1){
    pianoL[nb]->setReleased(mute);
  }
}


void MyDsp::update(void) {
  
  if (modif) {
    if (NewInstru != CurrentInstru) {
      if (NewInstru == 0) {
          for (int i=0 ; i<N ; i++) {
            delete pianoL[i];
            organL[i] = new MySine(AUDIO_SAMPLE_RATE_EXACT);
          }        
        CurrentInstru = 0;
      } else {
        for (int i=0 ; i<N ; i++) {
          delete organL[i];
          pianoL[i] = new MySine2(AUDIO_SAMPLE_RATE_EXACT);
          pianoL[i]->setReleased(0.0);
        }
        CurrentInstru = 1;
      }
    }
    for (int i = 0; i<5 ; i++){
      myMute[i] = 0.0;
      smoothL[i]->setDel(0.0);
    }
    modif = false;
  }


  
  audio_block_t* outBlock[AUDIO_OUTPUTS];
  for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
    outBlock[channel] = allocate();
    if (outBlock[channel]) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        
        float note_signal = 0.0;
        
        if(CurrentInstru == 0) {
          for (int i=0 ; i<N ; i++) {
            note_signal += organL[i]->tick()*smoothL[i]->tick(myMute[i])*0.25;
          }
          note_signal = echo.tick(note_signal);
        } else {
          for (int i=0 ; i<N ; i++) {
            note_signal += pianoL[i]->tick()*smoothL[i]->tick(myMute[i])*0.25;
          }
        }
        
        float currentSample = note_signal * myGain;
        currentSample = max(-1,min(1,currentSample));
        int16_t val = currentSample*MULT_16;
        outBlock[channel]->data[i] = val;
      }
      transmit(outBlock[channel], channel);
      release(outBlock[channel]);
    }
  }
}
