#include <Servo.h>
#include <NewPing.h>
//Ultrasonic sensor
#define Trig_pin2 11//Right
#define Echo_pin2 10
#define max_dist 400
/*
A low gain makes the system sluggish and unresponsive. 
A gain that is too high makes the axis oscillate or vibrate.
*/
#define Kp 180/20 //Proportional Gain
//This value is for the right trajectory relative to the Sonar sensor
#define desired_dist 5
//Create an object for the servo
int servoPin = 9;
Servo servo;
//Create an object for the Ultrasonic sensor
NewPing sonar(Trig_pin2,Echo_pin2,max_dist);

void setup() {
    servo.attach(servoPin); 
    Serial.begin(115200);   
}

void loop() {
/*
 * Calculate Steering angle
 * (180/20(Kp) * Cross Track Error(cm)(Ep)) =Steering Angle
 */
int actual_dist = sonar.ping_cm();
int Ep = (actual_dist - desired_dist);//Calculate Cross Track Error 
int steering_angle = ((Kp) * Ep);
if( actual_dist <= 5){
  steering_angle= 0;
 }
if(actual_dist >= 20){
  steering_angle = 180;
}
servo.write(steering_angle);
Serial.print(actual_dist);
Serial.print(',');
Serial.println(steering_angle);
delay(50);    
}
