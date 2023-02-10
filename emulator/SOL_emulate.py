import serial

SOLARIS = serial.Serial('COM1',9600)
SOLARIS.flushInput()



while True:
    SOLARIS.write()