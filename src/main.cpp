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
#define Ps3_data_analog_stick_lx (Ps3.data.analog.stick.lx)
#define Ps3_data_analog_stick_ly (-Ps3.data.analog.stick.ly)

#define Ps3_data_analog_stick_lx_a abs(Ps3.data.analog.stick.lx)
#define Ps3_data_analog_stick_ly_a abs(Ps3.data.analog.stick.ly)

#define StickLeft_norm_X        map(Ps3_data_analog_stick_lx,-128,128,-100,100)
#define StickLeft_norm_Y        map(Ps3_data_analog_stick_ly,-128,128,-100,100)

#define StickLeft_norm_Xa        map(abs(Ps3_data_analog_stick_lx),0,128,0,100)
#define StickLeft_norm_Ya        map(abs(Ps3_data_analog_stick_ly),0,128,0,100)

#define StickLeft_norm_ABS  ((Ps3_data_analog_stick_lx_a>Ps3_data_analog_stick_ly_a)?StickLeft_norm_X:((Ps3_data_analog_stick_lx_a<Ps3_data_analog_stick_ly_a)?StickLeft_norm_Y:((StickLeft_norm_X/StickLeft_norm_Y)*StickLeft_norm_X)))

// Ranges Left Stick -- Forward, Backward, Right, Left
#define StickLeft_on_Center     ((Ps3_data_analog_stick_lx_a<range)&&(Ps3_data_analog_stick_ly_a<range)) //⌧
#define StickLeft_on_LeftRight  ((Ps3_data_analog_stick_lx_a!=0)&&(Ps3_data_analog_stick_ly_a<range)) //⇆
#define StickLeft_on_UpDown     ((Ps3_data_analog_stick_lx_a<range)&&(Ps3_data_analog_stick_ly_a!=0)) //⇵
#define StickLeft_on_UpRight    ((Ps3_data_analog_stick_lx_a>0)&&(Ps3_data_analog_stick_ly_a>0))      //⦬|⦨
#define StickLeft_on_DownLeft   ((Ps3_data_analog_stick_lx_a<0)&&(Ps3_data_analog_stick_ly_a>0))      //⦫|⦯
#define StickLeft_on_DownRight  ((Ps3_data_analog_stick_lx_a>0)&&(Ps3_data_analog_stick_ly_a<0))      //⦮|⦪
#define StickLeft_on_UpLeft     ((Ps3_data_analog_stick_lx_a<0)&&(Ps3_data_analog_stick_ly_a>0))      //⦩|⦭

// Values Right Stick
#define Ps3_data_analog_stick_rx (Ps3.data.analog.stick.rx)
#define Ps3_data_analog_stick_ry (-Ps3.data.analog.stick.ry)

#define Ps3_data_analog_stick_rx_a abs(Ps3.data.analog.stick.rx)
#define Ps3_data_analog_stick_ry_a abs(Ps3.data.analog.stick.ry)

#define StickRight_norm_X        map(Ps3_data_analog_stick_rx,-128,128,-100,100)
#define StickRight_norm_Y        map(Ps3_data_analog_stick_ry,-128,128,-100,100)

#define StickRight_norm_Xa        map(abs(Ps3_data_analog_stick_rx),0,128,0,100)
#define StickRight_norm_Ya        map(abs(Ps3_data_analog_stick_ry),0,128,0,100)

#define StickRight_norm_ABS  ((Ps3_data_analog_stick_rx_a>Ps3_data_analog_stick_ry_a)?StickRight_norm_X:((Ps3_data_analog_stick_rx_a<Ps3_data_analog_stick_ry_a)?StickRight_norm_Y:((StickRight_norm_X/StickRight_norm_Y)*StickRight_norm_X)))

// Ranges Right Stick -- Forward, Backward, Right, Left
#define StickRight_on_Center     ((Ps3_data_analog_stick_rx_a<range)&&(Ps3_data_analog_stick_ry_a<range)) //⌧
#define StickRight_on_LeftRight  ((Ps3_data_analog_stick_rx_a!=0)&&(Ps3_data_analog_stick_ry_a<range))    //⇆
#define StickRight_on_Right        ((Ps3_data_analog_stick_rx>0)&&(Ps3_data_analog_stick_ry_a<range))     //🡪
#define StickRight_on_Left         ((Ps3_data_analog_stick_rx<0)&&(Ps3_data_analog_stick_ry_a<range))     //🡨
#define StickRight_on_UpDown     ((Ps3_data_analog_stick_rx_a<range)&&(Ps3_data_analog_stick_ry_a!=0))    //⇵
#define StickRight_on_Up           ((Ps3_data_analog_stick_rx_a<range)&&(Ps3_data_analog_stick_ry>0))     //🡩
#define StickRight_on_Down         ((Ps3_data_analog_stick_rx_a<range)&&(Ps3_data_analog_stick_ry<0))     //🡫
#define StickRight_on_UpRight    ((Ps3_data_analog_stick_rx_a>0)&&(Ps3_data_analog_stick_ry_a>0))         //⦬|⦨
#define StickRight_on_DownLeft   ((Ps3_data_analog_stick_rx_a<0)&&(Ps3_data_analog_stick_ry_a>0))         //⦫|⦯
#define StickRight_on_DownRight  ((Ps3_data_analog_stick_rx_a>0)&&(Ps3_data_analog_stick_ry_a<0))         //⦮|⦪
#define StickRight_on_UpLeft     ((Ps3_data_analog_stick_rx_a<0)&&(Ps3_data_analog_stick_ry_a>0))         //⦩|⦭

#define Show true

void logData(bool active){
  if(active){
    Serial.println('-------------------------------------------------------------');
    Serial.println('\t\t\tLeft Stick');
    Serial.print('Lx:');
    Serial.print(Ps3_data_analog_stick_lx);
    Serial.print('\t\t\t');
    Serial.print('Ly:');
    Serial.print(Ps3_data_analog_stick_ly);
    Serial.println();
    Serial.print('Rx:');
    Serial.print(Ps3_data_analog_stick_rx);
    Serial.print('\t\t\t');
    Serial.print('Ry:');
    Serial.print(Ps3_data_analog_stick_ry);
    Serial.println();
    Serial.print('mA:');
    Serial.print(MotorLeftUp.PWM()*MotorLeftUp.Direction());
    Serial.print('\t\t\t');
    Serial.print('mB:');
    Serial.print(MotorRightUp.PWM()*MotorRightUp.Direction());
    Serial.println();
    Serial.print('mC:');
    Serial.print(MotorLeftDown.PWM()*MotorLeftDown.Direction());
    Serial.print('\t\t\t');
    Serial.print('mD:');
    Serial.print(MotorRightDown.PWM()*MotorRightDown.Direction());
    Serial.println();
    Serial.println('-------------------------------------------------------------'):
  }
}

void notify(){
  //---------------- Analog stick value events ---------------
  //Event Left stick 
  if( (abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2)){
    if(StickLeft_on_Center){
      MotorLeftUp.Speed(0);         MotorRightUp.Speed(0);
      MotorLeftDown.Speed(0);       MotorRightDown.Speed(0);
    }
    else if(StickLeft_on_LeftRight){
      MotorLeftUp.Speed(StickLeft_norm_Xa);         MotorRightUp.Speed(-StickLeft_norm_Xa);
      MotorLeftDown.Speed(-StickLeft_norm_Xa);       MotorRightDown.Speed(StickLeft_norm_Xa);
    }
    else if(StickLeft_on_UpDown){
      MotorLeftUp.Speed(StickLeft_norm_Y);         MotorRightUp.Speed(StickLeft_norm_Y);
      MotorLeftDown.Speed(StickLeft_norm_Y);       MotorRightDown.Speed(StickLeft_norm_Y);
    }
    else if(StickLeft_on_UpRight || StickLeft_on_DownLeft){
      MotorLeftUp.Speed(StickLeft_norm_ABS);                        MotorRightUp.Speed(StickLeft_norm_Y-StickLeft_norm_X);
      MotorLeftDown.Speed(StickLeft_norm_Y-StickLeft_norm_X);       MotorRightDown.Speed(StickLeft_norm_ABS);
    }
    else if(StickLeft_on_UpLeft || StickLeft_on_DownRight){
      MotorLeftUp.Speed(StickLeft_norm_X+StickLeft_norm_Y);         MotorRightUp.Speed(StickLeft_norm_ABS);
      MotorLeftDown.Speed(StickLeft_norm_ABS);                      MotorRightDown.Speed(StickLeft_norm_X+StickLeft_norm_Y);
    }
    logData(Show);
  }

  //Event right stick 
  if((abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2)){
    if(StickRight_on_Center){ //⌧
      MotorLeftUp.Efect(0);         MotorRightUp.Efect(0);
      MotorLeftDown.Efect(0);       MotorRightDown.Efect(0);
      if(StickLeft_on_Center){
        MotorLeftUp.Speed(0);         MotorRightUp.Speed(0);
        MotorLeftDown.Speed(0);       MotorRightDown.Speed(0);
      }
    }
    else if(StickRight_on_Right){ //StickRight to 🡪
      if(StickLeft_on_Center){
        MotorLeftUp.Speed(StickRight_norm_X);         MotorRightUp.Speed(-StickRight_norm_X);
        MotorLeftDown.Speed(StickRight_norm_X);       MotorRightDown.Speed(-StickRight_norm_X);
      }
      else if(StickLeft_on_UpDown){
        MotorLeftUp.Efect(StickRight_norm_X);         MotorRightUp.Efect(StickRight_norm_X);
        MotorLeftDown.Efect(StickRight_norm_X);       MotorRightDown.Efect(StickRight_norm_Y);
      }
      else if(StickLeft_on_LeftRight){
        MotorLeftUp.Efect(StickRight_norm_X);         MotorRightUp.Efect(-StickRight_norm_Xa);
        MotorLeftDown.Efect(-StickRight_norm_Xa);       MotorRightDown.Efect(StickRight_norm_Xa);
      }
      else if(StickLeft_on_UpRight || StickLeft_on_DownLeft){
        MotorLeftUp.Efect(StickRight_norm_ABS);                        MotorRightUp.Efect(StickRight_norm_Y-StickRight_norm_X);
        MotorLeftDown.Efect(StickRight_norm_Y-StickRight_norm_X);       MotorRightDown.Efect(StickRight_norm_ABS);
      }
      else if(StickLeft_on_UpLeft || StickLeft_on_DownRight){
        MotorLeftUp.Efect(StickRight_norm_X+StickRight_norm_Y);         MotorRightUp.Efect(StickRight_norm_ABS);
        MotorLeftDown.Efect(StickRight_norm_ABS);                      MotorRightDown.Efect(StickRight_norm_X+StickRight_norm_Y);
      }
    }
    else if(StickRight_on_Left){  //StickRight to 🡨
      if(StickLeft_on_Center){ //StickLeft to ⌧
        MotorLeftUp.Speed(-StickRight_norm_X);         MotorRightUp.Speed(StickRight_norm_X);
        MotorLeftDown.Speed(-StickRight_norm_X);       MotorRightDown.Speed(StickRight_norm_X);
      }
      else if(StickLeft_on_UpDown){ //StickLeft to ⇵
        MotorLeftUp.Efect(StickRight_norm_X);         MotorRightUp.Efect(StickRight_norm_X);
        MotorLeftDown.Efect(StickRight_norm_X);       MotorRightDown.Efect(StickRight_norm_Y);
      }
      else if(StickLeft_on_LeftRight){  //StickLeft to ⇆
        MotorLeftUp.Efect(StickRight_norm_X);         MotorRightUp.Efect(-StickRight_norm_Xa);
        MotorLeftDown.Efect(-StickRight_norm_Xa);       MotorRightDown.Efect(StickRight_norm_Xa);
      }
      else if(StickLeft_on_UpRight || StickLeft_on_DownLeft){
        MotorLeftUp.Efect(StickRight_norm_ABS);                        MotorRightUp.Efect(StickRight_norm_Y-StickRight_norm_X);
        MotorLeftDown.Efect(StickRight_norm_Y-StickRight_norm_X);       MotorRightDown.Efect(StickRight_norm_ABS);
      }
      else if(StickLeft_on_UpLeft || StickLeft_on_DownRight){
        MotorLeftUp.Efect(StickRight_norm_X+StickRight_norm_Y);         MotorRightUp.Efect(StickRight_norm_ABS);
        MotorLeftDown.Efect(StickRight_norm_ABS);                      MotorRightDown.Efect(StickRight_norm_X+StickRight_norm_Y);
      }
    }
    logData(Show);
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

void loop(){
}