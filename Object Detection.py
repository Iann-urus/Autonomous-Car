'''
The following program detects Green objects and masks them 
The video file is used as an example
'''
import cv2
import numpy as np
feed = cv2.VideoCapture('path for video')#paste video path (change // to \\)
while feed.isOpened():

    rt,frame = feed.read()
    '''
    #COnvert RGB To HSV
    colour = np.uint8([[[0,255,0]]])
    hsv = cv2.cvtColor(colour,cv2.COLOR_RGB2HSV)
    print(hsv)
    '''
    #Green in HSV == ([60,255,255])
    lower = np.array([20,10,10])#lower bound for green in HSV
    upper = np.array([70,255,255])#upper boung in HSV
    mask = cv2.inRange(frame, lower,upper)
  
    cv2.imshow('Normal',frame)
    cv2.imshow('Mask',mask)
    #cv2.imshow('Color',feed2)
    
    h = cv2.waitKey(5)
    if h == '53':
        break
feed.release()   
cv2.destroyAllWindows()
