import serial

port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)

while True:
    rcv = port.read(10)
    print(rcv)
