import serial
import pygame


ser = serial.Serial('/dev/ttyUSB0', 9600)

pygame.mixer.pre_init(44100, -16, 2, 512)
pygame.mixer.init()
pygame.init()
drum_sound=pygame.mixer.Sound('Hihat_new_wav.wav')
  
while True:
        inp = int(ser.readline())
	
        if inp<18:
            print(inp)
            drum_sound.set_volume(.1)
            drum_sound.play()
        elif inp<25:
            print(inp)
            drum_sound.set_volume(.3)
            drum_sound.play()                
        elif inp<40:
            print(inp)
            drum_sound.set_volume(.6)
            drum_sound.play()
        elif inp<50:
            print(inp)
            drum_sound.set_volume(.8)
            drum_sound.play()            
        elif inp>49:
            print(inp)
            drum_sound.set_volume(1)
            drum_sound.play()
