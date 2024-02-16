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
    void replaceSine();
    
  private:
    Sine* sine = NULL;
    Phasor* sawtooth = new Phasor(AUDIO_SAMPLE_RATE_EXACT);
    Echo echo;
    Smooth smooth;
    int current = 0;
    bool modif_needed = false;
};

#endif
