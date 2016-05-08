import serial
import sys
import time
import string
import random

class UARTCommunicator:
    '''Communication logic between Raspberry Pi and STM32 microcontroller.'''
    def __init__(self):
        self.port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=5.0) # 5 secs only for debbuging purposes
        self.port.flushInput()
        self.port.flushOutput()
        
    def establishConnection(self):
        receivedLine = self.port.readline()
        receivedLine = receivedLine.rstrip()
        if receivedLine == "HELLO STM":
            self.port.write("HELLO PI\n")
            return True
        else:
            return False

    def dummyCommunication(self):
        while True:
            time.sleep(1)
            text = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(5))
            print("OUT: " + text)
            text += "\n"
            self.port.write(text)
            print("IN: " + self.port.readline().rstrip())
    
