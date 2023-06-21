import serial
import RPi.GPIO as GPIO
import time

LED_PIN = 12
DELAY_TIME = 1

wordinputed = ""

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)

ser = serial.Serial('/dev/ttyACM0', 9600)  # Replace '/dev/ttyACM0' with your serial port

while True:
    while ser.inWaiting() == 0:
        pass
    
    wordinputed = ser.readline().decode().strip()
    print(wordinputed)

    if wordinputed == "ASA":
        GPIO.output(LED_PIN, GPIO.HIGH)
        time.sleep(5)
        GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(1)

ser.close()
GPIO.cleanup()
