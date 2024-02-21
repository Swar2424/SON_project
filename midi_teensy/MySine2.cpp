#include <cmath>

#include "MySine2.h"

#define SINE_TABLE_SIZE 16384

MySine2::MySine2(int SR) : 
sineTable(SINE_TABLE_SIZE),
phasor(SR),
envelope(SR),
smooth(),
gain(1.0),
samplingRate(SR),
isMute(false),
isReleased(false) {
  smooth.setDel(0.0);
  smooth.setPole(0.2);
}

void MySine2::setFrequency(float f){
  phasor.setFrequency(f);
}
    
void MySine2::setGain(float g){
  gain = g;
}

void MySine2::setReleased(float b){
  envelope.setReleased(b);
}
    
float MySine2::tick(){

  int index = phasor.tick()*SINE_TABLE_SIZE;
  double value1 = sineTable.tick(index)*(1);
  double value2 = sineTable.tick(index*2)*(0.3);
  double value3 = sineTable.tick(index*3)*(0.15);
  double value4 = sineTable.tick(index*4)*(0.09);
  double value5 = sineTable.tick(index*5)*(0.06);
  double value6 = sineTable.tick(index*6)*(0.03);

  return(value1 + value2 + value3 + value4 + value5 + value6) * smooth.tick(envelope.tick());
  
}
