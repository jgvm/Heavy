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

// Values Left Stick
#define StickLeftY    map(-Ps3.data.analog.stick.ly, -128, 128, -100, 100)
#define StickLeftX    map(Ps3.data.analog.stick.lx, -128, 128, -100, 100)

// Values Right Stick
#define StickRightY    map(-Ps3.data.analog.stick.ry, -128, 128, -100, 100)
#define StickRightX    map(Ps3.data.analog.stick.rx, -128, 128, -100, 100)

// Ranges Left Stick -- Forward, Backward, Right, Left
#define StickLeftForward   ((-Ps3.data.analog.stick.ly > 0) && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range ))
#define StickLeftBackward  ((-Ps3.data.analog.stick.ly < 0) && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range ))
#define StickLeftRight     ((Ps3.data.analog.stick.lx > 0) && (-Ps3.data.analog.stick.ly > -range && -Ps3.data.analog.stick.ly < range ))
#define StickLeftLeft      ((Ps3.data.analog.stick.lx < 0) && (-Ps3.data.analog.stick.ly > -range && -Ps3.data.analog.stick.ly < range ))

#define StickLeftUpRight   (-Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.lx > range)
#define StickLeftDownRight (-Ps3.data.analog.stick.ly < range && Ps3.data.analog.stick.lx > range)
#define StickLeftUpLeft    (-Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.lx < -range)
#define StickLeftDownLeft  (-Ps3.data.analog.stick.ly < range && Ps3.data.analog.stick.lx < -range)

// Ranges Right Stick -- Forward, Backward, Right, Left
#define StickRightForward  ((-Ps3.data.analog.stick.ry < 0) && (Ps3.data.analog.stick.rx > -range && Ps3.data.analog.stick.rx < range ))
#define StickRightBackward ((-Ps3.data.analog.stick.ry > 0) && (Ps3.data.analog.stick.rx > -range && Ps3.data.analog.stick.rx < range ))
#define StickRightRight    ((Ps3.data.analog.stick.rx > 0) && (Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range ))
#define StickRightLeft     ((Ps3.data.analog.stick.rx < 0) && (Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range ))


void notify(){
  //---------------- Analog stick value events ---------------
  //Event booth Sticks
/*   if((abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2) && (abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 )){
    // Frente --- Derecha
    if(StickLeftForward && StickRightRight){
      // Serial.print(" Forward ----- Right");
      MotorRightUp.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorRightDown.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorLeftUp.Speed(StickLeftY, Forward);
      MotorLeftDown.Speed(StickLeftY, Forward);
    } 
    // Frente --- Izquierda
    else if(StickLeftForward && StickRightLeft){
      // Serial.print(" Forward ----- Left");
      MotorRightUp.Speed(StickLeftY, Forward);
      MotorRightDown.Speed(StickLeftY, Forward);
      MotorLeftUp.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
      MotorLeftDown.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
    } 
    // Atras --- Derecha
    else if(StickLeftBackward && StickRightRight){
      // Serial.print(" Backward ----- Right");
      MotorRightUp.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
      MotorRightDown.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
      MotorLeftUp.Speed(StickLeftY, Backward);
      MotorLeftDown.Speed(StickLeftY, Backward);
    } 
    // Atras --- Izquierda
    else if(StickLeftBackward && StickRightLeft){
      // Serial.print(" Backward ----- Left");
      MotorRightUp.Speed(StickLeftY, Backward);
      MotorRightDown.Speed(StickLeftY, Backward);
      MotorLeftUp.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
      MotorLeftDown.Speed(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
    } 
    // Derecha --- Derecha
    else if(StickLeftRight && StickRightRight){
      // Serial.print(" Right --- Right");
      MotorRightUp.Speed(StickLeftX, Backward);
      MotorRightDown.Speed(StickLeftX - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorLeftUp.Speed(StickLeftX, Forward);
      MotorLeftDown.Speed(StickLeftX - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
    }
    // Derecha --- Izquierda
    else if(StickLeftRight && StickRightLeft){
      // Serial.print(" Right --- Left");
      MotorRightUp.Speed(StickLeftX - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
      MotorRightDown.Speed(StickLeftX, Forward);
      MotorLeftUp.Speed(StickLeftX - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
      MotorLeftDown.Speed(StickLeftX, Backward);
    }
    // Izquierda --- Derecha
    else if(StickLeftLeft && StickRightRight){
      // Serial.print(" Left --- Right");
      MotorRightUp.Speed(StickLeftX -  map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
      MotorRightDown.Speed(StickLeftX, Forward);
      MotorLeftUp.Speed(StickLeftX -  map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorLeftDown.Speed(StickLeftX, Backward);
    }
    // Izquierda --- Izquierda
    else if(StickLeftLeft && StickRightLeft){
      // Serial.print(" Left --- Left");
      MotorRightUp.Speed(StickLeftX, Backward);
      MotorRightDown.Speed(StickLeftX -  map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
      MotorLeftUp.Speed(StickLeftX, Forward);
      MotorLeftDown.Speed(StickLeftX -  map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
    }
  }


  //Event Left stick 
  else  */if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
    // Forward and Backward
    if(StickLeftForward || StickLeftBackward){
      Serial.print(" Forward or Backward");
      MotorRightUp.   Speed(StickLeftY);
      MotorRightDown. Speed(StickLeftY);
      MotorLeftUp.    Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY);
    } // Side by side
    else if(StickLeftRight || StickLeftLeft){
      Serial.print(" Right or Left");
      MotorRightUp.   Speed(-StickLeftX);
      MotorRightDown. Speed(StickLeftX);
      MotorLeftUp.    Speed(StickLeftX);
      MotorLeftDown.  Speed(-StickLeftX);
    } 
    else if(StickLeftUpRight || StickLeftDownLeft){
      Serial.print(" Up Right or Down Left");
      MotorRightUp.   Speed(0);
      MotorRightDown. Speed(StickLeftX);
      MotorLeftUp.    Speed(StickLeftY);
      MotorLeftDown.  Speed(0);
    } // abajo derecha 
    else if(StickLeftDownRight || StickLeftUpLeft){
      Serial.print(" Down Right or Up Left");
      MotorRightUp.   Speed(-StickLeftX);
      MotorRightDown. Speed(0);
      MotorLeftUp.    Speed(0);
      MotorLeftDown.  Speed(StickLeftY);
    }  

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
    if(StickRightRight){
      Serial.print(" Rotate Right");
      MotorRightUp.Speed(StickRightX, Forward);
      MotorRightDown.Speed(StickRightX, Forward);
      MotorLeftUp.Speed(StickRightX, Backward);
      MotorLeftDown.Speed(StickRightX, Backward);
    }// rotacion isquierda
    else if(StickRightLeft){
      Serial.print(" Rotate Left");
      MotorRightUp.Speed(StickRightX, Backward);
      MotorRightDown.Speed(StickRightX, Backward);
      MotorLeftUp.Speed(StickRightX, Forward);
      MotorLeftDown.Speed(StickRightX, Forward);
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

void onDisconnect(){
  Ps3.end();
  Serial.println("Connecting...");
  Ps3.begin();
  while(!Ps3.isConnected());
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
  Ps3.attachOnDisconnect(onDisconnect);
  Ps3.begin();
  

  Serial.println("Ready.");
}

void loop()
{
  if(!Ps3.isConnected())
    return;
}
