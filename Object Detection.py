import cv2
import numpy as np
feed = cv2.VideoCapture('C:/Users/waigu/OneDrive/Desktop/ToDo/Autonomous car/green_ball.mp4')
while feed.isOpened():

    rt,frame = feed.read()
    '''
    #COnvert RGB To HSV
    colour = np.uint8([[[0,255,0]]])
    hsv = cv2.cvtColor(colour,cv2.COLOR_RGB2HSV)
    print(hsv)
    '''

    lower = np.array([20,10,10])
    upper = np.array([70,255,255])
    mask = cv2.inRange(frame, lower,upper)
    #feed2 = cv2.bitwise_and(frame,frame,mask=mask)
    cv2.imshow('Normal',frame)
    cv2.imshow('Mask',mask)
    #cv2.imshow('Color',feed2)
    
    h = cv2.waitKey(5)
    if h == '53':
        break
feed.release()   
cv2.destroyAllWindows()
