try:
    f = open('output1.txt', 'r')
    i = f.readline()
    f.close()
  
    t = time.time()

    wordspk = 0
    alfaspk = 0
    testspk = 0
    trainspk = 0
    alfatrainspk = 0
    testcount = 0

    while True:
        GPIO.setmode(GPIO.BCM)
        GPIO.setmode(GPIO.BOARD)

        # PHASE 1
        word = GPIO.input(wordpin) # slider button code (word and alfabet)
        alfa = GPIO.input(alfapin)

        if word == GPIO.LOW:
            if wordspk == 0: # only speak 1st change
                speak('word mode activated')
                alfaspk = 0
                wordspk = 1
            word = 1
            alfa = 0

        if alfa == GPIO.LOW:
            if alfaspk == 0: # only speak 1st change
                speak('alfabet mode activated')
                wordspk = 0
                alfaspk = 1
            alfa = 1
            word = 0

        test = GPIO.input(testpin) # slider button code (train and test)
        train = GPIO.input(trainpin)

        if test == GPIO.LOW:
            if testspk == 0: # only speak 1st change
                speak('test mode activated')
                trainspk = 0
                testspk = 1
            test = 1
            train = 0

        if train == GPIO.LOW:
            if trainspk == 0: # only speak 1st change
                speak('train mode activated')
                testspk = 0
                trainspk = 1
            test = 0
            train = 1
        
        # PHASE 2
        if alfa == 1 and train == 1: # /////////////////// alfabet train mode
            testcount = 0
            if t > 10 or alfatrainspk == 0: # after every 10 sec voice comes or 1st change
                speak(f'your current alphabet is {englishalpha[i]}')
                t = 0
                alfatrainspk = 1
            oldi = i
            rota = alfatrain_mode()
            
            f = open('output1.txt','w') # store current alfabet
            f.write('{}'.format(rota))
            f.close()

        elif alfa == 1 and test == 1: # /////////////////// alfabet test mode
            alfatrainspk = 0
            if testcount == 0: # this is added to stop changing alfa value every sec
                alpfashow, alpfaspeak = alfatest_mode()
                # oldi = alpfashow
                rota = alpfashow
                testcount = 1
            else:
                if GPIO.input(fbPin) == GPIO.HIGH or GPIO.input(bbPin) == GPIO.HIGH:
                    if (alpfashow == alpfaspeak and GPIO.input(fbPin) == GPIO.HIGH) or (alpfashow != alpfaspeak and GPIO.input(bbPin) == GPIO.HIGH): 
                        speak('Congrats')
                        speak(f'correct alphabet is {englishalpha[alpfashow]}')
                        # oldi = alpfashow
                    else :
                        speak('Sorry')
                        speak(f'correct alphabet is {englishalpha[alpfashow]}')
                        # alpfashow, alpfaspeak = alfatest_mode()
                testcount = 0

            if t > 10: # after every 10 sec voice comes or 1st change
                speak(f'Identify the correct alphabet, is it {englishalpha[alpfaspeak]}')
                t = 0

        # elif word == 1 and train == 1: # /////////////////// word train mode

        # elif word == 1 and train == 1: # /////////////////// word test mode

        if oldi != rota:
            servo1Angle = english[rota][0]
            servo2Angle = english[rota][1]
            servo3Angle = english[rota][2]
            servo4Angle = english[rota][3]
            servo5Angle = english[rota][4]
            servo6Angle = english[rota][5]

except KeyboardInterrupt:
    GPIO.cleanup()
