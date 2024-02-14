#ifndef BIQUAD_H_INCLUDED
#define BIQUAD_H_INCLUDED

#include "SineTable.h"
#include "Phasor.h"

class Biquad{
public:
  Biquad(int SR);
  
  void setFrequency(float f);
  void setGain(float g);
  float tick(float sinus);
  float tf2(float b0d, float b1d, float b2d, float a1d, float a2d);
  float tf2s(float b2, float b1, float b0, float a1, float a0, float w1);
  float resonlp(float fc, float Q, float g);
  float resonbp(float fc, float Q, float g);
  float resonhp(float fc, float Q, float g, float x);
private:
    SineTable sineTable;
    Phasor phasor;
    float gain;
    int samplingRate;
    float  del_b0d;
    float  del_b1d;
    float  del_b2d;
    float  del_a1d;
    float  del_a2d;
    float sr;
};

#endif  // SINE_H_INCLUDED
