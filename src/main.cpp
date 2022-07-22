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
#define Ps3_data_analog_stick_ly (-Ps3.data.analog.stick.ly)
#define Ps3_data_analog_stick_lx (Ps3.data.analog.stick.ly)

#define StickLeftY        map(Ps3_data_analog_stick_ly,-128,128,-100,100)
#define StickLeftX        map(Ps3_data_analog_stick_ly,-128,128,-100,100)

// Values Right Stick
#define Ps3_data_analog_stick_ry (-Ps3.data.analog.stick.ry)
#define Ps3_data_analog_stick_rx (Ps3.data.analog.stick.rx)

#define StickRightY       map(Ps3_data_analog_stick_ry,-128,128,-100,100)
#define StickRightX       map(Ps3_data_analog_stick_rx,-128,128,-100,100)

#define StickRightX_fLx   map(Ps3_data_analog_stick_rx,-128,128,-abs(StickLeftX),abs(StickLeftX))
#define StickRightX_fLy   map(Ps3_data_analog_stick_rx,-128,128,-abs(StickLeftY),abs(StickLeftY))


// Ranges Left Stick -- Forward, Backward, Right, Left
#define StickLeftUp         (Ps3_data_analog_stick_ly>=range)
#define StickLeftDown       (Ps3_data_analog_stick_ly<=-range)
#define StickLeftLeft       (Ps3_data_analog_stick_lx<=-range)
#define StickLeftRight      (Ps3_data_analog_stick_lx>=range)
#define StickLeftCenter     ((!StickLeftUp)&&(!StickLeftDown)&&(!StickLeftRight)&&(!StickLeftLeft))

#define StickLeftUpLeft     ((StickLeftUp)&&(StickLeftLeft))
#define StickLeftUpRight    ((StickLeftUp)&&(StickLeftRight))
#define StickLeftDownRight  ((StickLeftDown)&&(StickLeftRight))
#define StickLeftDownLeft   ((StickLeftDown)&&(StickLeftLeft))

#define StickLeftXY         (abs(Ps3_data_analog_stick_lx)>abs(Ps3_data_analog_stick_ly))
#define StickLeftYX         (abs(Ps3_data_analog_stick_lx)<abs(Ps3_data_analog_stick_ly))
#define StickLeftXeY        (abs(Ps3_data_analog_stick_lx)==abs(Ps3_data_analog_stick_ly))

bool StickLeftActive = false;

// Ranges Right Stick -- Forward, Backward, Right, Left
#define StickRightUp         (Ps3_data_analog_stick_ry>=range)
#define StickRightDown       (Ps3_data_analog_stick_ry<=-range)
#define StickRightLeft       (Ps3_data_analog_stick_rx<=-range)
#define StickRightRight      (Ps3_data_analog_stick_rx>=range)
#define StickRightCenter     ((!StickRightUp)&&(!StickRightDown)&&(!StickRightRight)&&(!StickRightLeft))

#define StickRightUpLeft     ((StickRightUp)&&(StickRightLeft))
#define StickRightUpRight    ((StickRightUp)&&(StickRightRight))
#define StickRightDownRight  ((StickRightDown)&&(StickRightRight))
#define StickRightDownLeft   ((StickRightDown)&&(StickRightLeft))

#define StickRightXY         (abs(Ps3_data_analog_stick_rx)>abs(Ps3_data_analog_stick_ry))
#define StickRightYX         (abs(Ps3_data_analog_stick_rx)<abs(Ps3_data_analog_stick_ry))
#define StickRightXeY        (abs(Ps3_data_analog_stick_rx)==abs(Ps3_data_analog_stick_ry))

bool StickRightActive = false;

void notify(){
  //---------------- Analog stick value events ---------------
  //Event Left stick 
  bool StickLeftAction = false;
  if( (abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2)){
  bool StickLeftAction = true;
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(Ps3_data_analog_stick_ly, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
    if(!StickLeftCenter) StickLeftActive = true;
    else StickLeftActive = false;
  }

  //Event right stick 
  bool StickRightAction = false;
  if((abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2)){
  bool StickRightAction = true;
    Serial.print("Moved the right stick:");
    Serial.print(" x="); Serial.print(Ps3_data_analog_stick_rx, DEC);
    Serial.print(" y="); Serial.print(Ps3_data_analog_stick_ry, DEC);
    Serial.println();
    if(!StickRightCenter) {StickRightActive = true;} 
    else {StickRightActive = false;}
  }

  //Event booth Sticks
  if(StickLeftActive && StickRightActive && (StickLeftAction || StickRightAction)){
    StickLeftAction = false;
    StickRightAction = false;
    if(StickLeftUp && StickRightRight){
      MotorLeftUp.    Speed(StickLeftY);                                MotorRightUp.   Speed(StickLeftY - StickRightX_fLy);
      MotorLeftDown.  Speed(StickLeftY);                                MotorRightDown. Speed(StickLeftY - StickRightX_fLy);
    } 
    else if(StickLeftUp && StickRightLeft){
      MotorLeftUp.    Speed(StickLeftY + StickRightX_fLy);              MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY + StickRightX_fLy);              MotorRightDown. Speed(StickLeftY);
    } 
    else if(StickLeftDown && StickRightRight){
      MotorLeftUp.    Speed(StickLeftY);                                MotorRightUp.   Speed(StickLeftY + StickRightX_fLy);
      MotorLeftDown.  Speed(StickLeftY);                                MotorRightDown. Speed(StickLeftY + StickRightX_fLy);
    } 
    else if(StickLeftDown && StickRightLeft){
      MotorLeftUp.    Speed(StickLeftY - StickRightX_fLy);              MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY - StickRightX_fLy);              MotorRightDown. Speed(StickLeftY);
    } 
    else if(StickLeftRight && StickRightRight){
      MotorLeftUp.    Speed(StickLeftX );                               MotorRightUp.   Speed(-StickLeftX );
      MotorLeftDown.  Speed(-StickLeftX + StickRightX_fLx);             MotorRightDown. Speed(StickLeftX - StickRightX_fLx);
    }
    else if(StickLeftRight && StickRightLeft){
      MotorLeftUp.    Speed(StickLeftX + StickRightX_fLx);              MotorRightUp.   Speed(-StickLeftX - StickRightX_fLx);
      MotorLeftDown.  Speed(-StickLeftX);                               MotorRightDown. Speed(StickLeftX);
    }
    else if(StickLeftLeft && StickRightRight){
      MotorLeftUp.    Speed(StickLeftX + StickRightX_fLx);               MotorRightUp.   Speed(-StickLeftX - StickRightX_fLx);
      MotorLeftDown.  Speed(-StickLeftX);                                MotorRightDown. Speed(StickLeftX);
    }
    else if(StickLeftLeft && StickRightLeft){
      MotorLeftUp.    Speed(StickLeftX);                                 MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(-StickLeftX - StickRightX_fLx);              MotorRightDown. Speed(StickLeftX + StickRightX_fLx);
    }
    // Down Left or Up Right and Y Mayor (⦯ ⦬)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftYX){
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftY);
    } 
    //Derecha arriba XY (🡥)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXeY){
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(0);
      MotorLeftDown.  Speed(0);                     MotorRightDown. Speed(StickLeftX);
    } 
    //Down Left or Up Right and X Mayor ( ⦫ ⦨)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXY){
      MotorLeftUp.    Speed(StickLeftX);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftX);
    } 
    // Up Left and X Mayor(⦩⦪)
    else if(( StickLeftUpLeft||StickLeftDownRight ) && StickLeftXY){
      MotorLeftUp.    Speed(StickLeftX+StickLeftY); MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(-StickLeftX);           MotorRightDown. Speed(StickLeftX+StickLeftY);
    } 
    //Derecha abajo XY (🡦)
    else if(StickLeftDownRight && StickLeftXeY){
      MotorLeftUp.    Speed(0);                     MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(0);
    }  
    //Derecha abajo Y Mayor (⦭⦮)
    else if(( StickLeftUpLeft||StickLeftDownRight ) && StickLeftYX){
      MotorLeftUp.    Speed(StickLeftX+StickLeftY); MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(StickLeftX+StickLeftY);
    } 
  }
  
  //Actions when only Left stick is Active
  else if( StickLeftActive && !StickRightActive && StickLeftAction){
    StickLeftAction = false;
    // Forward and Backward (⇅)
    if(StickLeftUp || StickLeftDown){
      Serial.print(" Forward or Backward");
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(StickLeftY);
    } 
    // Side by side (⇄)
    else if(StickLeftRight || StickLeftLeft){
      Serial.print(" Right or Left");
      MotorLeftUp.    Speed(StickLeftX);            MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(-StickLeftX);           MotorRightDown. Speed(StickLeftX);
    } 
    //Derecha arriba Y Mayor (⦯ ⦬)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftYX){
      Serial.print(" Up Right or Down Left");
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftY);
    } 
    //Derecha arriba XY (🡥)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXeY){
      Serial.print(" Up Right or Down Left");
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(0);
      MotorLeftDown.  Speed(0);                     MotorRightDown. Speed(StickLeftX);
    } 
    //Derecha arriba X Mayor ( ⦫ ⦨)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXY){
      Serial.print(" Up Right or Down Left");
      MotorLeftUp.    Speed(StickLeftX);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftX);
    } 
    //Derecha abajo X Mayor(⦩⦪)
    else if(( StickLeftUpLeft||StickLeftDownRight ) && StickLeftXY){
      Serial.print(" Down Right or Up Left");
      MotorLeftUp.    Speed(StickLeftX+StickLeftY); MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(-StickLeftX);           MotorRightDown. Speed(StickLeftX+StickLeftY);
    } 
    //Derecha abajo XY (🡦)
    else if(StickLeftDownRight && StickLeftXeY){
      Serial.print(" Down Right or Up Left");
      MotorLeftUp.    Speed(0);                     MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(0);
    }  
    //Derecha abajo Y Mayor (⦭⦮)
    else if(( StickLeftUpLeft||StickLeftDownRight ) && StickLeftYX){
      Serial.print(" Down Right or Up Left");
      MotorLeftUp.    Speed(StickLeftX+StickLeftY); MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(StickLeftX+StickLeftY);
    } 

    Serial.print(" " + String(MotorRightUp.Speed()));
    Serial.print(" " + String(MotorRightDown.Speed()));
    Serial.print(" " + String(MotorLeftUp.Speed()));
    Serial.print(" " + String(MotorLeftDown.Speed()));

    Serial.println();
  }


  //Event right stick 
  else if(!StickLeftActive && StickRightActive && StickRightAction){
    StickRightAction = false;
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
