import cv2 as cv

cap = cv.VideoCapture(0)
# cap.set(cv.CAP_PROP_FRAME_WIDTH, 1280)
# cap.set(cv.CAP_PROP_FRAME_HEIGHT, 720)  

while True:
    ret, frame = cap.read()
    hsv_frame = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
    width = int(cap.get(3))
    height = int(cap.get(4))

    # height, width, _ = frame.shape

    cx = int(width / 2)
    cy = int(height / 2)

    pixel_center = hsv_frame[cy, cx]
    hue_value = pixel_center[0]
    saturation_value = pixel_center[1]
    brightness_value = pixel_center[2]

    color = "UNDEFINED"
    if hue_value < 5 :
    # and 94 < brightness_value < 256:
        color = "RED"
    # elif hue_value < 16:
    #     color = "ORANGE"
    # elif hue_value < 33:
    #     color = "YELLOW"
    elif 33 < hue_value < 79   and 44 < brightness_value < 256:
        color = "GREEN"
    # elif hue_value < 131:
    #     color = "BLUE"
    # elif hue_value < 147:
    #     color = "VIOLET"
    # elif hue_value < 170:
    #     color = "PINK"
    else:
        color = "WHITE"

    
    cv.putText(frame, color, (10, 50), 0, 1, (255, 0, 0), 2)
    cv.circle(frame, (cx, cy), 10, (255, 0, 0), 3)


    cv.imshow("AMONGUS", frame)
    if cv.waitKey(1) == ord('z'):
        break

cap.release()
cv.destroyAllWindows()
