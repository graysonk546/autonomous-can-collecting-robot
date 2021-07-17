
import serial
import re
import json

def parseResponse(response):
    pass

# start script
# wait for start command
# enter commands to read out importatnt perameters during driving
# wait for manually entered ending command

    

sp = serial.Serial("/dev/ttyUSB0", 115200)

sp.write(b"dc-speed")

value = sp.read(sp.inWaiting())

print(value)


