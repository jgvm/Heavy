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

// Values Booth Sticks -- Positives 
#define StickLeftXp    map((Ps3.data.analog.stick.lx>0) ?  Ps3.data.analog.stick.lx:0, 0,128,0,100)
#define StickLeftYp    map((Ps3.data.analog.stick.ly<0) ? -Ps3.data.analog.stick.ly:0, 0,128,0,100)
#define StickRightXp   map((Ps3.data.analog.stick.rx>0) ?  Ps3.data.analog.stick.rx:0, 0,128,0,100)
#define StickRightYp   map((Ps3.data.analog.stick.ry<0) ? -Ps3.data.analog.stick.ry:0, 0,128,0,100)

// Values Booth Sticks -- Negatives
#define StickLeftXn    map((Ps3.data.analog.stick.lx<0) ? -Ps3.data.analog.stick.lx:0, 0,128,0,100)
#define StickLeftYn    map((Ps3.data.analog.stick.ly>0) ?  Ps3.data.analog.stick.ly:0, 0,128,0,100)
#define StickRightXn   map((Ps3.data.analog.stick.rx<0) ? -Ps3.data.analog.stick.rx:0, 0,128,0,100)
#define StickRightYn   map((Ps3.data.analog.stick.ry>0) ?  Ps3.data.analog.stick.ry:0, 0,128,0,100)

// // Values Right Stick -- With maximum Stick Maximum Y 
#define StickRightXrfp   map((Ps3.data.analog.stick.rx>0) ?  Ps3.data.analog.stick.rx:0, 0,128,0,Ps3.data.analog.stick.ly)
#define StickRightXrfn   map((Ps3.data.analog.stick.rx<0) ? -Ps3.data.analog.stick.rx:0, 0,128,0,Ps3.data.analog.stick.ly)
#define StickRightXrbp   map((Ps3.data.analog.stick.rx>0) ?  Ps3.data.analog.stick.rx:0, 0,128,0,Ps3.data.analog.stick.ly)
#define StickRightXrbn   map((Ps3.data.analog.stick.rx<0) ? -Ps3.data.analog.stick.rx:0, 0,128,0,Ps3.data.analog.stick.ly)

// Ranges Left Stick -- Forward, Backward, Right, Left
#define StickLeftRangeForward   ((Ps3.data.analog.stick.ly < 0) && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range ))
#define StickLeftRangeBackward  ((Ps3.data.analog.stick.ly > 0) && (Ps3.data.analog.stick.lx > -range && Ps3.data.analog.stick.lx < range ))
#define StickLeftRangeRight     ((Ps3.data.analog.stick.lx > 0) && (Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range ))
#define StickLeftRangeLeft      ((Ps3.data.analog.stick.lx < 0) && (Ps3.data.analog.stick.ly > -range && Ps3.data.analog.stick.ly < range ))

// Ranges Left Stick -- Corners
#define StickLeftRangeUpRight (Ps3.data.analog.stick.ly < -range && Ps3.data.analog.stick.lx > range)
#define StickLeftRangeDownRight (Ps3.data.analog.stick.ly > range && Ps3.data.analog.stick.lx > range)
#define StickLeftRangeUpLeft (Ps3.data.analog.stick.ly < -range && Ps3.data.analog.stick.lx < -range)
#define StickLeftRangeDownLeft (Ps3.data.analog.stick.ly > range && Ps3.data.analog.stick.lx < -range)

// Ranges Right Stick -- Forward, Backward, Right, Left
#define StickRightRangeForward   ((Ps3.data.analog.stick.ry < 0) && (Ps3.data.analog.stick.rx > -range && Ps3.data.analog.stick.rx < range ))
#define StickRightRangeBackward  ((Ps3.data.analog.stick.ry > 0) && (Ps3.data.analog.stick.rx > -range && Ps3.data.analog.stick.rx < range ))
#define StickRightRangeRight     ((Ps3.data.analog.stick.rx > 0) && (Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range ))
#define StickRightRangeLeft      ((Ps3.data.analog.stick.rx < 0) && (Ps3.data.analog.stick.ry > -range && Ps3.data.analog.stick.ry < range ))

void notify(){
  //---------------- Analog stick value events ---------------
  //Event booth Sticks
  if((abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2) && (abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 )){
    // Frente --- Derecha
    if(StickLeftRangeForward && StickRightRangeRight){
      Serial.print(" Forward ----- Right");
      MotorRightUp.Move(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorRightDown.Move(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorLeftUp.Move(StickLeftY, Forward);
      MotorLeftDown.Move(StickLeftY, Forward);
    } 
    // Frente --- Izquierda
    else if(StickLeftRangeForward && StickRightRangeLeft){
      Serial.print(" Forward ----- Left");
      MotorRightUp.Move(StickLeftY, Forward);
      MotorRightDown.Move(StickLeftY, Forward);
      MotorLeftUp.Move(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
      MotorLeftDown.Move(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
    } 
    // Atras --- Derecha
    else if(StickLeftRangeBackward && StickRightRangeRight){
      Serial.print(" Backward ----- Right");
      MotorRightUp.Move(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
      MotorRightDown.Move(StickLeftY - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
      MotorLeftUp.Move(StickLeftY, Backward);
      MotorLeftDown.Move(StickLeftY, Backward);
    } 
    // Atras --- Izquierda
    else if(StickLeftRangeBackward && StickRightRangeLeft){
      Serial.print(" Backward ----- Left");
      MotorRightUp.Move(StickLeftY, Backward);
      MotorRightDown.Move(StickLeftY, Backward);
      MotorLeftUp.Move(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
      MotorLeftDown.Move(StickLeftY - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
    } 
    // Derecha --- Derecha
    else if(StickLeftRangeRight && StickRightRangeRight){
      Serial.print(" Right --- Right");
      MotorRightUp.Move(StickLeftX, Backward);
      MotorRightDown.Move(StickLeftX - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorLeftUp.Move(StickLeftX, Forward);
      MotorLeftDown.Move(StickLeftX - map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
    }
    // Derecha --- Izquierda
    else if(StickLeftRangeRight && StickRightRangeLeft){
      Serial.print(" Right --- Left");
      MotorRightUp.Move(StickLeftX - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
      MotorRightDown.Move(StickLeftX, Forward);
      MotorLeftUp.Move(StickLeftX - map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
      MotorLeftDown.Move(StickLeftX, Backward);
    }
    // Izquierda --- Derecha
    else if(StickLeftRangeLeft && StickRightRangeRight){
      Serial.print(" Left --- Right");
      MotorRightUp.Move(StickLeftX -  map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Backward);
      MotorRightDown.Move(StickLeftX, Forward);
      MotorLeftUp.Move(StickLeftX -  map(Ps3.data.analog.stick.rx,0,128,0,StickLeftY), Forward);
      MotorLeftDown.Move(StickLeftX, Backward);
    }
    // Izquierda --- Izquierda
    else if(StickLeftRangeLeft && StickRightRangeLeft){
      Serial.print(" Left --- Left");
      MotorRightUp.Move(StickLeftX, Backward);
      MotorRightDown.Move(StickLeftX -  map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Forward);
      MotorLeftUp.Move(StickLeftX, Forward);
      MotorLeftDown.Move(StickLeftX -  map(Ps3.data.analog.stick.rx,-128,0,0,StickLeftY), Backward);
    }
  }

  //Event right stick 
  else if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
    // frente
    if(StickLeftRangeForward){
      Serial.print(" Forward");
      MotorRightUp.Move(StickLeftYp - StickRightXrfp, Forward);
      MotorRightDown.Move(StickLeftYp - StickRightXrfp, Forward);
      MotorLeftUp.Move(StickLeftYp - StickRightXn , Forward);
      MotorLeftDown.Move(StickLeftYp - StickRightXn , Forward);
    } // atras
    else if(StickLeftRangeBackward){
      Serial.print(" Backward");
      MotorRightUp.Move(StickLeftY, Backward);
      MotorRightDown.Move(StickLeftY, Backward);
      MotorLeftUp.Move(StickLeftY, Backward);
      MotorLeftDown.Move(StickLeftY, Backward);
    } // derecha
    else if(StickLeftRangeRight){
      Serial.print(" Right");
      MotorRightUp.Move(StickLeftX, Backward);
      MotorRightDown.Move(StickLeftX, Forward);
      MotorLeftUp.Move(StickLeftX, Forward);
      MotorLeftDown.Move(StickLeftX, Backward);
    } // isquierda
    else if(StickLeftRangeLeft){
      Serial.print(" Left");
      MotorRightUp.Move(StickLeftX, Forward);
      MotorRightDown.Move(StickLeftX, Backward);
      MotorLeftUp.Move(StickLeftX, Backward);
      MotorLeftDown.Move(StickLeftX, Forward);
    } // arriba derecha 
    else if(StickLeftRangeUpRight){
      Serial.print(" Up Right");
      MotorRightUp.Stop();
      MotorRightDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2, 0, 128, 0, 100), Forward);
      MotorLeftUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2, 0, 128, 0, 100), Forward);
      MotorLeftDown.Stop();
    } // abajo derecha 
    else if(StickLeftRangeDownRight){
      Serial.print(" Down Right");
       MotorRightUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
      MotorRightDown.Stop();
      MotorLeftUp.Stop();
      MotorLeftDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
    } // arriba isquierda 
    else if(StickLeftRangeUpLeft){
      Serial.print(" Up Left");
      MotorRightUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Forward);
      MotorRightDown.Stop();
      MotorLeftUp.Stop();
      MotorLeftDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Forward);
    } // abajo isquierda 
    else if(StickLeftRangeDownLeft){
      Serial.print(" Down Left");
      MotorRightUp.Stop();
      MotorRightDown.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
      MotorLeftUp.Move(map((Ps3.data.analog.stick.ly + Ps3.data.analog.stick.lx)/2,0,128,0,100), Backward);
      MotorLeftDown.Stop();
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
    if(StickRightRangeRight){
      Serial.print(" Rotate Right");
      MotorRightUp.Move(StickRightX, Forward);
      MotorRightDown.Move(StickRightX, Forward);
      MotorLeftUp.Move(StickRightX, Backward);
      MotorLeftDown.Move(StickRightX, Backward);
    }// rotacion isquierda
    else if(StickRightRangeLeft){
      Serial.print(" Rotate Left");
      MotorRightUp.Move(StickRightX, Backward);
      MotorRightDown.Move(StickRightX, Backward);
      MotorLeftUp.Move(StickRightX, Forward);
      MotorLeftDown.Move(StickRightX, Forward);
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
  Ps3.begin();

  Serial.println("Ready.");
}

void loop()
{
  if(!Ps3.isConnected())
    return;
}
