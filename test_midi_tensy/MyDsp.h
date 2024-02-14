#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "MySine.h"
#include "Sine.h"
#include "Phasor.h"
#include "Echo.h"

class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    
    virtual void update(void);
    void setFreq(int nb, float freq);
    void setGaine(float gaine);
    void setMute(int nb, float mute);
    
  private:
    MySine sine0;
    MySine sine1;
    MySine sine2;
    MySine sine3;
    Sine oscil;
    Echo echo;
    float myGain = 0.5;
    float myMute[4] = {1, 1, 1, 1};
    float myMute_r[4] = {1, 1, 1, 1};
};

#endif
