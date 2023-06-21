import speech_recognition as sr
import os

if __name__ == "__main__":
    # while True:
    r = sr.Recognizer()
    
    with sr.Microphone() as source:
        r.adjust_for_ambient_noise(source)
        print('Please say')
        audio = r.listen(source)
        vice = 'error'
        try:
            vice = r.recognize_google(audio)
            print('you had said '+ vice)

        except Exception as e:
            print('error : ' + str(e))
        
    # command = 'say'
    os.system(f'say {vice}')
