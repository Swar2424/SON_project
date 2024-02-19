#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "MySine.h"
#include "MySine2.h"
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
    MySine* organL[5];
    MySine2* pianoL[5];
    Smooth* smoothL[5];
    Echo echo;
    int N = 5;
    float myGain = 0.5;
    float myMute[5] = {0, 0, 0, 0, 0};
    int CurrentInstru = 0;
    int NewInstru = 0;
    int modif = false;
};

#endif
