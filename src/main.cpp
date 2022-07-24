#include <Arduino.h>
#include <Ps3Controller.h>
#include <Motors.h>


Motor MotorRightUp(17, 5, 16,routeB);//LD
Motor MotorRightDown(2, 4, 15);//LU
Motor MotorLeftUp(12, 14, 13 );//RD
Motor MotorLeftDown(26, 25, 27);//RU

int player = 0;
int battery = 0;

const int range = 20;

// Values Left Stick
#define Ps3_data_analog_stick_ly (-Ps3.data.analog.stick.ly)
#define Ps3_data_analog_stick_lx (Ps3.data.analog.stick.lx)

#define StickLeftY        map(Ps3_data_analog_stick_ly,-128,128,-100,100)
#define StickLeftX        map(Ps3_data_analog_stick_lx,-128,128,-100,100)

#define StickLeftYa        map(abs(Ps3_data_analog_stick_ly),0,128,0,100)
#define StickLeftXa        map(abs(Ps3_data_analog_stick_lx),0,128,0,100)

// Values Right Stick
#define Ps3_data_analog_stick_ry (-Ps3.data.analog.stick.ry)
#define Ps3_data_analog_stick_rx (Ps3.data.analog.stick.rx)

#define StickRightY       map(Ps3_data_analog_stick_ry,-128,128,-100,100)
#define StickRightX       map(Ps3_data_analog_stick_rx,-128,128,-100,100)

#define StickRightX_fLx   map(abs(Ps3_data_analog_stick_rx),0,128,0,StickLeftX)
#define StickRightX_fLy   map(abs(Ps3_data_analog_stick_rx),0,128,0,StickLeftY)

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
bool StickLeftAction = false;
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
bool StickRightAction = false;

void notify(){
  //---------------- Analog stick value events ---------------
  //Event Left stick 
  if( (abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2)){
    StickLeftAction = true;
    if(!StickLeftCenter) {StickLeftActive = true;}
    else {
      StickLeftActive = false;
    }
  }

  //Event right stick 
  if((abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2)){
    StickRightAction = true;
    if(!StickRightCenter) {StickRightActive = true;} 
    else {
      StickRightActive = false;
    }
  }

  //Event booth Sticks
  if(StickLeftActive && StickRightActive && (StickLeftAction || StickRightAction)){
    Serial.print("Booth Sticks\t\t");
    Serial.print("\t" + String(StickLeftY));
    Serial.print("\t" + String(StickLeftX));
    Serial.print("\t" + String(StickRightY));
    Serial.println("\t" + String(StickRightX));

    StickLeftAction = false;
    StickRightAction = false;
    // Up -- Right
    if((StickLeftUp && !StickLeftLeft && !StickLeftRight) && StickRightRight){
      MotorLeftUp.    Speed(StickLeftY);                                MotorRightUp.   Speed(StickLeftYa - StickRightX_fLy);
      MotorLeftDown.  Speed(StickLeftY);                                MotorRightDown. Speed(StickLeftYa - StickRightX_fLy);
    }
    // Up -- Left 
    else if((StickLeftUp && !StickLeftLeft && !StickLeftRight) && StickRightLeft){
      MotorLeftUp.    Speed(StickLeftYa - StickRightX_fLy);              MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftYa - StickRightX_fLy);              MotorRightDown. Speed(StickLeftY);
    } 
    // Down -- Right
    else if((StickLeftDown && !StickLeftLeft && !StickLeftRight) && StickRightRight){
      MotorLeftUp.    Speed(-StickLeftY);                                MotorRightUp.   Speed(-int(StickLeftYa - StickRightX_fLy));
      MotorLeftDown.  Speed(-StickLeftY);                                MotorRightDown. Speed(-int(StickLeftYa - StickRightX_fLy));
    } 
    // Down -- Left
    else if((StickLeftDown && !StickLeftLeft && !StickLeftRight) && StickRightLeft){
      MotorLeftUp.    Speed(-int(StickLeftYa - StickRightX_fLy));              MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(-int(StickLeftYa - StickRightX_fLy));              MotorRightDown. Speed(StickLeftY);
    } 
    // Right -- Right
    else if((StickLeftRight && !StickLeftUp && !StickLeftDown) && StickRightRight){
      MotorLeftUp.    Speed(StickLeftX );                               MotorRightUp.   Speed(-StickLeftX );
      MotorLeftDown.  Speed(-int(StickLeftXa - StickRightX_fLx));             MotorRightDown. Speed(StickLeftXa - StickRightX_fLx);
    }
    // Right -- Left
    else if((StickLeftRight && !StickLeftUp && !StickLeftDown) && StickRightLeft){
      MotorLeftUp.    Speed(StickLeftXa - StickRightX_fLx);              MotorRightUp.   Speed(-int(StickLeftXa - StickRightX_fLx));
      MotorLeftDown.  Speed(-StickLeftXa);                               MotorRightDown. Speed(StickLeftXa);
    } 
    // Left -- Right
    else if((StickLeftLeft && !StickLeftUp && !StickLeftDown) && StickRightRight){
      MotorLeftUp.    Speed(-int(StickLeftXa - StickRightX_fLx));          MotorRightUp.   Speed(StickLeftXa - StickRightX_fLx);
      MotorLeftDown.  Speed(StickLeftXa);                                MotorRightDown. Speed(-StickLeftXa);
    }
    // Left -- Left
    else if((StickLeftLeft && !StickLeftUp && !StickLeftDown) && StickRightLeft){
      MotorLeftUp.    Speed(-StickLeftX);                                 MotorRightUp.   Speed(StickLeftX);
      MotorLeftDown.  Speed(StickLeftXa - StickRightX_fLx);              MotorRightDown. Speed(-int(StickLeftXa - StickRightX_fLx));
    }
    // Down Left or Up Right and Y Mayor (⦯ ⦬)
    else if(StickLeftUpRight && StickLeftYX){
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftY);
    } 
    //Derecha arriba XY (🡥)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXeY){
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(0);
      MotorLeftDown.  Speed(0);                     MotorRightDown. Speed(StickLeftX);
    } 
    //Down-Left or Up-Right and X Mayor ( ⦫ ⦨)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXY){
      MotorLeftUp.    Speed(StickLeftX);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftX);
    } 
    // Up-Left or Down-Right and X Mayor(⦩⦪)
    else if(( StickLeftUpLeft||StickLeftDownRight ) && StickLeftXY){
      MotorLeftUp.    Speed(StickLeftX+StickLeftY); MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(-StickLeftX);           MotorRightDown. Speed(StickLeftX+StickLeftY);
    } 
    //Derecha abajo XY (🡦)
    else if(( StickLeftUpLeft||StickLeftDownRight ) && StickLeftXeY){
      MotorLeftUp.    Speed(0);                     MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(0);
    }
    //Derecha abajo Y Mayor (⦭⦮)
    else if(( StickLeftUpLeft||StickLeftDownRight ) && StickLeftYX){
      MotorLeftUp.    Speed(StickLeftX+StickLeftY); MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(StickLeftX+StickLeftY);
    }
    else if(StickRightCenter && StickLeftCenter){
      MotorLeftUp.    Speed(0);   MotorRightUp.   Speed(0);
      MotorLeftDown.  Speed(0);   MotorRightDown. Speed(0);
    } 
  }
  else if(!StickLeftActive && !StickRightActive && (StickLeftAction || StickRightAction)){
    //Centro ()
    Serial.println("Center\t\t");
    Serial.print("\t" + String(StickLeftY));
    Serial.print("\t" + String(StickLeftX));
    Serial.print("\t" + String(StickRightY));
    Serial.println("\t" + String(StickRightX));
    StickLeftAction = false;
    StickRightAction = false;
    MotorLeftUp.    Speed(0);   MotorRightUp.   Speed(0);
    MotorLeftDown.  Speed(0);   MotorRightDown. Speed(0);
  }

  //Actions when only Left stick is Active
  else if( StickLeftActive && !StickRightActive && StickLeftAction){
    Serial.println("Left Stick\t\t");
    Serial.print("\t" + String(StickLeftY));
    Serial.print("\t" + String(StickLeftX));
    Serial.print("\t" + String(StickRightY));
    Serial.println("\t" + String(StickRightX));

    StickLeftAction = false;
    // Forward and Backward (⇅)
    if((StickLeftUp && !StickLeftLeft && !StickLeftRight) || (StickLeftDown && !StickLeftLeft && !StickLeftRight)){
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(StickLeftY);
      MotorLeftDown.  Speed(StickLeftY);            MotorRightDown. Speed(StickLeftY);
    } 
    // Side by side (⇄)
    else if((StickLeftRight && !StickLeftUp && !StickLeftDown) || (StickLeftLeft && !StickLeftUp && !StickLeftDown)){
      MotorLeftUp.    Speed(StickLeftX);            MotorRightUp.   Speed(-StickLeftX);
      MotorLeftDown.  Speed(-StickLeftX);           MotorRightDown. Speed(StickLeftX);
    } 
    //Derecha arriba Y Mayor (⦯ ⦬)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftYX){
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftY);
    } 
    //Derecha arriba XY (🡥)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXeY){
      MotorLeftUp.    Speed(StickLeftY);            MotorRightUp.   Speed(0);
      MotorLeftDown.  Speed(0);                     MotorRightDown. Speed(StickLeftX);
    } 
    //Derecha arriba X Mayor ( ⦫ ⦨)
    else if(( StickLeftDownLeft||StickLeftUpRight ) && StickLeftXY){
      MotorLeftUp.    Speed(StickLeftX);            MotorRightUp.   Speed(StickLeftY-StickLeftX);
      MotorLeftDown.  Speed(StickLeftY-StickLeftX); MotorRightDown. Speed(StickLeftX);
    } 
    //Derecha abajo X Mayor(⦩⦪)
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
      MotorLeftUp.    Speed(StickLeftX+StickLeftY); MotorRightUp.   Speed(-StickLeftY);
      MotorLeftDown.  Speed(-StickLeftY);            MotorRightDown. Speed(StickLeftX+StickLeftY);
    } 
    //Centro ()
    else if(StickRightCenter){
      MotorLeftUp.    Speed(0);   MotorRightUp.   Speed(0);
      MotorLeftDown.  Speed(0);   MotorRightDown. Speed(0);
    } 
  }

  //Event right stick 
  else if(!StickLeftActive && StickRightActive && StickRightAction){
    Serial.println("Right Stick\t\t");
    Serial.print("\t" + String(StickLeftY));
    Serial.print("\t" + String(StickLeftX));
    Serial.print("\t" + String(StickRightY));
    Serial.println("\t" + String(StickRightX));

    StickRightAction = false;
    // rotacion derecha
    if(StickRightRight){
      MotorRightUp.Speed(StickRightX, Forward);
      MotorRightDown.Speed(StickRightX, Forward);
      MotorLeftUp.Speed(StickRightX, Backward);
      MotorLeftDown.Speed(StickRightX, Backward);
    }// rotacion isquierda
    else if(StickRightLeft){
      MotorRightUp.Speed(StickRightX, Backward);
      MotorRightDown.Speed(StickRightX, Backward);
      MotorLeftUp.Speed(StickRightX, Forward);
      MotorLeftDown.Speed(StickRightX, Forward);
    } 
    else if(StickRightCenter){
      MotorRightUp.Speed(0);
      MotorRightDown.Speed(0);
      MotorLeftUp.Speed(0);
      MotorLeftDown.Speed(0);
    } 
  }
  
/*   else if(!StickLeftActive && !StickRightActive && !StickLeftAction && !StickRightAction && StickRightCenterAction && StickLeftCenterAction){
    Serial.print('\t');Serial.print(Ps3_data_analog_stick_lx, DEC);
    Serial.print('\t');Serial.print(Ps3_data_analog_stick_ly, DEC);
    Serial.print('\t');Serial.print(Ps3_data_analog_stick_rx, DEC);
    Serial.print('\t');Serial.print(Ps3_data_analog_stick_ry, DEC);
    Serial.print('\t' + String(StickLeftActive));
    Serial.print('\t' + String(StickRightActive));
    Serial.print('\t' + String(StickLeftAction));
    Serial.print('\t' + String(StickRightAction));
    Serial.print('\t' + String(StickLeftUp));
    Serial.print('\t' + String(StickLeftRight));
    Serial.print('\t' + String(StickLeftDown));
    Serial.print('\t' + String(StickLeftLeft));
    Serial.println();
  }
 */
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
