/*
  Motors.cpp - Library for flashing Motors code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "analogWrite.h"
#include "Motors.h"

Motor::Motor(uint8_t pin_EN, uint8_t pin_IN1, uint8_t pin_IN2, motorWires route){
    _pin_EN = pin_EN;
    if(route == routeA){
        _pin_IN1 = pin_IN1;
        _pin_IN2 = pin_IN2;
    }
    else if(route == routeB){
        _pin_IN1 = pin_IN2;
        _pin_IN2 = pin_IN1;
    }
    else{
        _pin_IN1 = pin_IN1;
        _pin_IN2 = pin_IN2;
    }
}

void Motor::begin(){
    pinMode(_pin_EN, OUTPUT);
    analogWriteChannel(_pin_IN1);
    analogWriteChannel(_pin_IN2);
}

void Motor::Move(uint8_t speed, rotateDirection direction){
    Speed(speed);
    Direction(direction);
};

void Motor::Move(){
    digitalWrite(_pin_EN, HIGH);
};

void Motor::Stop(){
    digitalWrite(_pin_EN, LOW);
};

void Motor::Direction(rotateDirection direction){
    _direction = direction;
    if(_direction == Forward) {
        analogWrite(_pin_IN1, int(map(_speed,0,100,0,255)), 255);
        analogWrite(_pin_IN2, 0, 255);
    }
    else if(_direction == Backward) {
        analogWrite(_pin_IN1, 0, 255);
        analogWrite(_pin_IN2,int(map(_speed,0,100,0,255)), 255);
    }
};

rotateDirection Motor::Direction(){
    return _direction;
};

void Motor::Speed(uint8_t speed){
    _speed = speed;
    analogWrite(_pin_EN, int(map(_speed,0,100,0,255)), 255);
};

uint8_t Motor::Speed(){
    return _speed;
};