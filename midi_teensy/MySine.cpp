#include <cmath>

#include "MySine.h"

#define SINE_TABLE_SIZE 16384

MySine::MySine(int SR) : 
sineTable(SINE_TABLE_SIZE),
phasor(SR),
gain(1.0),
samplingRate(SR){}

void MySine::setFrequency(float f){
  phasor.setFrequency(f);
}
    
void MySine::setGain(float g){
  gain = g;
}
    
float MySine::tick(){
  int index1 = phasor.tick()*SINE_TABLE_SIZE;

  double value0 = sineTable.tick(index1*0.5);
  double value1 = sineTable.tick(index1);
  double value2 = sineTable.tick(index1*1.5);
  double value3 = sineTable.tick(index1*2);
  double value4 = sineTable.tick(index1*3);
  double value5 = sineTable.tick(index1*4);
  double value6 = sineTable.tick(index1*5);
  double value7 = sineTable.tick(index1*6);
  double value8 = sineTable.tick(index1*7)*0.05;
  double value9 = sineTable.tick(index1*8);
  double value10 = sineTable.tick(index1*9)*0.05;
  double value11 = sineTable.tick(index1*10);
  double value12 = sineTable.tick(index1*11)*0.05;
  double value13 = sineTable.tick(index1*12);
  double value14 = sineTable.tick(index1*13)*0.05;
  double value15 = sineTable.tick(index1*14)*0.05;
  double value16 = sineTable.tick(index1*15)*0.05;
  double value17 = sineTable.tick(index1*16);

  return(value0 + value1 + value2 + value3 + value4 + value5 + value6 + value7 + value8 + value9 + value10 + value11 + value12 + value13 + value14 + value15 + value16 + value17)*0.02;
  
  
}
