#include <Servo.h>

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
}
void loop() {
speed_time();
searchColours();
look_time();
/*
if(counter >= 12){
  kill();
 }
 */
}
void speed_time(){
  // Turn on motors
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
  if (Red <=15 && Green <=15 && Blue <=15) //If the values are low it's likely the white color (all the colors are present)
      servo.write(40),
      delay(100),
      Serial.println("White");                    
      
  else if (Red<Blue && Red<=Green && Red<23)      //if Red value is the lowest one and smaller thant 23 it's likely Red
      servo.write(80),
      delay(100),
      Serial.println("Red");

  else if (Blue<Green && Blue<Red && Blue<20)//Same thing for Blue
      servo.write(10),
      delay(100),
      Serial.println("Blue");
      
 else if (Green<Red && Green-Blue<= 8)           //Green it was a little tricky, you can do it using the same method as above (the lowest), but here I used a reflective object
      Serial.println("Green");     
      
  else
     Serial.println("Unknown"),
     servo.write(40);//if the color is not recognized, you can add as many as you want
    
}
