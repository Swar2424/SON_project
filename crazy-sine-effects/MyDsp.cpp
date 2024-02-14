#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
sine(AUDIO_SAMPLE_RATE_EXACT),
biquad(AUDIO_SAMPLE_RATE_EXACT)
{}

MyDsp::~MyDsp(){}

// set sine wave frequency
void MyDsp::setFreq(float freq){
  sine.setFrequency(freq);
}


void MyDsp::setGaine(float gaine) {
  myGain = gaine;
}

void MyDsp::update(void) {
  audio_block_t* outBlock[AUDIO_OUTPUTS];
  outBlock[0] = allocate();
  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    float currentSample = biquad.tick(sine.tick())*myGain;
    currentSample = max(-1,min(1,currentSample));
    int16_t val = currentSample*MULT_16;
    outBlock[0]->data[i] = val;
  }
  transmit(outBlock[0], 0);
  release(outBlock[0]);
}
