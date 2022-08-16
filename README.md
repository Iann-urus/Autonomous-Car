# Autonomous-Car
#dependancies
import time
import cv2 as cv
import numpy as np
import keyboard as kd
from picamera.array import PiRGBArray
from picamera import PiCamera

# initialize the camera and grab a reference to the raw camera capture
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))
#warmup the camera
time.sleep(0.5)
#Create a function to capture video by iterating through each frame
def take_video():
    # capture frames from the camera
    for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        # grab the raw NumPy array representing the image, then initialize the timestamp
        # and occupied/unoccupied text
        image = frame.array
        # show the frame
        cv.imshow("Frame", image)
        key = cv.waitKey(1) & 0xFF
        # clear the stream in preparation for the next frame
        rawCapture.truncate(0)
while kd.is_pressed('q') == False:
    take_video()
    print(image)






