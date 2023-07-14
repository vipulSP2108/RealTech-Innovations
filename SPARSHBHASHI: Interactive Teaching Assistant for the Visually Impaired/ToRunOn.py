import serial.tools.list_ports
import time
import os
import random
     
correct_greetings = [
    "Superb, that's the correct answer!",
    "Well done, you got the correct answer!",
    "Congratulations, that's the right answer!",
    "Great job, you got it right!",
    "Excellent work, you got the correct answer!",
    "Fantastic, that's the right answer!"
]

wrong_greetings = [
    "Oops, that's not the correct answer.",
    "Sorry, that's incorrect.",
    "Incorrect, try again.",
    "Not quite right, give it another shot.",
    "Wrong answer, keep trying.",
    "Unfortunately, that's not the correct response."
]

welcome_greetings = [
    "Welcome!",
    "Hello there!",
    "Greetings!",
    "Hi, and welcome!",
    "Nice to meet you!",
    "Hello and congratulations!",
    "Welcome aboard!",
    "Hi, there!",
    "Greetings and salutations!",
    "Hey, welcome!",
    "Hello, friend!",
    "Welcome to the team!",
    "Hi, newcomer!",
    "Nice to have you here!",
    "Hey, glad you're here!"
]

exit_greetings = [
    "Farewell! We hope you enjoyed your experience.",
    "Goodbye and thank you for being a part of our community.",
    "Wishing you the best as you move on. Goodbye!",
    "Farewell and safe travels on your future endeavors.",
    "Thank you for your time with us. Goodbye and take care!",
    "Signing off with gratitude. Goodbye and see you again soon!",
    "It's been a pleasure having you here. Goodbye and stay awesome!",
    "Saying goodbye with a smile. Thank you and farewell!",
    "Wishing you all the best as you venture forward. Goodbye!",
    "Thank you for being a valued member. Farewell and until we meet again!"
]

ports = serial.tools.list_ports.comports()
serialinst = serial.Serial()

for onePort in ports:
    print(str(onePort))

# portVal = input('Enter the working port (e.g., "/dev/cu.usbmodem1101"): ')
# print(portVal)

serialinst.baudrate = 9600
serialinst.port = '/dev/cu.usbmodem1101'

def randomx(x):
    random_greeting = random.choice(x)
    return random_greeting

try:
    serialinst.open()
    time.sleep(2)  # Delay to allow the Arduino to initializ
    os.system(f'say {randomx(welcome_greetings)} on your spersh bhhaashi')
    
    while True:
        # print(1)
        if serialinst.in_waiting:
            data = serialinst.readline().decode().strip()
            print(data)
            
            if (data == "backword"):
                # random_greeting = random.choice(backword)
                os.system(f'say Lets move on to the next letter,')

            elif (data == "forword"): 
                # random_greeting = random.choice(forword)
                os.system(f'say Lets move on to the next letter,')
           
            elif (data == "train"): 
                random_greeting = random.choice(exit_greetings)
                os.system(f'say alfabet train mode activated')

            elif (data == "test"):
                os.system(f'say Now alfabet Test is starting. If the letter presented in Braille matches the heard letter, press the right side button; otherwise, press the left side button')

            elif (data == "correct_greetings"):
                random_greeting = random.choice(correct_greetings)
                os.system(f'say {random_greeting}')

            elif (data == "wrong_greetings"):
                random_greeting = random.choice(wrong_greetings)
                os.system(f'say {random_greeting}')

            elif (data == "end"):
                random_greeting = random.choice(exit_greetings)
                os.system(f'say {random_greeting}')
                break

            else:
                os.system(f'say This Letter is, {data}')

except Exception as e:
    print("An error occurred:", str(e))

finally:
    serialinst.close()
