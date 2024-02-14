#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "Echo.h"
#include "Sine.h"
#include "Biquad.h"

class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    
    virtual void update(void);
    void setFreq(float freq);
    void setGaine(float gaine);
    
  private:
    Phasor sine;
    Biquad biquad;
    float myGain = 0.5;
};

#endif
