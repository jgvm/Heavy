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


/**
 *  Quadrature mode configuration structure
 */
enum Quadrature : uint8_t {
  ON    = 0x00, //!<  Enable quadrature mode CPR = 4xPPR
  OFF   = 0x01  //!<  Disable quadrature mode / CPR = PPR
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

    /**
     *  function enabling hardware interrupts for the encoder channels with provided callback functions
     *  if callback is not provided then the interrupt is not enabled
     * 
     * @param doA pointer to the A channel interrupt handler function
     * @param doB pointer to the B channel interrupt handler function
     * @param doIndex pointer to the Index channel interrupt handler function
     * 
     */
    void _enableInterrupts(void (*doA)() = nullptr, void(*doB)() = nullptr, void(*doIndex)() = nullptr);
    
    //  Encoder interrupt callback functions
    /** A channel callback function */
    void _handleA();
    /** B channel callback function */
    void _handleB();
    /** Index channel callback function */
    void _handleIndex();


    long _pulses;
    int _rpm;

    int pinA; //!< encoder hardware pin A
    int pinB; //!< encoder hardware pin B
    int index_pin; //!< index pin

     // Encoder configuration
    Pullup pullup; //!< Configuration parameter internal or external pullups
    Quadrature quadrature;//!< Configuration parameter enable or disable quadrature mode
    float cpr;//!< encoder cpr number


    int hasIndex(); //!< function returning 1 if encoder has index pin and 0 if not.

    volatile long pulse_counter;//!< current pulse counter
    volatile long pulse_timestamp;//!< last impulse timestamp in us
    volatile int A_active; //!< current active states of A channel
    volatile int B_active; //!< current active states of B channel
    volatile int I_active; //!< current active states of Index channel
    volatile bool index_found = false; //!< flag stating that the index has been found

    // velocity calculation variables
    float prev_Th, pulse_per_second;
    volatile long prev_pulse_counter, prev_timestamp_us;
};
#endif