
import serial

sp = serial.Serial("/dev/ttyUSB0", 115200)

value = sp.read(sp.inWaiting())


