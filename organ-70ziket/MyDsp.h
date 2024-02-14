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
    void setFreq(float freq);
    void setGaine(float gaine);
    void setMute(float mute);
    
  private:
    MySine sine;
    Sine oscil;
    Echo echo;
    float myGain = 0.5;
    float myMute = 1;
    float myMute_r = 1;
};

#endif
