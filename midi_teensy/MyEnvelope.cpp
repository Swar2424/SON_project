#include <cmath>

#include "MySine2.h"

#define SINE_TABLE_SIZE 16384

MyEnvelope::MyEnvelope(int SR) : 
samplingRate(SR),
envelopeIndex(0),
envelopeValue(1.0),
isMute(false),
isReleased(false) {}


void MyEnvelope::setReleased(float b){
  if (b==0.0 && isMute==false) {
    isMute=true;
    
  } else if (isMute==true) {
    isReleased = false;
    envelopeValue = 1.0;
    envelopeIndex = 0;
    isMute=false;
  }
  
  
}
    
float MyEnvelope::tick(){
  float attackTime = 0.003;
  float decayTime = 0.01;
  float sustainLevel = 0.07;
  float releaseTime = 3;
  
  if (!isReleased) {
      if (envelopeIndex < attackTime * samplingRate) {
          envelopeValue = (float)envelopeIndex / (attackTime * samplingRate);
      }
      else if ((float)envelopeIndex < ((float)attackTime + (float)decayTime) * (float)samplingRate) {
          envelopeValue = 1.0 - (1.0 - sustainLevel) * ((float)(envelopeIndex - attackTime * samplingRate) / (decayTime * samplingRate));
      }
      else {
          envelopeValue = sustainLevel * (1.0 - (float)(envelopeIndex - (attackTime + decayTime) * samplingRate) / (releaseTime * samplingRate));
          if (envelopeValue <= 0.001) {
              envelopeValue = 0.0;
              isReleased = true;
          }
      }
      envelopeIndex++;
  }

  return(envelopeValue);
  
}
