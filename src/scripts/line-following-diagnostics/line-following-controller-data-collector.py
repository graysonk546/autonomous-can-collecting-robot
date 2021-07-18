import serial
from threading import Thread
import json
from datetime import datetime
from time import sleep

running = True

def collect_data():

    SERIAL_PORT = '/dev/ttyUSB0'
    TIMEOUT = 15
    BAUD_RATE = 115200
    POLL_FREQUENCY = 2  # Hz
    POLL_PERIOD = 1 / POLL_FREQUENCY  # seconds
    CLI_EOL = b'\n'
    COMMAND = b'poll-line-following-controller'

    file_path = 'data/line-following-controller-data-' + \
                    datetime.now().strftime("%d-%m-%Y-%H.%M.%S") + '.json'

    output_data = []

    with open(file_path, 'w') as outputFile:
        sp = serial.Serial(SERIAL_PORT, BAUD_RATE)
        while (running):
            sp.write(COMMAND + CLI_EOL)
            resp = parse_response(sp.read(sp.inWaiting()))
            if (not(resp is None)):
                data = json.loads(resp)
                print(data)
                output_data.append(data)
            sleep(POLL_PERIOD)
        
        print(output_data)
        outputFile.write(json.dumps(output_data, indent=4))
    
    print('Data successfully saved to \"' + file_path + '\"')

def parse_response(response):

    response = str(response, "utf-8")
    lines = response.splitlines()
    for line in lines:
        if line.startswith("JSON:"):
            return line.strip("JSON: ")

def check_to_terminate():

    global running
    input('Press ENTER to stop serial data collection and save: ')
    running = False

if __name__ == "__main__":
    
    PROGRAM_NAME = 'LINE FOLLOWING CONTROLLER SERIAL DATA COLLECTOR'

    print(PROGRAM_NAME)
    print('='*len(PROGRAM_NAME))

    input('Press ENTER to begin serial data collection: ')

    collector_thread = Thread(target=collect_data)
    collector_thread.start()
    user_input_thread = Thread(target=check_to_terminate)
    user_input_thread.start()

    collector_thread.join()
    user_input_thread.join()