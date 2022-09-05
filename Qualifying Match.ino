#include <NewPing.h>
#include <Servo.h>

#define servoPin 6
Servo servo;
#define sensors 2
#define max_dist 400
NewPing sonar[sensors] ={
  NewPing( 4, 5,max_dist),//Left(trig,echo)
  NewPing( 7, 8,max_dist)//Right
};
//Global Variables
int Left,Right = 0;
int Rtotal_val,Rnew_val,Ltotal_val,Lnew_val = 0;
float St,gain = 0;
//Motor connections
int enA = 9;
int in1 = 10;
int in2 = 11;

long pM,pM2,pM3 = 0;
void setup(){
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  servo.write(40);//Mid position
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
   // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  Serial.begin(9600);

}
void loop(){
  // Turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255);
 //unsigned long cM2 = millis();
   //if(cM2 -pM2 > 50){
    //pM2 = cM2;
    Left = sonar[0].ping_cm();
    Right = sonar[1].ping_cm();
    delay(50);
  // }
//unsigned long cM = millis();
//if(cM - pM > 200){
 // pM = cM;
if(Left < 41 && Right > 41){
    gain = 41.0/float(Left);
    St = round(gain*40.0);
    servo.write(St+4);
    delay(20);
}
if(Right < 41 && Left > 41){
    gain = float(Right)/41.0;
    St = round(gain*40.0);
    servo.write(St+4);
    delay(20);
} 
     Serial.print("S-");Serial.print(servo.read());
     Serial.print(";");Serial.print(int(St));
     Serial.print(",L-");Serial.print(Left);
     Serial.print(",R-");Serial.println(Right);
//}
}
/*
void turn_left(){
  
}
void turn_right(){
  
}
*/
