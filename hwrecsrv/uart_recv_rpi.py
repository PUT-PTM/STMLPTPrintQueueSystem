import serial

port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)

port.flushInput()
port.flushOutput()

rec = port.readline()
if rec == "HELLO STM\n":
    print("Connected with STM Board!")

while True:
    port.write("echo echo\n")
    rcv = port.readline()
    print(rcv)
