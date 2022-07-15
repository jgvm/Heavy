#include <Arduino.h>
#include <Ps3Controller.h>
#include <Motors.h>

Motor MotorRightUp(26, 25, 27);
Motor MotorRightDown(12, 14, 13);
Motor MotorLeftUp(2, 4, 15 );
Motor MotorLeftDown(17, 5, 16, routeB);

int player = 0;
int battery = 0;

const int range = 20;

void notify(){
  //---------------- Analog stick value events ---------------

  //Event booth Sticks
  if((abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2) && (abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 )){
    // Frente --- Derecha
    if((Ps3.data.analog.stick.ly < 0 && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range )) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx > 0)){
      Serial.print(" Forward ----- Right");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Forward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
    } 
    // Frente --- Izquierda
    else if((Ps3.data.analog.stick.ly < 0 && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range )) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx < 0)){
      Serial.print(" Forward ----- Left");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Forward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Forward);
    } // Atras --- Derecha
    else if((Ps3.data.analog.stick.ly > 0 && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range )) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx > 0)){
      Serial.print(" Backward ----- Right");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Backward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Backward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
    } 
    // Atras --- Izquierda
    else if((Ps3.data.analog.stick.ly > 0 && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range )) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx < 0)){
      Serial.print(" Backward ----- Left");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Backward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100) - map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Backward);
    } 
    // Derecha --- Derecha
    else if(((Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range) && Ps3.data.analog.stick.lx > 0) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx > 0)){
      Serial.print(" Right --- Right");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Backward);
    }
    // Derecha --- Izquierda
    else if(((Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range) && Ps3.data.analog.stick.lx > 0) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx < 0)){
      Serial.print(" Right --- Left");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Backward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Forward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
    }
    // Izquierda --- Derecha
    else if(((Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range) && Ps3.data.analog.stick.lx < 0) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx > 0)){
      Serial.print(" Left --- Right");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Backward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Forward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
    }
    // Izquierda --- Izquierda
    else if(((Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range) && Ps3.data.analog.stick.lx < 0) && ((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx < 0)){
      Serial.print(" Left --- Left");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100) - map(Ps3.data.analog.stick.rx,0,128,0,100), Backward);
    }

  }

  //Event right stick 
  else if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
    // frente
    if(Ps3.data.analog.stick.ly < 0 && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range )){
      Serial.print(" Forward");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Forward);
    } // atras
    else if(Ps3.data.analog.stick.ly > 0 && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range )){
      Serial.print(" Backward");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.ly),0,128,0,100), Backward);
    } // derecha
    else if((Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range) && Ps3.data.analog.stick.lx > 0){
      Serial.print(" Right");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
    } // isquierda
    else if((Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range) && Ps3.data.analog.stick.lx < 0){
      Serial.print(" Left");
      MotorRightUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
      MotorRightDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorLeftUp.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Backward);
      MotorLeftDown.Move(map(Ps3.data.analog.stick.lx,0,128,0,100), Forward);
    } // arriba derecha 
    else if(Ps3.data.analog.stick.ly < -range && Ps3.data.analog.stick.lx > range){
      Serial.print(" Forward Right");
      MotorRightUp.Stop();
      MotorRightDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Forward);
      MotorLeftUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Forward);
      MotorLeftDown.Stop();
    } // arriba isquierda 
    else if(Ps3.data.analog.stick.ly < -range && Ps3.data.analog.stick.lx < -range){
      Serial.print(" Forward Left");
      MotorRightUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Forward);
      MotorRightDown.Stop();
      MotorLeftUp.Stop();
      MotorLeftDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Forward);
    } // abajo derecha 
    else if(Ps3.data.analog.stick.ly > range && Ps3.data.analog.stick.lx > range){
      Serial.print(" Backward Right");
       MotorRightUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
      MotorRightDown.Stop();
      MotorLeftUp.Stop();
      MotorLeftDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
    } // abajo isquierda 
    else if(Ps3.data.analog.stick.ly > range && Ps3.data.analog.stick.lx < -range){
      Serial.print(" Backward Left");
      MotorRightUp.Stop();
      MotorRightDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
      MotorLeftUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
      MotorLeftDown.Stop();
    } // 

    Serial.print(" " + String(MotorRightUp.Speed()));
    Serial.print(" " + String(MotorRightDown.Speed()));
    Serial.print(" " + String(MotorLeftUp.Speed()));
    Serial.print(" " + String(MotorLeftDown.Speed()));

    Serial.println();

  }
  //Event right stick 
  else if( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ){
    Serial.print("Moved the right stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
    Serial.println();
    // rotacion derecha
    if((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx > 0){
      Serial.print(" Rotate Right");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Forward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Forward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Backward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Backward);
    }// rotacion isquierda
    else if((Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range) && Ps3.data.analog.stick.rx < 0){
      Serial.print(" Rotate Left");
      MotorRightUp.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Backward);
      MotorRightDown.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Backward);
      MotorLeftUp.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Forward);
      MotorLeftDown.Move(map(abs(Ps3.data.analog.stick.rx),0,128,0,100), Forward);
    } 

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
