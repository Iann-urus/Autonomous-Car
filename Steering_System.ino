#include <Servo.h>
#include <NewPing.h>
//Ultrasonic sensor
  #define Sensors 2
  #define max_dist 400
  NewPing sonar[Sensors] = {    //Create an array to loop through the sensor readings
    NewPing(10, 11, max_dist),
    NewPing(8, 9, max_dist)
  };
//Create global variables
int Left,Right,D_fe,Sx,Current_Trajectory,KD_fe = 0;
int Kpe = 0;//Desired Trajectory to balance on both sides,also Kpe  
//Create an object for the servo
#define servoPin 5
Servo servo;
void setup() {
    servo.attach(servoPin); 
    Serial.begin(115200);   
}
void loop() {
  getKpe();
  normal_mode();
  Serial.print(",");
  Serial.print(Left);
  Serial.print(",");
  Serial.print(Right);
  Serial.print(",Servo Angle:");
  Serial.print(Sx);
  Serial.print(",D_fe");
  Serial.print(D_fe);
  Serial.print(",Kpe:");
  Serial.println(Kpe);
}  
void getKpe(){
  delay(50);
  Left = sonar[0].ping_cm();
  Right = sonar[1].ping_cm();
   D_fe =(Left + Right);
   KD_fe =((Left + Right)/2);
   if(Left > Right){
    Current_Trajectory = Left;
   }
   if(Right > Left){
    Current_Trajectory = Right;
   }
   if(Current_Trajectory == Left){
    Serial.print("T:");
    Serial.print(Current_Trajectory);
   }
   if(Current_Trajectory == Right){
    Serial.print("F:");
    Serial.print(Current_Trajectory);
   }
   Kpe = (Current_Trajectory-KD_fe);//Desired Trajectory to balance on both sides,also Kpe  
}
void normal_mode(){
  int Mx = 180;
  int Kp = (Mx/D_fe);
  Sx = (Kp * Kpe);
  servo.write(Sx);
  }
