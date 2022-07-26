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

void Motor::Speed(int speed){
    _speed = abs(speed)>100?100:speed;
    int speed2PWM = map(abs(_speed),0,100,0,255);
    _PWM = speed2PWM - map(_efect,0,100,0,speed2PWM);
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

void Motor::Speed(int speed, motorDirection forceDirection){
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

int Motor::Speed(){
    return _speed;
};

void Motor::Efect(int efect){
    _efect = abs(efect);
    Speed(_speed);
};

int Motor::Efect(){
    return _efect;
};

int Motor::PWM(){
    return _PWM;
};

motorDirection Motor::Direction(){
    return _direction;
};