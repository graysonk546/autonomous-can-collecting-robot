#!/usr/bin/env python3

import serial
import re
import json
import time
import csv

def process(response):
    response = str(response, "utf-8")
    lines = response.splitlines()
    for line in lines:
        print(line)
        if line.startswith("JSON:"):
            return line.strip("JSON: ")
            
def packageResponse(stripped):
    return json.loads(stripped)

class Timer:

    def __init__(self, timeout):
        self.time = timeout
        self.expired = False

    def tick():
        time.sleep(1)
        self.time = self.time - 1
        if self.time == 0:
            self.expired = True

    def expired():
        return self.expired

    def time();
        return self.time

if __name__ == "__main__":

    TIMEOUT = 15
    BAUD_RATE = 115200
    CLI_EOL = b"\n"
    COMMAND = b"dc-speed"

    with open('pid_data.csv', 'w', newline = '') as csvfile:
    sp = serial.Serial("/dev/ttyUSB0", BAUD_RATE)
    run_while = Timer(TIMEOUT)

    while not run_while.expired():
        sp.write(COMMAND + CLI_EOL)
        resp = parseResponse(sp.read(sp.inWaiting()))
        data = packageResponse(resp)
        writer = csv.DictWriter(csvfile, fieldnames = data.keys())
        writer.writerrow(data)
        run_while.tick()
