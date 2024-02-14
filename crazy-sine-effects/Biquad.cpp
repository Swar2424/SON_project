#include <cmath>

#include "Biquad.h"

#define SINE_TABLE_SIZE 16384

Biquad::Biquad(int SR) : 
sr(SR),
sineTable(SINE_TABLE_SIZE),
phasor(SR),
gain(1.0),
del_b0d(0.0),
del_b1d(0.0),
del_b2d(0.0),
del_a1d(0.0),
del_a2d(0.0),
samplingRate(SR){}


void Biquad::setFrequency(float f){
  phasor.setFrequency(f);
}
    
void Biquad::setGain(float g){
  gain = g;
}


float Biquad::tf2(float b0d, float b1d, float b2d, float a1d, float a2d){
    float rep = b0d*del_b0d + b1d*del_b1d + b2d*del_b2d + a1d*del_a1d + a2d*del_a2d;
    del_b2d = del_b1d;
    del_b1d = del_b0d;
    del_a2d = del_a1d;
    del_a1d = rep;
    return rep;
}


float Biquad::tf2s(float b2, float b1, float b0, float a1, float a0, float w1){
  float c   = 1.0/tan(w1*0.5/sr);
  float csq = c*c;
  float d   = a0 + a1 * c + csq;
  float b0d = (b0 + b1 * c + b2 * csq)/d;
  float b1d = 2.0 * (b0 - b2 * csq)/d;
  float b2d = (b0 - b1 * c + b2 * csq)/d;
  float a1d = 2.0 * (a0 - csq)/d;
  float a2d = (a0 - a1*c + csq)/d;
  return tf2(b0d,b1d,b2d,a1d,a2d);
}


float Biquad::resonlp(float fc, float Q, float g) {
     float wc = 2*M_PI*fc;
     float a1 = 1.0/Q;
     float a0 = 1.0;
     float b2 = 0.0;
     float b1 = 0.0;
     float b0 = g;
     return tf2s(b2,b1,b0,a1,a0,wc);
};


float Biquad::resonbp(float fc, float Q, float g) {
     float wc = 2*M_PI*fc;
     float a1 = 1.0/Q;
     float a0 = 1;
     float b2 = 0.0;
     float b1 = g;
     float b0 = 0.0;
     return tf2s(b2,b1,b0,a1,a0,wc);
};


float Biquad::resonhp(float fc, float Q, float g, float x) {
  return g*x-resonlp(fc,Q,g);
}
    
float Biquad::tick(float sinus){
    del_b0d = sinus;
    float rep = resonlp(500.0, 16.0, 1.0);
    return sinus;
}
