


import scipy.interpolate
import numpy as np

import tkinter as tk
from tkinter.filedialog import askopenfilename
tk.Tk().withdraw() # part of the import if you are not using other tkinter functions

import serial

y = [31.770,30.250,28.820,27.450,26.160,24.940,23.770,22.670,21.620,
     20.630,19.680,18.780,17.930,17.120,16.350,15.620,14.930,14.260,
     13.630,13.040,12.470,11.920,11.410,10.910,10.450,10.000,9.57500,
     9.170,8.784,8.416,8.064,7.730,7.410,7.106,6.815,6.538,6.273,6.020,
     5.778,5.548,5.327];
x = np.linspace(0,40,41)
y_interp = scipy.interpolate.interp1d(x, y)

fn = askopenfilename()
print("user chose", fn)

file = open(fn,'r')
lines = file.readlines()

##SOLARIS = serial.Serial('COM1',9600)
##SOLARIS.flushInput()

count =0
for line in lines:
    count += 1
    data = line.strip()
    print("Line {}: {}".format(count, data))
    data = data.split(',')
    print(data[2])

    

    print(y_interp(float(data[2])/10))
##while True:
##    SOLARIS.write()

