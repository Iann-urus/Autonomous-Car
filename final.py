#dependancies
import time
import cv2 as cv
import numpy as np
import keyboard as kd
from picamera.array import PiRGBArray
from picamera import PiCamera
import RPi.GPIO as GPIO            # import RPi.GPIO module  
from time import sleep# lets us have a delay
'''
GPIO.setmode(GPIO.BCM)             # choose BCM or BOARD  
GPIO.setup(16, GPIO.OUT)
GPIO.setup(26, GPIO.OUT)
'''

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (720, 480)
camera.framerate = 30
rawCapture = PiRGBArray(camera, size=(720, 480))
#warmup the camera
time.sleep(1)
def msk_RED():
#create contours for RED Objects 
    contours,hierarchy = cv.findContours(R_Thresh,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
    for pic,contour in enumerate(contours):
        area1 = cv.contourArea(contour)
        #print(area1)
        if(area1 > 480):
            x,y,w,h = cv.boundingRect(contour)
            image = cv.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)
            Green = False
            if(Green == False):
                print("Kr")#Keep Right
                
                GPIO.output(16, 0)         # set GPIO24 to 1/GPIO.HIGH/True  
                
def msk_GREEN():
    #create contours for GREEN Objects
    contours,hierarchy = cv.findContours(G_Thresh,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
    for pic,contour in enumerate(contours):
        area = cv.contourArea(contour)
        #print(area)
        if(area>480):
            x,y,w,h = cv.boundingRect(contour)
            image = cv.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
            Green = True
            if(Green == True):
                print('Kl')#Keep Left
            
                GPIO.output(26, 0)         # set GPIO24 to 1/GPIO.HIGH/True  
                
while True:
    # capture frames from the camera
    for image in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        # grab the raw NumPy array representing the image, then initialize the timestamp
        # and occupied/unoccupied text
        frame = image.array
        hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
        #MASKS
        #Range of RED(HSV 0 255 255)
        up_r = np.array([178,255,255],np.uint8)#[180,255,255]
        low_r = np.array([158,100,100],np.uint8)#[136,87,111]
        mask_r = cv.inRange(hsv,low_r,up_r)
        #Gaussian Blur the Mask(RED)
        Red_blur = cv.GaussianBlur(mask_r,(51,51),0)
        #Threshold the blurred mask(GREEN)
        t,R_Thresh = cv.threshold(Red_blur,50,255,cv.THRESH_BINARY)

        #Range of GREEN(HSV 60 255 255)
        up_g = np.array([102,255,255],np.uint8)
        low_g = np.array([25,200,72],np.uint8)#[25,52,72]
        mask_g = cv.inRange(hsv,low_g,up_g)
        #Gaussian Blur the Mask(GREEN)
        Green_blur = cv.GaussianBlur(mask_g,(51,51),0)
        #Threshold the blurred mask(GREEN)
        g,G_Thresh = cv.threshold(Green_blur,50,255,cv.THRESH_BINARY)
        cv.imshow("Main",frame)
        cv.imshow("Green",G_Thresh)
        cv.imshow("Red",R_Thresh)
        cv.imshow("Mask Green",mask_g)
        cv.imshow("Mask Red",mask_r)
        h = cv.waitKey(5)
        if h == 53:
            break      
        # clear the stream in preparation for the next frame
        rawCapture.truncate(0)
        #Find any objects
        msk_GREEN()
        msk_RED()
    cv.destroyAllWindows()
    time.sleep(5)
'''
def calibrate():
    def nothing(x):
        pass
    cv.namedWindow("Trackbars")
     
    cv.createTrackbar("B", "Trackbars", 0, 255,nothing)
    cv.createTrackbar("G", "Trackbars", 0, 255,nothing)
    cv.createTrackbar("R", "Trackbars", 0, 255,nothing)

    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
            image = frame.array
            hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)

            B = cv.getTrackbarPos("B", "Trackbars")
            G = cv.getTrackbarPos("G", "Trackbars")
            R = cv.getTrackbarPos("R", "Trackbars")

            green = np.uint8([[[B, G, R]]])
            hsvGreen = cv.cvtColor(green,cv.COLOR_BGR2HSV)
            lowerLimit = np.uint8([hsvGreen[0][0][0]-10,100,100])
            upperLimit = np.uint8([hsvGreen[0][0][0]+10,255,255])

            mask = cv.inRange(hsv, lowerLimit, upperLimit)

            result = cv.bitwise_and(image  , image , mask=mask)

            cv.imshow("frame", image)
            cv.imshow("mask", mask)
            cv.imshow("result", result)

            key = cv.waitKey(1)
            rawCapture.truncate(0)
            if key == 27:
                    break
'''
