#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "MySine.h"
#include "MySine2.h"
#include "Sine.h"
#include "Phasor.h"
#include "Echo.h"
#include "Smooth.h"

class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    
    virtual void update(void);
    void setFreq(int nb, float freq);
    void setGaine(float gaine);
    void setMute(int nb, float mute);
    void switchInstru(int instru);
    
  private:
    MySine* organ0 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
    MySine* organ1 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
    MySine* organ2 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
    MySine* organ3 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
    MySine* organ4 = new MySine(AUDIO_SAMPLE_RATE_EXACT);
    MySine2* sine0 = NULL;
    MySine2* sine1 = NULL;
    MySine2* sine2 = NULL;
    MySine2* sine3 = NULL;
    MySine2* sine4 = NULL;
    Smooth smooth0;
    Smooth smooth1;
    Smooth smooth2;
    Smooth smooth3;
    Smooth smooth4;
    Sine oscil;
    Echo echo;
    float myGain = 0.5;
    float myMute[5] = {0, 0, 0, 0, 0};
    int CurrentInstru = 0;
    int NewInstru = 0;
    int modif = false;
};

#endif
