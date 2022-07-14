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

enum rotateDirection {
  Forward,
  Backward,
};

class Motor{
  public:
    //Motor (Pin_EN, Pin_IN1, Pin_IN2, route = routeA)
    Motor(uint8_t pin_EN, uint8_t pin_IN1, uint8_t pin_IN2, motorWires route = routeA);
    void begin();
    void Move(uint8_t speed, rotateDirection direction);
    void Move();
    void Stop();
    void Direction(rotateDirection direction);
    rotateDirection Direction();
    void Speed(uint8_t speed);
    uint8_t Speed();

  private:
    //Pins
    uint8_t _pin_EN;

    uint8_t _pin_IN1;
    uint8_t _pin_IN2;

    //Values
    uint8_t _speed;
    rotateDirection _direction;
    rotateDirection _direction_prev;
};
#endif