import serial, time, math
import numpy as np
import matplotlib.pyplot as plt

def output2cart(input):
  pan, tilt, output = input.T
  a = 1736 
  b = -0.8824
  distance = (output/a)**(1/b)
  x = distance * np.sin(np.radians(pan)) * np.cos(np.radians(tilt))
  y = distance * np.sin(np.radians(pan)) * np.sin(np.radians(tilt))
  z = distance * np.cos(np.radians(tilt))
  return x,y,z

def plot(input):
  # Creating figure
  fig = plt.figure(figsize = (10, 7))
  ax = plt.axes(projection ="3d")
  
  # Creating plot
  ax.scatter3D(input[0], input[1], input[2], color = "green")
  plt.title("simple 3D scatter plot")
  
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
  # Checks that line follows three number format
  if len(line.split(",")) > 2:
    pan_angle, tilt_angle, sensor_output = (int(x) for x in line.strip().split(","))  #converts the strings into integer
    print(pan_angle,tilt_angle,sensor_output)
    data = np.append(data, [[pan_angle,tilt_angle,sensor_output]], axis=0)
  line = serialPort.readline().decode().strip() # Get next line 

print("End")
serialPort.close()

plot(output2cart(data))