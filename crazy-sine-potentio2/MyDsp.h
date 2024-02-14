#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "Sine.h"
#include "Echo.h"
#include "Smooth.h"
#include "MySine.h"

class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    
    virtual void update(void);
    void setFreq(float freq);
    void setGaine(float gaine);
    
  private:
    Sine oscil;
    MySine sine;
    Smooth smooth;
    Echo echo;
    
    float myGain = 0.5;
};

#endif
