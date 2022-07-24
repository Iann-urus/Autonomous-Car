import cv2 as cv
import numpy as np
feed = cv.VideoCapture(0)
    
while feed.isOpened():
    rt,frame = feed.read()
    #resize the video
    scale_down =int((frame.shape[1]*50/100)),int((frame.shape[0]*50/100))
    frame = cv.resize(frame,scale_down,interpolation=cv.INTER_AREA)
    hsv = cv.cvtColor(frame,cv.COLOR_BGR2HSV)#change colour space
    '''
    Create masks for the colours RED & GREEN
    '''
    #Range of RED(HSV 0 255 255)
    up_r = np.array([180,255,255],np.uint8)
    low_r = np.array([136,87,111],np.uint8)
    mask_r = cv.inRange(hsv,low_r,up_r)
    #Range of GREEN(HSV 60 255 255)
    up_g = np.array([102,255,255],np.uint8)
    low_g = np.array([25,52,72],np.uint8)
    mask_g = cv.inRange(hsv,low_g,up_g)
    #create a kernel to dilate the frame
    kernel = np.ones((5,5),np.uint8)
    #join the mask and original frame
    mask_r = cv.dilate(mask_r,kernel)
    new_r = cv.bitwise_and(frame,frame,mask=mask_r)
    mask_g = cv.dilate(mask_g,kernel)
    new_g = cv.bitwise_and(frame,frame,mask=mask_g)
    #create contours for RED Objects 
    contours,hierarchy = cv.findContours(mask_r,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
    for pic,contour in enumerate(contours):
        area = cv.contourArea(contour)
        if(area > 300):
            x,y,w,h = cv.boundingRect(contour)
            frame = cv.rectangle(frame,(x,y),(x+w,y+h),(0,0,255),2)
    #create contours for GREEN Objects
    contours,hierarchy = cv.findContours(mask_g,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
    for pic,contour in enumerate(contours):
        area = cv.contourArea(contour)
        if(area>300):
            x,y,w,h = cv.boundingRect(contour)
            frame = cv.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
    cv.imshow("ObjectDetection",frame)
    h = cv.waitKey(5)
    if h == 53:
        break
feed.release()   
cv.destroyAllWindows()