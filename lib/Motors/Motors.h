/*
enum rotateDirection
    clockWise - 0
    clockWiseR - 1

map motorSpeed 0-255 to 0-100

Forward:
    rightMotor - clockWise
    leftMotor - clockWiseR
Backward:
    rightMotor - clockWiseR
    leftMotor - clockWise
*/

/*
  Motors.h - Library for flashing Motors code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef Motors_h
#define Motors_h

#include "Arduino.h"
#include "analogWrite.h"

enum motorWires {
  routeA,
  routeB
};
enum motorDirection {
  Forward=-1,
  Stoped=0,
  Backward=1
};

class Motor{
  public:
    //Motor (Pin_EN, Pin_IN1, Pin_IN2, route = routeA)
    Motor(uint8_t pin_EN, uint8_t pin_IN1, uint8_t pin_IN2, motorWires route = routeA);
    void begin();
    void Speed(int speed);
    void Speed(int speed, motorDirection forceDirection);
    int Speed();
    void Efect(int efect);
    int Efect();
    int PWM();
    motorDirection Direction();

  private:
    //Pins
    uint8_t _pin_EN;

    uint8_t _pin_IN1;
    uint8_t _pin_IN2;

    //Values
    int _speed;
    int _efect;
    int _PWM;
    motorDirection _direction;
    
    //Encoder
    long _pulses;
    int _rpm;
    uint8_t _pin_phaseA;
    uint8_t _pin_phaseB;
    void _atachEncoder( isr);
    void _readEncoder();
};
#endif