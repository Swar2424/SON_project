#ifndef MYENVELOPE_H_INCLUDED
#define MYENVELOPE_H_INCLUDED


class MyEnvelope{
public:
  MyEnvelope(int SR);
  
  void setReleased(float b);
  float tick();
private:
  int samplingRate;
  int envelopeIndex;
  float envelopeValue;
  bool isMute;
  bool isReleased;
};

#endif  // SINE_H_INCLUDED
