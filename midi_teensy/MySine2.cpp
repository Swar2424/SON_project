#include <cmath>

#include "MySine2.h"

#define SINE_TABLE_SIZE 16384

MySine2::MySine2(int SR) : 
sineTable(SINE_TABLE_SIZE),
phasor(SR),
gain(1.0),
samplingRate(SR),
envelopeIndex(0),
envelopeValue(1.0),
isMute(false),
isReleased(false) {}

void MySine2::setFrequency(float f){
  phasor.setFrequency(f);
}
    
void MySine2::setGain(float g){
  gain = g;
}

void MySine2::setReleased(float b){
  if (b==0.0 && isMute==false) {
    isMute=true;
    
  } else if (isMute==true) {
    isReleased = false;
    envelopeValue = 1.0;
    envelopeIndex = 0;
    isMute=false;
  }
  
  
}
    
float MySine2::tick(){
  float attackTime = 0.005;
  float decayTime = 0.03;
  float sustainLevel = 0.4;
  float releaseTime = 0.5;
  
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
  
  int index = phasor.tick()*SINE_TABLE_SIZE;
  double value1 = sineTable.tick(index)*(1);
  double value2 = sineTable.tick(index*2)*(0.3*1);
  double value3 = sineTable.tick(index*3)*(0.3*0.5);
  double value4 = sineTable.tick(index*4)*(0.3*0.3);
  double value5 = sineTable.tick(index*5)*(0.3*0.2);
  double value6 = sineTable.tick(index*6)*(0.3*0.1);

  return(value1 + value2 + value3 + value4 + value5 + value6) * envelopeValue;
  

  
//  int index0 = (int) (index1/2)%SINE_TABLE_SIZE;
//  int index2 = (int) (index1*2)%SINE_TABLE_SIZE;
//  int index4 = (int) (index1*4)%SINE_TABLE_SIZE;
//  int index_quinte = (int) (index1*(2^(7/12)))%SINE_TABLE_SIZE;
//  int index_quinte2 = (int) (index_quinte*2)%SINE_TABLE_SIZE;
//  int index_quinte4 = (int) (index_quinte*4)%SINE_TABLE_SIZE;
//  int index_tierce = (int) (index1*(2^(4/12)))%SINE_TABLE_SIZE;
//  int index_tierce2 = (int) (index_tierce*2)%SINE_TABLE_SIZE;
//  int index_tierce4 = (int) (index_tierce*4)%SINE_TABLE_SIZE;
//  double value0 = sineTable.tick(index0)>=0.0 ? 1.0:-1.0;
//  double value1 = sineTable.tick(index1)>=0.0 ? 1.0:-1.0;
//  double value2 = sineTable.tick(index2)>=0.0 ? 1.0:-1.0;
//  double value3 = sineTable.tick(index4)>=0.0 ? 1.0:-1.0;
//  double value4 = sineTable.tick(index_quinte)>=0.0 ? 1.0:-1.0;
//  double value5 = sineTable.tick(index_quinte2)>=0.0 ? 1.0:-1.0;
//  double value6 = sineTable.tick(index_quinte4)>=0.0 ? 1.0:-1.0;
//  double value7 = sineTable.tick(index_tierce)>=0.0 ? 1.0:-1.0;
//  double value8 = sineTable.tick(index_tierce2)>=0.0 ? 1.0:-1.0;
//  double value9 = sineTable.tick(index_tierce4)>=0.0 ? 1.0:-1.0;
//
//  return(value0 + value1 + value2 + value3 + value4 + value5 + value6 + value7 + value8 + value9);
  
  
}
