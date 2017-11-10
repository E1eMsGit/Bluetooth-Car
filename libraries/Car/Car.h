#ifndef Car_h
#define Car_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif 

#define CM 1
#define INC 0

class Car
{
  public:
    Car(int, int, int, int, int, int);
    void setMotorsSpeed(int, int);
    void forward();
    void forwardLeft();
    void forwardRight();
    void left();
    void right();
    void backward();
    void backwardLeft();
    void backwardRight();
    void stand();
  
  private:
    int motorL1_, motorL2_, inputL_;
    int motorR1_, motorR2_, inputR_;    
};

#endif
