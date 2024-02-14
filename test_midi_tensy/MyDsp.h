#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "MySine.h"
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
    
  private:
    MySine sine0;
    MySine sine1;
    MySine sine2;
    MySine sine3;
    MySine sine4;
    Smooth smooth0;
    Smooth smooth1;
    Smooth smooth2;
    Smooth smooth3;
    Smooth smooth4;
    Sine oscil;
    Echo echo;
    float myGain = 0.5;
    float myMute[5] = {0, 0, 0, 0, 0};
};

#endif
