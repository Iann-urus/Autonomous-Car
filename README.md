# Autonomous-Car
![🏎️🚩Autonomous_Car 🏁](https://user-images.githubusercontent.com/67041860/188293683-f2aa7515-b62b-4c2e-be43-469af9fb9b77.png)
   
   ![GitHub last commit](https://img.shields.io/github/last-commit/Iann-urus/Autonomous-Car)

This project is an self-driving car with object avoidance.

Team members: Ian, Sammuel.

# Brief Overview.
This car was designed to participate in the WRO Future Engineers Category.
This documentation explains how the car functions as well as the solutions for various problems.
Team Information is provided as well.

# Hardware Schematic
![Autonomous car (4)](https://user-images.githubusercontent.com/67041860/188294082-4ce2c9ac-f2be-43a5-877b-57d8c173704d.png)

# Program Flow
![Autonomous car (6)](https://user-images.githubusercontent.com/67041860/188424047-e76df53b-0001-4604-b3c4-72052f0333e2.png)

# Game Setting
The self-driving car challenge in this season is a Time Attack race: there will not be multiple cars at the same time on the track. 
Instead, one car per attempt will try to achieve the best time by driving several laps fully autonomously. 

![Screenshot 2022-09-04 051936](https://user-images.githubusercontent.com/67041860/188294321-a91b329c-b885-4ffd-91b0-917c33b6aa09.png)

   # Traffic Signs
   The traffic signs indicate the side of the lane the vehicle has to follow.
   
   The traffic sign to keep to the right side of the lane is a red pillar. 
   The traffic sign to keep to the left side of the lane is a green pillar.
   The vehicle is not allowed to move or knock down the traffic signs.
   
 # Turning the car around corners
 In order to turn the car around corners our team took advantage of the coloured strokes in the corners.
 
 ![Screenshot 2022-09-04 052815](https://user-images.githubusercontent.com/67041860/188294534-1f244f6a-5acb-4698-8cff-1d80c503d3d2.png)

In order to detect the colours we used a TCS230 TCS3200D Colour Recognition Sensor. 

We just need to convert the CMYK Colour Space to RGB and then differentiate between the orange and red.

         The Orange colour- 255, 102, 0 (RGB)
         The Blue colour-  0, 51, 255.

Not only that but the colours also help us to know whether to turn left or right depending on the one detected first.

To instruct the servo we used a conditional statement to check if any of the colours has been detected, if so we turn the servo 90 degrees for a few seconds.


         if(bool(int(blue == NULL) & int(green == NULL))){
           servo.write(180);
               unsigned long cM3 = millis();
               if(cM3 - pM3 > 5000){
               pM3 = cM3;
               servo.write(Sx);
               }
               counter = counter++;
           }

# Steering the Car(No Objects)
When we were picking a method of steering the car it needed the following criteria:
  
   -The amount of turning would depend on how far the car was from the wall.  
   -Fast and responsive.

We settled on proportional control.

The idea is lifted from PID control in control theory but in our case, we got away with the proportional control only.

![image](https://user-images.githubusercontent.com/67041860/188303485-502ce03b-050f-41bf-8dff-0fb3527edf15.png)
![Screenshot 2022-09-04 101626](https://user-images.githubusercontent.com/67041860/188302096-3a656055-6fff-4dba-b467-ddd44cf60f3b.png)

The steering angle in our case is :
            
         Steering angle = Proportional Gain * output
         //Gain = Output(Servo)/Input(Distance(cm))
         
This is assuming the servo has a defined central position 50(degrees)

          //Right
         if(Right < 41 && Left > 41){
              gain = float(Right)/41.0;
               St = round(gain*50.0);
           servo.write(round(St)+3);
         }
         
The function for the left was treated differently as we are moving from the central position 50 towards 0(degrees).
Thus the gain becomes:

         gain = 41.0/float(Left);
         St = round(gain*50.0);
         
         
# Object Avoidance(Final Matches)
The car is required to avoid the red and green pillars while moving to either side of the trock depending on the pillar colour.

![Screenshot 2022-09-04 103607](https://user-images.githubusercontent.com/67041860/188302778-67f52564-50bb-420f-b265-86ec70a80fbf.png)

The colour of the red traffic signs is RGB (238, 39, 55).
 The colour of the green traffic signs is RGB (68, 214, 44).

First we need to detect the objects.

This is done with on OpenCv python program.
We create a mask for the colours Green and Red respectively and the send an interrupt to the arduino if a specific colour has been detected.

      #Range of RED(HSV 0 255 255)
           up_r = np.array([178,255,255],np.uint8)#[180,255,255]
           low_r = np.array([158,100,100],np.uint8)#[136,87,111]
           mask_r = cv.inRange(hsv,low_r,up_r)
           
A 51,51 Kernel is then applied to make it easier to detect the colours.

      Red_blur = cv.GaussianBlur(mask_r,(51,51),0)

To reduce noise we set a thereshold for the colours to be filtered.This greatly reduces errors!

     #Threshold the blurred mask(GREEN)
      t,R_Thresh = cv.threshold(Red_blur,50,255,cv.THRESH_BINARY)
      
      

 







