import RPi.GPIO as GPIO
import time
from time import sleep
# from gpiozero import Servo
import random
import os

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

# servo1 = Servo(5)
# servo2 = Servo(6)
# servo3 = Servo(7)
# servo4 = Servo(8)
# servo5 = Servo(9)
# servo6 = Servo(10)

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

# main
try:
  f = open('output1.txt', 'r')
  i = f.readline()
  f.close()
  
  t = time.time()
  
  while True:
    GPIO.setmode(GPIO.BCM)
    GPIO.setmode(GPIO.BOARD)
    
    if GPIO.input(testPin) == GPIO.HIGH:
      if test == 1:
        test = 0
        GPIO.output(11, GPIO.LOW) # train mode on light off
        speak('train mode activated')
      else:
        test = 1
        GPIO.output(11, GPIO.HIGH) # test mode on light on
        speak('test mode activated')
        testcount = 0
        t = 0
      sleep(1)

    # train mode
    if test == 0: 
      if t%10 == 0:
        speak(f'your current alphabet is {englishalpha[i]}')
      oldi = i
      rota = train_mode()

    # test mode
    if test == 1:
      if testcount == 0:
        alpfashow, alpfaspeak = test_mode()
        oldi = alpfashow
        rota = alpfashow
        testcount += 1
      else:
        if GPIO.input(fbPin) == GPIO.HIGH or GPIO.input(bbPin) == GPIO.HIGH:
          if (alpfashow == alpfaspeak and GPIO.input(fbPin) == GPIO.HIGH) or (alpfashow != alpfaspeak and GPIO.input(bbPin) == GPIO.HIGH): 
            speak('Congrats')
          speak(f'correct alphabet is {englishalpha[alpfashow]}')
          oldi = alpfashow
          alpfashow, alpfaspeak = test_mode()
      
      # after every 10 sec voice comes
      if t%10 == 0:
        speak(f'Identify the correct alphabet, is it {englishalpha[alpfaspeak]}')
        
    if oldi != rota:
      # aagaar plain motor to iske bad all band the chalu
      servo1Angle = english[rota][0]
      servo2Angle = english[rota][1]
      servo3Angle = english[rota][2]
      servo4Angle = english[rota][3]
      servo5Angle = english[rota][4]
      servo6Angle = english[rota][5]
    
      duty_cycle = rotate_servo(servo1Angle)
      pwm1.ChangeDutyCycle(duty_cycle)
      duty_cycle = rotate_servo(servo2Angle)
      pwm2.ChangeDutyCycle(duty_cycle)
      duty_cycle = rotate_servo(servo3Angle)
      pwm3.ChangeDutyCycle(duty_cycle)
      duty_cycle = rotate_servo(servo4Angle)
      pwm4.ChangeDutyCycle(duty_cycle)
      duty_cycle = rotate_servo(servo5Angle)
      pwm5.ChangeDutyCycle(duty_cycle)
      duty_cycle = rotate_servo(servo6Angle)
      pwm6.ChangeDutyCycle(duty_cycle)
      
    f = open('output1.txt','w')
    f.write('{}'.format(i))
    f.close()

except KeyboardInterrupt:
  GPIO.cleanup()


# GPIO.add_event_detect(fbPin, GPIO.RISING, callback=train_mode, bouncetime=200)
# GPIO.add_event_detect(bbPin, GPIO.RISING, callback=train_mode, bouncetime=200)
# GPIO.add_event_detect(testPin, GPIO.RISING, callback=train_mode, bouncetime=200)
