#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
smooth0(),
smooth1(),
smooth2(),
smooth3(),
smooth4(),
echo(AUDIO_SAMPLE_RATE_EXACT,10000)
{
  echo.setDel(8000);
  echo.setFeedback(0.4);
  smooth0.setPole(0.999);
  smooth1.setPole(0.999);
  smooth2.setPole(0.999);
  smooth3.setPole(0.999);
  smooth4.setPole(0.999);
}

MyDsp::~MyDsp(){}

// set sine wave frequency
void MyDsp::setFreq(int nb, float freq){
  if (CurrentInstru == 0) {
      switch(nb) {
        case 0:
          organ0->setFrequency(freq);
          break;
        case 1:
          organ1->setFrequency(freq);
          break;
        case 2:
          organ2->setFrequency(freq);
          break;
        case 3:
          organ3->setFrequency(freq);
          break;
        case 4:
          organ4->setFrequency(freq);
          break;
      }
  } else {
      switch(nb) {
        case 0:
          sine0->setFrequency(freq);
          break;
        case 1:
          sine1->setFrequency(freq);
          break;
        case 2:
          sine2->setFrequency(freq);
          break;
        case 3:
          sine3->setFrequency(freq);
          break;
        case 4:
          sine4->setFrequency(freq);
          break;
      }
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
    switch(nb) {
        case 0:
          sine0->setReleased(mute);
          break;
        case 1:
          sine1->setReleased(mute);
          break;
        case 2:
          sine2->setReleased(mute);
          break;
        case 3:
          sine3->setReleased(mute);
          break;
        case 4:
          sine4->setReleased(mute);
          break;
      }
  }
}


void MyDsp::update(void) {
  
  if (modif) {
    if (NewInstru != CurrentInstru) {
      if (NewInstru == 0) {
        delete sine0;
        delete sine1;
        delete sine2;
        delete sine3;
        delete sine4;
        organ0 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
        organ1 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
        organ2 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
        organ3 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
        organ4 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
        CurrentInstru = 0;
      } else {
        delete organ0;
        delete organ1;
        delete organ2;
        delete organ3;
        delete organ4;
        sine0 = new MySine2(AUDIO_SAMPLE_RATE_EXACT);
        sine1 = new MySine2(AUDIO_SAMPLE_RATE_EXACT);
        sine2 = new MySine2(AUDIO_SAMPLE_RATE_EXACT);
        sine3 = new MySine2(AUDIO_SAMPLE_RATE_EXACT);
        sine4 = new MySine2(AUDIO_SAMPLE_RATE_EXACT);
        CurrentInstru = 1;
      }
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
          note_signal = organ0->tick()*smooth0.tick(myMute[0])*0.25 + organ1->tick()*smooth1.tick(myMute[1])*0.25 + organ2->tick()*smooth2.tick(myMute[2])*0.25 + organ3->tick()*smooth3.tick(myMute[3])*0.25 + organ4->tick()*smooth4.tick(myMute[4])*0.25;
          note_signal = echo.tick(note_signal);
        } else {
          note_signal = sine0->tick()*smooth0.tick(myMute[0])*0.25 + sine1->tick()*smooth1.tick(myMute[1])*0.25 + sine2->tick()*smooth2.tick(myMute[2])*0.25 + sine3->tick()*smooth3.tick(myMute[3])*0.25 + sine4->tick()*smooth4.tick(myMute[4])*0.25;
          
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
