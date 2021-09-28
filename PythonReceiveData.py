import serial, time, math
import numpy as np

def cosd(num):
  return math.cos(math.radians(num))


def sind(num):
  return math.sin(math.radians(num))

def output2cart(input):
  pan, tilt, output = input
  a = 1736 
  b = -0.8824
  distance = (output/a)**(1/b)
  x = distance * cosd(pan) * sind(tilt)
  y = distance * sind(pan) * sind(tilt)
  z = distance * cosd(tilt)
  return x,y,z


#name of serial port
arduinoComPort = "/dev/ttyACM0"

#baudrate
baudRate = 9600

# set up the serial line
serialPort = serial.Serial(arduinoComPort, 9600)
time.sleep(2)

#Send Arduino a Signal
pan_angles = (180 - 0)/5
tilt_angles = (180 - 0)/5

# Read and record the data
data = np.array([[0,0,0]])                    # empty list to store the data


line = ""               # stores serial output
while not serialPort.readline().decode().strip() == "Begin":
  print("waiting to begin")

while not serialPort.readline().decode().strip() == "End":
  line = serialPort.readline().decode() # convert the byte string to a unicode string
  while len(line.split(",")) < 3:
    line = serialPort.readline().decode() # convert the byte string to a unicode string
  pan_angle, tilt_angle, sensor_output = (int(x) for x in line.strip().split(","))  #converts the strings into integer
  print(pan_angle,tilt_angle,sensor_output)
  data = np.append(data, [[pan_angle,tilt_angle,sensor_output]], axis=0)

print("end")
serialPort.close()

data = np.delete(data, 0, 0)

data_cart = np.array([output2cart(datapoint) for datapoint in data])

print(data_cart)

import matplotlib.pyplot as plt

plt.plot(data)
plt.xlabel('Angles')
plt.ylabel('Servo Reading')
plt.title('Servo Reading vs. Angle')
plt.show()