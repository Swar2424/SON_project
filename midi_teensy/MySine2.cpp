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
  smooth.setPole(0.3);
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
  double value2 = sineTable.tick(index*2)*(0.3*1);
  double value3 = sineTable.tick(index*3)*(0.3*0.5);
  double value4 = sineTable.tick(index*4)*(0.3*0.3);
  double value5 = sineTable.tick(index*5)*(0.3*0.2);
  double value6 = sineTable.tick(index*6)*(0.3*0.1);

  return(value1 + value2 + value3 + value4 + value5 + value6) * smooth.tick(envelope.tick());
  
}
