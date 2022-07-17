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
    _speed = speed;
    digitalWrite(_pin_EN, LOW);
    if(_speed == 0) {
        _direction = Stoped;
        analogWrite(_pin_IN1, 0, 255);
        analogWrite(_pin_IN2, 0, 255);
    }
    else if(_speed > 0) {
        _direction = Forward;
        analogWrite(_pin_IN1, abs(map(_speed,0,100,0,255)), 255);
        analogWrite(_pin_IN2, 0, 255);
    }
    else if(_speed < 0) {
        _direction = Backward;
        analogWrite(_pin_IN1, 0, 255);
        analogWrite(_pin_IN2, abs(map(_speed,0,100,0,255)), 255);
    }
    digitalWrite(_pin_EN, HIGH);
};

void Motor::Speed(int8_t speed, motorDirection forceDirection){
    _speed = abs(speed);
    _direction = forceDirection;
    digitalWrite(_pin_EN, LOW);
    if(forceDirection == Forward) {
        analogWrite(_pin_IN1, abs(map(_speed,0,100,0,255)), 255);
        analogWrite(_pin_IN2, 0, 255);
    }
    else if(forceDirection == Backward) {
        analogWrite(_pin_IN1, 0, 255);
        analogWrite(_pin_IN2, abs(map(_speed,0,100,0,255)), 255);
    }
    else{
        analogWrite(_pin_IN1, 0, 255);
        analogWrite(_pin_IN2, 0, 255);
    }
    digitalWrite(_pin_EN, HIGH);

};

int8_t Motor::Speed(){
    return _speed;
};

motorDirection Motor::Direction(){
    if(_speed == 0) {
        return Stoped;
    }
    else if(_speed > 0) {
        return Forward;
    }
    else if(_speed < 0) {
        return Backward;
    }
};