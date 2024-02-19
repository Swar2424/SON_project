#ifndef MYSINE2_H_INCLUDED
#define MYSINE2_H_INCLUDED

#include "SineTable.h"
#include "Phasor.h"

class MySine2{
public:
  MySine2(int SR);
  
  void setFrequency(float f);
  void setGain(float g);
  void setReleased(float b);
  float tick();
private:
  SineTable sineTable;
  Phasor phasor;
  float gain;
  int samplingRate;
  int envelopeIndex;
  float envelopeValue;
  bool isMute;
  bool isReleased;
  
};

#endif  // SINE_H_INCLUDED
