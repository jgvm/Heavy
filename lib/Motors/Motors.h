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
    void Speed(int8_t speed);
    void Speed(int8_t speed, motorDirection forceDirection);
    int8_t Speed();
    void Efect(int8_t efect);
    int8_t Efect();
    int8_t PWM();
    motorDirection Direction();

  private:
    //Pins
    uint8_t _pin_EN;

    uint8_t _pin_IN1;
    uint8_t _pin_IN2;

    //Values
    int8_t _speed;
    int8_t _efect;
    int8_t _PWM;



    motorDirection _direction;
};
#endif