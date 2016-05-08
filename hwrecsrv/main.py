import uartcomm
import sys

def main():
    uart = uartcomm.UARTCommunicator()
    if uart.establishConnection():
        print("Connected with STM board!")
        uart.dummyCommunication()
    else:
        print("An error occured during establishing connection!")
        return 1

    return 0

if __name__ == "__main__":
    sys.exit(main())
