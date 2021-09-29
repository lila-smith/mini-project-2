import serial, time, math
import numpy as np

def output2cart(input):
  pan, tilt, output = input.T
  a = 1736 
  b = -0.8824
  distance = (output/a)**(1/b)
  x = distance * np.cos(np.radians(pan)) * np.sin(np.radians(tilt))
  y = distance * np.cos(np.radians(pan)) * np.sin(np.radians(tilt))
  z = distance * np.cos(np.radians(tilt))
  return x,y,z

#name of serial port
arduinoComPort = "/dev/ttyACM0" # Change this if on Windows

#baudrate
baudRate = 9600

# set up the serial line
serialPort = serial.Serial(arduinoComPort, 9600)
time.sleep(2)

# Read and record the data
data = np.array([[0,0,0]])                    # empty list to store the data

while not serialPort.readline().decode().strip() == "Begin":
  print("waiting to begin")

while not serialPort.readline().decode().strip() == "End":
  line = serialPort.readline().decode() # convert the byte string to a unicode string
  while len(line.split(",")) < 3:
    line = serialPort.readline().decode() # convert the byte string to a unicode string
  print(line)
  pan_angle, tilt_angle, sensor_output = (int(x) for x in line.strip().split(","))  #converts the strings into integer
  print(pan_angle,tilt_angle,sensor_output)
  data = np.append(data, [[pan_angle,tilt_angle,sensor_output]], axis=0)

print("end")
serialPort.close()

data = np.delete(data, 0, 0)

x,y,z = output2cart(data)

print(x,y,z)

import matplotlib.pyplot as plt

# Creating figure
fig = plt.figure(figsize = (10, 7))
ax = plt.axes(projection ="3d")
 
# Creating plot
ax.scatter3D(x, y, z, color = "green")
plt.title("simple 3D scatter plot")
 
# show plot
plt.show()