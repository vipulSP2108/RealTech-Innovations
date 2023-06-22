import RPi.GPIO as GPIO
import time
from time import sleep
# from gpiozero import Servo
import random
import os

fbPin = 2
bbPin = 3
# testPin = 4
# test = 0

motor1 = 0
motor2 = 0
motor3 = 0
motor4 = 0
motor5 = 0
motor6 = 0

i = 0
oldi = 0

# led1 = 4
# led2 = 5
# led3 = 6
# led4 = 7

wordpin = 9
alfapin = 10
testpin = 11
trainpin = 12

GPIO.setmode(GPIO.BCM)
# GPIO.setup(led1, GPIO.OUT)
# GPIO.setup(led2, GPIO.OUT)
# GPIO.setup(led3, GPIO.OUT)
# GPIO.setup(led4, GPIO.OUT)

GPIO.setup(wordpin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(alfapin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(testpin, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(trainpin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

GPIO.setmode(GPIO.BCM)
GPIO.setup(fbPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(13, GPIO.OUT) #LED
GPIO.setup(bbPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(12, GPIO.OUT) #LED
GPIO.setup(testPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(11, GPIO.OUT) #LED

GPIO.setup(5, GPIO.OUT)
pwm1 = GPIO.PWM(5, 50)
GPIO.setup(6, GPIO.OUT)
pwm2 = GPIO.PWM(6, 50)
GPIO.setup(7, GPIO.OUT)
pwm3 = GPIO.PWM(7, 50)
GPIO.setup(8, GPIO.OUT)
pwm4 = GPIO.PWM(8, 50)
GPIO.setup(9, GPIO.OUT)
pwm5 = GPIO.PWM(9, 50)
GPIO.setup(10, GPIO.OUT)
pwm6 = GPIO.PWM(10, 50)
# GPIO.setup(11, GPIO.OUT)

englishalpha = [['A']]
english = [[90,0,0,0,0,0]]

# servo
def rotate_servo(angle):
    duty_cycle = (angle / 18) + 2
    return duty_cycle

# speak
def speak(spk):
    command = 'say'
    os.system(f'{command} {spk}')

# train_mode
def train_mode():
    global i, englishalpha
    
    if GPIO.input(fbPin) == GPIO.HIGH:
        GPIO.output(13, GPIO.HIGH)
        i += 1
        sleep(1)
        speak(f'next alphabet is {englishalpha[i]}')
    else:
        GPIO.output(13, GPIO.LOW)
    
    if GPIO.input(bbPin) == GPIO.HIGH:
        i -= 1
        GPIO.output(12, GPIO.HIGH)
        sleep(1)
        speak(f'previous alphabet is {englishalpha[i]}')
    else:
        GPIO.output(12, GPIO.LOW)
    
    return i

# test_mode
def test_mode():
    global englishalpha
    rand = random.randint(26)
    addsub = random.randint(26)
    listx = [rand, rand+addsub, rand-addsub]
    alpfaspeak = random(listx)
    alpfashow = random(listx)
    speak(f'Identify the correct alphabet, is it {englishalpha[alpfaspeak]}')
    return alpfashow, alpfaspeak

try:
    f = open('output1.txt', 'r')
    i = f.readline()
    f.close()
  
    t = time.time()

    while True:
        word = GPIO.input(wordpin)
        alfa = GPIO.input(alfapin)
        GPIO.setmode(GPIO.BCM)
        GPIO.setmode(GPIO.BOARD)

        if word == GPIO.LOW:
            # GPIO.output(led1, GPIO.HIGH)
            word = 1
            alfa = 0
        # else:
            # GPIO.output(led1, GPIO.LOW)
            # alfa = 1
            # word = 0

        if alfa == GPIO.LOW:
            # GPIO.output(led2, GPIO.HIGH)
            alfa = 1
            word = 0
        # else:
            # GPIO.output(led2, GPIO.LOW)

        test = GPIO.input(testpin)
        train = GPIO.input(trainpin)

        if test == GPIO.LOW:
            # GPIO.output(led3, GPIO.HIGH)
            test = 1
            train = 0
        # else:
            # GPIO.output(led3, GPIO.LOW)
            # test = 0
            # train = 1
        if train == GPIO.LOW:
            test = 0
            train = 1
            # GPIO.output(led4, GPIO.HIGH)
            # train
        # else:
            # GPIO.output(led4, GPIO.LOW)

except KeyboardInterrupt:
    GPIO.cleanup()
