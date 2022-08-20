#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

//HCSR04 Sensors,With an array to loop through each
  #define Sensors 2
  #define max_dist 400
   NewPing sonar[Sensors] = {   
    NewPing(10, 11, max_dist),
    NewPing(8, 9, max_dist)
  };

//Global Variables
//PID Control
volatile int Left,Right,D_fe,Sx,Cp,Dp,Kpe = 0;

//Servo Object PWM-3, 5, 6, 9, 10, 11
#define servoPin 5
Servo servo;

//Colour Sensor
/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
const int interruptPin = 2;
volatile boolean state = false;
void isr() 
{
  state = true;
}
/* tcs.getRawData() does a delay(Integration_Time) after the sensor readout.
We don't need to wait for the next integration cycle because we receive an interrupt when the integration cycle is complete*/
void getRawData_noDelay(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  *c = tcs.read16(TCS34725_CDATAL);
  *r = tcs.read16(TCS34725_RDATAL);
  *g = tcs.read16(TCS34725_GDATAL);
  *b = tcs.read16(TCS34725_BDATAL);
}

void setup() {
servo.attach(servoPin);
Serial.begin(115200);
//Setup Colour Sensor
 pinMode(interruptPin, INPUT_PULLUP); //TCS interrupt output is Active-LOW and Open-Drain
  attachInterrupt(digitalPinToInterrupt(interruptPin), isr, FALLING);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
  // Set persistence filter to generate an interrupt for every RGB Cycle, regardless of the integration limits
  tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE); 
  tcs.setInterrupt(true);
  
  Serial.flush();
}

void loop() {
  //Get sensor input(Critical Function)
  noInterrupts();
    delay(50);
    Left = sonar[0].ping_cm();
    Right = sonar[1].ping_cm();
  
    if(Left > Right){
      Cp = Left;
     }
     if(Right > Left){
      Cp = Right;
     }

    //Colour Sensor
    if (state) {
    uint16_t r, g, b, c, colorTemp, lux;
    getRawData_noDelay(&r, &g, &b, &c);
    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);
    
    Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");
    Serial.flush();

    tcs.clearInterrupt();
    state = false;
    interrupts();
    }
}

/*
This mode uses pid control to move the car forward
adjusting its steering angle unless an interrupt is triggered

Steering Angle(Sx)= Proprtional Gain(Kp) * Cross Track Error(Kpe)
Kp = Maximum Output/Input
Kpe = Current position(Cp) - Desired Position(Dp)[Volatile]
*/
void normal_mode(){
  //Find Kp
  D_fe = Left + Right; //This is the most the car can be away from one wall
  int Mx = 180;//This is the maximum a servo can turn
  int Kp = (Mx/D_fe);

  //Find Kpe
  Kpe = (Cp-Dp);
//Steering Angle for normal Mode
  Sx = (Kp*Kpe);  
  servo.write(Sx);
}
