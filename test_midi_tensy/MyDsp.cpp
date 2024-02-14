#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767

MyDsp::MyDsp() : 
AudioStream(AUDIO_OUTPUTS, new audio_block_t*[AUDIO_OUTPUTS]),
sine0(AUDIO_SAMPLE_RATE_EXACT),
sine1(AUDIO_SAMPLE_RATE_EXACT),
sine2(AUDIO_SAMPLE_RATE_EXACT),
sine3(AUDIO_SAMPLE_RATE_EXACT),
oscil(AUDIO_SAMPLE_RATE_EXACT),
echo(AUDIO_SAMPLE_RATE_EXACT,10000)
{
  echo.setDel(10000);
  echo.setFeedback(0.6);
}

MyDsp::~MyDsp(){}

// set sine wave frequency
void MyDsp::setFreq(int nb, float freq){
  switch(nb) {
    case 0:
      sine0.setFrequency(freq/4);
      break;
    case 1:
      sine1.setFrequency(freq/4);
      break;
    case 2:
      sine2.setFrequency(freq/4);
      break;
    case 3:
      sine3.setFrequency(freq/4);
      break;
  }
  oscil.setFrequency(14);
}

void MyDsp::setGaine(float gaine) {
  myGain = gaine;
}

void MyDsp::setMute(int nb, float mute) {
  myMute[nb] = mute;
}

void MyDsp::update(void) {
  audio_block_t* outBlock[AUDIO_OUTPUTS];
  for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
    outBlock[channel] = allocate();
    if (outBlock[channel]) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float note_signal = sine0.tick()*myMute[0] + sine1.tick()*myMute[1] + sine2.tick()*myMute[2] + sine3.tick()*myMute[3];
        float currentSample = echo.tick(note_signal * (oscil.tick()*0.1+0.9)) * myGain;
        currentSample = max(-1,min(1,currentSample));
        int16_t val = currentSample*MULT_16;
        outBlock[channel]->data[i] = val;
      }
      transmit(outBlock[channel], channel);
      release(outBlock[channel]);
    }
  }
}
