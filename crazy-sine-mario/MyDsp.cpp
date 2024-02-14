#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
high_sine(AUDIO_SAMPLE_RATE_EXACT),
sine2(AUDIO_SAMPLE_RATE_EXACT),
main_sine(AUDIO_SAMPLE_RATE_EXACT),
sine1(AUDIO_SAMPLE_RATE_EXACT),
echo(AUDIO_SAMPLE_RATE_EXACT,10000)
{
  echo.setDel(10000);
  echo.setFeedback(0.5);
}

MyDsp::~MyDsp(){}

// set sine wave frequency
void MyDsp::setFreq(float freq){
  high_sine.setFrequency(freq*2);
  main_sine.setFrequency(freq);
  sine1.setFrequency(6);
  sine2.setFrequency(8);
}

void MyDsp::setGaine(float gaine) {
  myGain = gaine;
}

void MyDsp::setMute(float mute) {
  myMute = mute;
}

void MyDsp::update(void) {
  audio_block_t* outBlock[AUDIO_OUTPUTS];
  for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
    outBlock[channel] = allocate();
    if (outBlock[channel]) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float currentSample = echo.tick(high_sine.tick()*0.2 + main_sine.tick()*0.8)*myMute*myGain*sine1.tick()*sine2.tick();
        currentSample = max(-1,min(1,currentSample));
        int16_t val = currentSample*MULT_16;
        outBlock[channel]->data[i] = val;
      }
      transmit(outBlock[channel], channel);
      release(outBlock[channel]);
    }
  }
}
