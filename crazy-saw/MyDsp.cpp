#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
echo(AUDIO_SAMPLE_RATE_EXACT,10000),
smooth()
{
  echo.setDel(10000);
  echo.setFeedback(0.5);
  smooth.setPole(0.999);
}

MyDsp::~MyDsp(){}

// set sine wave frequency
void MyDsp::setFreq(float freq){
  if (current == 0) {
    sawtooth->setFrequency(freq);
  } else {
    sine->setFrequency(freq);
  }
}


void MyDsp::replaceSine() {
  modif_needed = true;
}

void MyDsp::update(void) {
  
  if (modif_needed) {
    if (current == 0) {
      delete sawtooth;
      sine = new Sine(AUDIO_SAMPLE_RATE_EXACT);
      current = 1;
    } else {
      delete sine;
      sawtooth = new Phasor(AUDIO_SAMPLE_RATE_EXACT);
      current = 0;
    }  
    modif_needed = false;
  }
  
  audio_block_t* outBlock[AUDIO_OUTPUTS];
  for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
    outBlock[channel] = allocate();
    if (outBlock[channel]) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        
        float signal_tick;
        if (current == 0) {
          signal_tick = sawtooth->tick();
        } else {
          signal_tick = sine->tick();
        }

        float currentSample = echo.tick(signal_tick);
        currentSample = max(-1,min(1,currentSample));
        int16_t val = currentSample*MULT_16;
        outBlock[channel]->data[i] = val;
      }
      transmit(outBlock[channel], channel);
      release(outBlock[channel]);
    }
  }
}
