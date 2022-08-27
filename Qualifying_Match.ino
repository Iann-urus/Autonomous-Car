#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

//HCSR04 Sensors,With an array to loop through each
  #define Sensors 2
  #define max_dist 400
   NewPing sonar[Sensors] = {   
    NewPing(10, 11, max_dist),
    NewPing(8, 9, max_dist)
  };
  
//Motor connections
int enA = 1;
int in1 = 20;
int in2 = 3;

//Global Variables
int counter,counter2 = 0;//keep track of the laps
//PID Control
volatile int Left,Right,D_fe,Sx,Cp,Dp,Kpe = 0;

//Colour sensor 
// set to false if using a common cathode LED
#define commonAnode true
// our RGB -> eye-recognized gamma color
byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
float red,green,blue = 0;

//Servo Object PWM-3, 5, 6, 9, 10, 11
#define servoPin 5
Servo servo;

//Timing(Delay Replacement)
long pM,pM2,pM3 = 0; //Comparison for the timer,not int because it quickly becomes big
long hcsr04 = 50;//the intervals for the ultrasonic sensors 

void setup() {
servo.attach(servoPin);
Serial.begin(115200);

// Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
 if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
 // gamma table helps convert RGB colors to what humans see
for (int i=0; i<256; i++) {
  float x = i;
  x /= 255;
  x = pow(x, 2.5);
  x *= 255;

  if (commonAnode) {
    gammatable[i] = 255 - x;
  } else {
    gammatable[i] = x;
  }
}
}

void loop() {
  //Get sensor input(Critical Function)
  //Get sensor readings every 50ms
  unsigned long cM = millis();
  if(cM - pM > hcsr04){
    pM = cM;
    tcs.setInterrupt(false);  // turn on LED
    tcs.setInterrupt(true);  // turn off LED
    Left = sonar[0].ping_cm();
    Right = sonar[1].ping_cm();
  
    if(Left > Right){
      Cp = Left;
     }
     if(Right > Left){
      Cp = Right;
     }
  
  /*
  if(currentMillis2 - previousMillis2 > 2000){
    previousMillis2 = currentMillis2;
    Serial.print("Left:");Serial.print(Left);
    Serial.print(", Right");Serial.println(Right);
  */
    
     //Colour sensor
    tcs.getRGB(&red, &green, &blue);
    red = int(red);
    green = int(green);
    blue = int(blue);
  }
    Serial.print("R: "); Serial.print(red); Serial.print(" ");
    Serial.print("G: "); Serial.print(green); Serial.print(" ");
    Serial.print("B: "); Serial.print(blue); Serial.print(" ");
    Serial.println(" ");
    Serial.flush();
    no_obstacles();
}

/*
This mode uses pid control to move the car forward
adjusting its steering angle unless an interrupt is triggered

Steering Angle(Sx)= Proprtional Gain(Kp) * Cross Track Error(Kpe)
Kp = Maximum Output/Input
Kpe = Current position(Cp) - Desired Position(Dp)[Volatile]
*/

void no_obstacles(){
  //Find Kp
  D_fe = Left + Right; //This is the most the car can be away from one wall
  int Mx = 180;//This is the maximum a servo can turn
  int Kp = (Mx/D_fe);

  //Find Kpe
  Kpe = (Cp-Dp);
//Steering Angle for normal Mode
  Sx = (Kp*Kpe);  
  servo.write(Sx);

  //Detect colours
  //Orange
  if(red >=155){
    red = NULL;
    if(green <= 48){
      green = NULL;
   }
  }
  //Blue
  if(blue >= 120){
    blue = NULL;
    if(green <=90){
      green = NULL;
   }
  }
  
  //Turn Right
    if(bool(int(red == NULL) & int(green == NULL))){
        // Turn on motors
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        
        // deccelerate from normal to 1/4 speed
        for (int i = 130; i < 65; --i) {
          analogWrite(enA, i);
        }
        
        servo.write(90);
        unsigned long cM2 = millis();
        //Serial.println(servo.read());
        if(cM2 - pM2 > 5000){
          pM2 = cM2;
          servo.write(Sx);
          //Serial.println(servo.read());
        }
            
        counter = counter++; 
      
  }
    //Turn Left
    if(bool(int(blue == NULL) & int(green == NULL))){
      // Turn on motors
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      
      for (int i = 130; i < 65; --i) {
        analogWrite(enA, i);
      }
      servo.write(180);
      unsigned long cM3 = millis();
      if(cM3 - pM3 > 5000){
      pM3 = cM3;
      servo.write(Sx);
      }
      counter = counter++;
  }
}
