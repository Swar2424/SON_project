#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
sawtooth(AUDIO_SAMPLE_RATE_EXACT),
sine1(AUDIO_SAMPLE_RATE_EXACT),
sine2(AUDIO_SAMPLE_RATE_EXACT),
sine3(AUDIO_SAMPLE_RATE_EXACT),
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
  sawtooth.setFrequency(freq);
  sine1.setFrequency(4);
  sine2.setFrequency(7);
  sine3.setFrequency(11);
}

void MyDsp::update(void) {
  audio_block_t* outBlock[AUDIO_OUTPUTS];
  for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
    outBlock[channel] = allocate();
    if (outBlock[channel]) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float currentSample = smooth.tick(echo.tick((sawtooth.tick()*2 - 1)*(sine1.tick()*0.5 +0.5)*(sine2.tick()*0.5 +0.5)*(sine3.tick()*0.5 +0.5)*0.5));
        currentSample = max(-1,min(1,currentSample));
        int16_t val = currentSample*MULT_16;
        outBlock[channel]->data[i] = val;
      }
      transmit(outBlock[channel], channel);
      release(outBlock[channel]);
    }
  }
}
