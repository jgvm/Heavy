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
enum motorWires {
  routeA,
  routeB
};

enum rotateDirection {
  clockWise,
  clockWise_R
};

class Motor{
  public:
  
    //Motor (Pin_EN, Pin_IN1, Pin_IN2, route = routeA)
    Motor(uint8_t pin_EN, uint8_t pin_IN1, uint8_t pin_IN2, motorWires route = routeA);
    
    void Start(uint8_t speed, rotateDirection direction);
    void Start();
    void Stop();
    void changeDirection(rotateDirection direction);
    void toggleDirection();
    void changeSpeed(uint8_t speed);
    bool getState();
  private:
    //Pins
    uint8_t _pin_EN;
    uint8_t _pin_IN1;
    uint8_t _pin_IN2;

    //Values
    uint8_t _speed;
    rotateDirection _direction;
    bool _state;

    //Auxiliar functions
    uint8_t _setSpeed(uint8_t speed);
    void _updateState();
};

class HBridge{
  public:
    HBridge(Motor* left, Motor* right);
    void forward(int speed);
    void backward(int speed);
    void turnLeft(int speed, float ratio);
    void turnRight(int speed, float ratio);
    void rotate(rotateDirection direction);

  private:
    int _speed;
    bool _directionY; /* 0 = front, 1 = back */
    rotateDirection _directionX;
    float _ratio;
    Motor* _left;
    Motor* _right;
};
#endif