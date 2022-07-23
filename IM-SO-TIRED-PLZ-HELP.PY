import cv2 as cv
import numpy as np

cap = cv.VideoCapture(0)
# cap2 = cv.VideoCapture(1)

while True:
    ret, frame = cap.read()
    ret2, frame2 = cap.read()

    if ret == False or ret2 == False:
        break

    # width = int(cap.get(3))
    # height = int(cap.get(4))

    # img = cv.line(frame, (0,0), (width, height), (255, 0, 0), 10)
    # img2 = cv.line(img, (0,height), (width, 0), (0, 255, 0), 5)
    # img3 = cv.rectangle(img2, (100,100), (200,200), (128, 128, 128), 5)
    # img4 = cv.circle(img3, (300,300), 60, (0, 0, 255), -1)

    # font = cv.FONT_HERSHEY_SIMPLEX
    # img5 = cv.putText(img3, "L-CHAMP", (100, height - 10), font, 1,  (0, 0, 0), 5, cv.LINE_AA)

    hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    hsv2 = cv.cvtColor(frame2, cv.COLOR_BGR2HSV)
    lower_blue = np.array([20,10,10])
    upper_blue = np.array([70,255,255])

    lower_blue1 = np.array([90, 50, 50])
    upper_blue1 = np.array([130, 255, 255])

    mask = cv.inRange(hsv, lower_blue, upper_blue)
    mask2 = cv.inRange(hsv2, lower_blue1, upper_blue1)
    # result = cv.bitwise_and(frame, frame, mask=mask)
    # result2 = cv.bitwise_and(frame2, frame2, mask=mask2)

    result = cv.resize(mask, (240, 320))
    result2 = cv.resize(mask2, (240, 320))
    dst = cv.addWeighted(mask,0.3,mask2,0.7,0)

    cv.imshow("POG", dst)

    if cv.waitKey(1) == ord('z'):
        break

cap.release()
cv.destroyAllWindows()
