#include <Arduino.h>
#include <Ps3Controller.h>
#include <Motors.h>

Motor MotorRightUp(26, 25, 27);
Motor MotorRightDown(12, 14, 13);
Motor MotorLeftDown(17, 5, 16);
Motor MotorLeftUp(2, 4, 14);

int player = 0;
int battery = 0;

void notify(){
  //---------------- Analog stick value events ---------------
  if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
    Serial.println();
    if(Ps3.data.analog.stick.ly > 0 && Ps3.data.analog.stick.lx == 0){
      
    }
  }

  if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
    Serial.print("Moved the right stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
    Serial.println();
  }

  //---------- Analog shoulder/trigger button events ----------
  if( abs(Ps3.event.analog_changed.button.l1)){
    Serial.print("Pressing the left shoulder button: ");
    Serial.println(Ps3.data.analog.button.l1, DEC);
  }

  if( abs(Ps3.event.analog_changed.button.r1) ){
    Serial.print("Pressing the right shoulder button: ");
    Serial.println(Ps3.data.analog.button.r1, DEC);
  }

  if( abs(Ps3.event.analog_changed.button.l2) ){
    Serial.print("Pressing the left trigger button: ");
    Serial.println(Ps3.data.analog.button.l2, DEC);
  }

  if( abs(Ps3.event.analog_changed.button.r2) ){
    Serial.print("Pressing the right trigger button: ");
    Serial.println(Ps3.data.analog.button.r2, DEC);
  }
  //---------------------- Battery events ---------------------
  if( battery != Ps3.data.status.battery ){
    battery = Ps3.data.status.battery;
    Serial.print("The controller battery is ");
    if( battery == ps3_status_battery_charging )      Serial.println("charging");
    else if( battery == ps3_status_battery_full )     Serial.println("FULL");
    else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
    else if( battery == ps3_status_battery_low)       Serial.println("LOW");
    else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
    else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
    else Serial.println("UNDEFINED");
  }
}

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("01:02:03:04:05:06");

    Serial.println("Ready.");
}

void loop()
{
    if(!Ps3.isConnected())
        return;
    //-------------------- Player LEDs -------------------


    //------ Digital cross/square/triangle/circle buttons ------
    if( Ps3.data.button.cross && Ps3.data.button.down )
        Serial.println("Pressing both the down and cross buttons");
    if( Ps3.data.button.square && Ps3.data.button.left )
        Serial.println("Pressing both the square and left buttons");
    if( Ps3.data.button.triangle && Ps3.data.button.up )
        Serial.println("Pressing both the triangle and up buttons");
    if( Ps3.data.button.circle && Ps3.data.button.right )
        Serial.println("Pressing both the circle and right buttons");

    if( Ps3.data.button.l1 && Ps3.data.button.r1 )
        Serial.println("Pressing both the left and right bumper buttons");
    if( Ps3.data.button.l2 && Ps3.data.button.r2 )
        Serial.println("Pressing both the left and right trigger buttons");
    if( Ps3.data.button.l3 && Ps3.data.button.r3 )
        Serial.println("Pressing both the left and right stick buttons");
    if( Ps3.data.button.select && Ps3.data.button.start )
        Serial.println("Pressing both the select and start buttons");

    delay(2000);
}