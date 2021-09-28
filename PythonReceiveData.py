import serial

#name of serial port
arduinoComPort = "COM4"

#baudrate
baudRate = 9600

# set up the serial line
ser = serial.Serial('COM4', 9600)
time.sleep(2)

#Send Arduino a Signal


# Read and record the data
data =[]                       # empty list to store the data
for i in range(100):
  line = serialPort.readline().decode()  # convert the byte string to a unicode string
  if len(line) > 0:
    a, b, c = (int(x) for x in line.split(','))  #converts the strings into integer
    print(a,b,c)
    data.append(a,b,c)     # add int to data lists

ser.close()

import matplotlib.pyplot as plt

plt.plot(data)
plt.xlabel('Angles')
plt.ylabel('Servo Reading')
plt.title('Servo Reading vs. Angle')
plt.show()










