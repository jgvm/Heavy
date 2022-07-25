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

void Motor::Speed(int8_t speed){
    _speed = abs(speed)>100?100:speed;
    uint8_t tmpSpeed = map(abs(_speed),0,100,0,255);
    _PWM = tmpSpeed-map(_efect,0,100,0,tmpSpeed);
    digitalWrite(_pin_EN, LOW);
    if(_speed == 0) {
        _direction = Stoped;
        analogWrite(_pin_IN1, 0, 255);
        analogWrite(_pin_IN2, 0, 255);
    }
    else if(_speed > 0) {
        _direction = Forward;
        analogWrite(_pin_IN1, _PWM, 255);
        analogWrite(_pin_IN2, 0, 255);
    }
    else if(_speed < 0) {
        _direction = Backward;
        analogWrite(_pin_IN1, 0, 255);
        analogWrite(_pin_IN2, _PWM, 255);
    }
    digitalWrite(_pin_EN, HIGH);
};

void Motor::Speed(int8_t speed, motorDirection forceDirection){
    _speed = speed;
    _direction = forceDirection;
    if(_direction == Forward) {
        Speed(abs(_speed));
    }
    else if(_direction == Backward) {
        Speed(-abs(_speed));
    }
    else{
        Speed(0);
    }
    digitalWrite(_pin_EN, HIGH);
};

int8_t Motor::Speed(){
    return _speed;
};

void Motor::Efect(int8_t efect){
    _efect = efect;
    Speed(_speed);
};

int8_t Motor::Efect(){
    return _efect;
};

motorDirection Motor::Direction(){
    return _direction;
};