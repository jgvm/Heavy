#include <Arduino.h>
#include <Ps3Controller.h>
#include <Motors.h>

Motor MotorRightUp(26, 25, 27, routeB);
Motor MotorRightDown(12, 14, 13,routeB);
Motor MotorLeftUp(2, 4, 15);
Motor MotorLeftDown(17, 5, 16,routeB);

int player = 0;
int battery = 0;

void notify(){
  //---------------- Analog stick value events ---------------
  if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
    // alfrente
    if(Ps3.data.analog.stick.ly < 0 && (Ps3.data.analog.stick.lx > -62 && Ps3.data.analog.stick.lx < 62 )){
      Serial.print(" Forward");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
    } // atras
    else if(Ps3.data.analog.stick.ly > 0 && (Ps3.data.analog.stick.lx > -62 && Ps3.data.analog.stick.lx < 62 )){
      Serial.print(" Backward");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
    } // derecha
    else if((Ps3.data.analog.stick.ly > -62 && Ps3.data.analog.stick.ly < 62) && Ps3.data.analog.stick.lx > 0){
      Serial.print(" Right");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
    } // isquierda
    else if(Ps3.data.analog.stick.ly == 0 && Ps3.data.analog.stick.lx < 0){
      Serial.print(" Left");
      MotorRightUp.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Forward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Backward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Forward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Backward);
    } // derecha arriba
    else if(Ps3.data.analog.stick.ly > 0 && Ps3.data.analog.stick.lx > 0){
      Serial.print(" Forward Right");
      MotorRightUp.Stop();
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Backward);
      MotorLeftDown.Stop();
    } // isquierda arriba
    else if(Ps3.data.analog.stick.ly > 0 && Ps3.data.analog.stick.lx < 0){
      Serial.print(" Forward Left");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorRightDown.Stop();
      MotorLeftUp.Stop();
      MotorLeftDown.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Backward);
    } // derecha abajo
    else if(Ps3.data.analog.stick.ly < 0 && Ps3.data.analog.stick.lx > 0){
      Serial.print(" Backward Right");
      MotorRightUp.Stop();
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Forward);
      MotorLeftDown.Stop();
    } // isquierda abajo
    else if(Ps3.data.analog.stick.ly < 0 && Ps3.data.analog.stick.lx < 0){
      Serial.print(" Backward Left");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorRightDown.Stop();
      MotorLeftUp.Stop();
      MotorLeftDown.Move(map(Ps3.data.analog.stick.ly,0,128,0,100), Forward);
    } // 
    Serial.print(" " + String(MotorRightUp.Speed()));
    Serial.print(" " + String(MotorRightDown.Speed()));
    Serial.print(" " + String(MotorLeftUp.Speed()));
    Serial.print(" " + String(MotorLeftDown.Speed()));

    Serial.println();

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
}

void onConnect(){
    Serial.println("Connected.");
}

void setup()
{
  MotorRightUp.begin();
  MotorRightDown.begin();
  MotorLeftDown.begin();
  MotorLeftUp.begin();
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
}