# Autonomous-Car
![🏎️🚩Autonomous_Car 🏁](https://user-images.githubusercontent.com/67041860/188293683-f2aa7515-b62b-4c2e-be43-469af9fb9b77.png)
   
   ![GitHub last commit](https://img.shields.io/github/last-commit/Iann-urus/Autonomous-Car)

This project is an self-driving car with object avoidance.

Team members:Ian, Sammuel, Immanuel.

# Brief Overview.
This car was designed to participate in the WRO Future Engineers Category.
This documentation explains how the car functions as well as the solutions for various problems.
Team Information is provided as well.

# Hardware Schematic
![Autonomous car (4)](https://user-images.githubusercontent.com/67041860/188294082-4ce2c9ac-f2be-43a5-877b-57d8c173704d.png)

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





