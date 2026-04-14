import serial
import csv
import time

ser = serial.Serial('/dev/ttyUSB0',9600,timeout=1)

file = open("rolex_log.csv","w",newline='')
writer = csv.writer(file)

writer.writerow([
    "time","temperature","gas","distance",
    "motion_front","motion_back","cliff"
])

print("Logging started...")

while True:

    line = ser.readline().decode().strip()

    if line.startswith("DATA"):

        parts = line.split(",")

        writer.writerow([
            time.time(),
            parts[1],
            parts[2],
            parts[3],
            parts[4],
            parts[5],
            parts[6]
        ])

        file.flush()
        print(parts)
