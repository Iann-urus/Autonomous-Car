#include <Servo.h>
#include <NewPing.h>

// Motor A connections
int enA = 5;
int in1 = 10;
int in2 = 11;

//Servo
int servoPin = 9;
Servo servo;
//Colour Sensor
#define S2 7
#define S3 8
#define out 6

int frequency = 0;
int Red,Green,Blue = 0;
int counter = 0;
int Left = 0;
float St,gain = 0;
int match_direction = 0;
#define TRIGGER_PIN  12
#define ECHO_PIN     13  
NewPing sonar(TRIGGER_PIN, ECHO_PIN,400); 
void setup() {
Serial.begin(9600);
  
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  //Colour Sensor
   pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(out, INPUT);
   servo.attach(servoPin);
   servo.write(60);
   //delay(1000);
   //servo.write(115);
}
void loop() {
//speed_time();
searchColours();
look_time();
}
void ped(){
  if(Left < 20)//41 for actual map
    gain = 10.0/float(Left);
    St = round(gain*40.0);
    servo.write(St);
    //Serial.println(St+2);
    //delay(10);
}
void speed_time(){
  // Turn on motors
  Left = sonar.ping_cm();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 190);
  delay(100);
}

void searchColours(){
  digitalWrite(S2, LOW);                                           //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green 
  digitalWrite(S3, LOW);                                           
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again, if you have trouble with this expression check the bottom of the code
  //delay(5);  
  digitalWrite(S3, HIGH);                                         //Here we select the other color (set of photodiodes) and measure the other colors value using the same techinque
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  //delay(5);  
  digitalWrite(S2, HIGH);  
  Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  //delay(5);  
}

void look_time(){
  if (Red <=20 && Green <=20 && Blue <=20) //If the values are low it's likely the white color (all the colors are present)
      forward(),
      Serial.println("White");                    
      
  else if (Blue>Red && Green>Blue)      //if Red value is the lowest one and smaller thant 23 it's likely Red
      right(),
      Serial.println("Orange");

  else if (Blue<Green && Blue<Red && Blue<22)//Same thing for Blue
      left(),
      Serial.println("Blue");
  else
     forward(),
     Serial.println("Unknown");
  //if the color is not recognized, you can add as many as you want
    
}
void left(){
  servo.write(0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(500);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 135);
  delay(2100);
  analogWrite(enA, 150);
  ped();
}
void right(){
  servo.write(0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 140);
  delay(890);
  servo.write(170);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 108);
  delay(4200);
  analogWrite(enA, 120);
}
void forward(){
  servo.write(60);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 105);
  //delay(10);
}
