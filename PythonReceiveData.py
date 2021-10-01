import serial, time, math
import numpy as np
import matplotlib.pyplot as plt

def output2cart(input):
  """
  The purpose of this function is to convert angles and sensor output to
  cartesian coordinates.

  input: n by 3 array in order pan, tilt, and output
  
  Returns x,y,z in cm.
  """
  pan, tilt, output = input.T
  # These values were found with MATLAB's cf tool to translate output to actual
  # distance. They fit the exponential below.
  a = 1736 
  b = -0.8824
  distance = (output/a)**(1/b)
  # Spherical polar coordinates to cartesian coordinates
  x = distance * np.cos(np.radians(pan)) * np.sin(np.radians(180 - tilt))
  y = distance * np.sin(np.radians(pan)) * np.sin(np.radians(180 - tilt))
  z = distance * np.cos(np.radians(180 - tilt))
  return x,y,z

def plot(input):
  """
  Plots 3D scatter of points.

  input: 3 by n array in order x, y, and z
  """
  # Creating figure
  fig = plt.figure(figsize = (10, 7))
  ax = plt.axes(projection ="3d")
  
  # Creating plot
  ax.scatter3D(input[0], input[1], input[2])
  plt.title("simple 3D scatter plot")
  
  ax.set_xlabel('X axis (cm)')
  ax.set_ylabel('Y axis (cm)')
  ax.set_zlabel('Z axis (cm)')

  # show plot
  plt.show()

# ====== Setup Values ======
#name of serial port
arduinoComPort = "/dev/ttyACM0" # Change this if on Windows
baudRate = 9600 #baudrate
times_to_run = 5

line = "" 
data = np.array([[0,0,0]])    # array to store the data in
serialPort = serial.Serial(arduinoComPort, 9600)

time.sleep(2)

# Waits for "Begin" to start reading lines
while not serialPort.readline().decode().strip() == "Begin":
  print("Waiting To Begin")

# Continues to collect data until "End"
while not line == "End":
  # Checks that line follows three number format before recording
  if len(line.split(",")) > 2:
    pan_angle, tilt_angle, sensor_output = (int(x) for x in line.strip().split(","))  #converts the strings into integer
    print(pan_angle,tilt_angle,sensor_output)
    data = np.append(data, [[pan_angle,tilt_angle,sensor_output]], axis=0)
  line = serialPort.readline().decode().strip() # Get next line

# Remove row used to initialize data
data = np.delete(data,0,0)

print("End")
serialPort.close()

# Use functions above to visualize data
plot(output2cart(data))