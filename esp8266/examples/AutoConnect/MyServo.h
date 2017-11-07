#ifndef MyServo_H
#define MyServo_H
#include <Arduino.h>
#include "Servo.h"
#define ENABLE_CONTROL_BY_TIME
#define T_PERIOD 6000
//#define ENABLE_CONTROL_BY_STEP
//#define T_RES 50
#define BUSY_STATE 1
#define FREE_STATE 0
//#define ENABLE_EN_PIN
class MyServo
{
  public:
    float ofsX;
    float minX;
    float maxX;
    float x0;
    float x1;
    float x;
    float dx;
    unsigned char stepTime;
    unsigned char nSteps;
    float v;
    float T;
	float t;
    int enablePin;
    int controlPin;
    char state;
    //-----------------//
    void writeAngle(float angle);   
    void init(int ctlPin,int enPin);
    float tAngle(float t);
    void turnOnServo();
    void turnOffServo();
    void turnServo();
	void reset();
  private:
    Servo mServo;
    float readAngle();
	
};
#endif

