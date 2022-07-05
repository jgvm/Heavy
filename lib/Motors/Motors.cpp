/*
  Motors.cpp - Library for flashing Motors code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Motors.h"

uint8_t Motor::_setSpeed(uint8_t speed){
    _speed = map(0,100, 0,255, speed);
    return _speed;
};

void Motor::_updateState(){
    if(_state){
        analogWrite(_pin_EN, _speed);
        if(_direction == clockWise){
            digitalWrite(_pin_IN1, true);
            digitalWrite(_pin_IN2, false);
        }
        if(_direction == clockWise_R){
            digitalWrite(_pin_IN1, false);
            digitalWrite(_pin_IN2, true);
        }
    }
    else{
        digitalWrite(_pin_EN, 0);
        digitalWrite(_pin_IN1, 0);
        digitalWrite(_pin_IN2, 0);
    }
};
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
    pinMode(pin_EN, OUTPUT);
    pinMode(pin_IN1, OUTPUT);
    pinMode(pin_IN2, OUTPUT);
    _setSpeed(0);
    _state=false;
    _updateState();
}
void Motor::Start(uint8_t speed, rotateDirection direction){
    if(_speed != speed) _speed = speed;
    if(_direction != direction) _direction = direction;
    _updateState();
};
void Motor::Start(){
    _state = true;
    _updateState();
};
void Motor::Stop(){
    _state = false;
    _updateState();
};
void Motor::changeDirection(rotateDirection direction){
    if(_direction != direction) {
        _direction = direction;
        _updateState();
    }
};
void Motor::toggleDirection(){
    if(_direction==clockWise){
        _direction = clockWise_R;
    }
    else if(_direction==clockWise_R){
            _direction=clockWise;
    }
    _updateState();

};
void Motor::changeSpeed(uint8_t speed){
    if(_speed != speed) {
        _speed = speed;
        _updateState();
    }
};
bool Motor::getState(){
    return _state;
};

HBridge::HBridge(Motor* left, Motor* right){
    _left = left;
    _right = right;
}