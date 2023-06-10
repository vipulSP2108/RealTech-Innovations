import RPi.GPIO as GPIO
from time import sleep
from gpiozero import Servo
from random import randint

fbPin = 2
bbPin = 3
testPin = 4
test = 0

servo1Angle = 0
servo2Angle = 0
servo3Angle = 0
servo4Angle = 0
servo5Angle = 0
servo6Angle = 0
i = 0
oldi = 0

# Initialize Servo Objects
servo1 = Servo(5)
servo2 = Servo(6)
servo3 = Servo(7)
servo4 = Servo(8)
servo5 = Servo(9)
servo6 = Servo(10)

# Configure GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(fbPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(bbPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(12, GPIO.OUT)
GPIO.setup(testPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(11, GPIO.OUT)

englishalpha = [['A'], ['B'], ['C']]
english = [[0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 90], [0, 0, 0, 0, 90, 90]]

def speak_next():
    # Function to speak the next character
    pass  # Replace this with your code to speak the character

def train_mode():
    global i, oldi, servo1Angle, servo2Angle, servo3Angle, servo4Angle, servo5Angle, servo6Angle
    
    if GPIO.input(fbPin) == GPIO.HIGH:
        GPIO.output(13, GPIO.HIGH)
        i += 1
        sleep(1)
        speak_next()
    else:
        GPIO.output(13, GPIO.LOW)
    
    if GPIO.input(bbPin) == GPIO.HIGH:
        i -= 1
        GPIO.output(12, GPIO.HIGH)
        sleep(1)
        speak_next()
    else:
        GPIO.output(12, GPIO.LOW)
    
    if GPIO.input(testPin) == GPIO.HIGH:
        global test
        if test == 1:
            test = 0
            GPIO.output(11, GPIO.HIGH)
        else:
            test = 1
            GPIO.output(11, GPIO.LOW)
        sleep(1)
        speak_next()
    
    if test == 0:
        servo1Angle = english[i][0]
        servo2Angle = english[i][1]
        servo3Angle = english[i][2]
        servo4Angle = english[i][3]
        servo5Angle = english[i][4]
        servo6Angle = english[i][5]
    else:
        i = randint(0, 9)
        print(i)
        sleep(1)
    
    print(servo6Angle)
    
    if oldi != i:
        servo1.value = servo1Angle
        servo2.value = servo2Angle
        servo3.value = servo3Angle
        servo4.value = servo4Angle
        servo5.value = servo5Angle
        servo6.value = servo6Angle

# Main Program
GPIO.cleanup()
GPIO.setmode(GPIO.BCM)

GPIO.add_event_detect(fbPin, GPIO.RISING, callback=train_mode, bouncetime=200)
GPIO.add_event_detect(bbPin, GPIO.RISING, callback=train_mode, bouncetime=200)
GPIO.add_event_detect(testPin, GPIO.RISING, callback=train_mode, bouncetime=200)

try:
    while True:
        sleep(0.1)

except KeyboardInterrupt:
    GPIO.cleanup()
