#include "MyDsp.h"

#define AUDIO_OUTPUTS 2

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
sine(AUDIO_SAMPLE_RATE_EXACT),
echoL(AUDIO_SAMPLE_RATE_EXACT,5000),
echoR(AUDIO_SAMPLE_RATE_EXACT,5000)
{
  echoR.setDel(5000);
  echoR.setFeedback(0.5);
  echoL.setDel(5000);
  echoL.setFeedback(0.5);
}

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
  outBlock[1] = allocate();
  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    float sineSample = sine.tick();
    float currentSampleL = echoL.tick(sineSample)*myGain;
    float currentSampleR = echoR.tick(sineSample)*myGain;
    currentSampleL = max(-1,min(1,currentSampleL));
    currentSampleR = max(-1,min(1,currentSampleR));
    int16_t valL = currentSampleL*MULT_16;
    int16_t valR = currentSampleR*MULT_16;
    outBlock[0]->data[i] = valL;
    outBlock[1]->data[i] = valR;
  }
  transmit(outBlock[0], 0);
  release(outBlock[0]);
  transmit(outBlock[1], 1);
  release(outBlock[1]);
}
