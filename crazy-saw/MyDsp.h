#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "Phasor.h"
#include "Echo.h"
#include "Sine.h"
#include "Smooth.h"

class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    
    virtual void update(void);
    void setFreq(float freq);
    
  private:
    Sine sine1;
    Sine sine2;
    Sine sine3;
    Phasor sawtooth;
    Echo echo;
    Smooth smooth;
};

#endif
