# SOLARIS
The Submersible Oceanic Luminecent Analyzer of Reactive Intermediate Species is deep-sea chemical analyzer designed to measure reactive oxygen species (O<sup>2-</sup> & H<sup>2</sup>O<sup>2</sup>).

<table>
  <tr>
    <td>SOLARIS Enter Pressure Test</td>
     <td>System Schematic</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/220796370-8fd705e8-36ad-4265-8744-91ff943fbad6.jpeg" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/220803921-1aea62c2-e4da-48ba-9d18-7e5da49a30eb.jpg" width="425"></td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/220811167-8a5c0d3d-fa57-4d1d-abc4-ac9f06bc5743.jpg" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/220811171-995016dc-33bf-4cbe-8e7c-7e84269386b5.jpg" width="425"></td>
  </tr>
</table>



## Hardware

### Electrical

#### 23-0001-01_Rb Custom Printed Circuit Board

#### Motors & Controllers
[All Motion](https://www.allmotion.com/) [EZ10EN stepper motor driver](https://www.allmotion.com/ez10en) with a [RS323 to RS485 converter](https://www.allmotion.com/rs485-ne)

#### Temperature Controller

### Mechanical

## Software

### The Application

### Using the Emulator

Download & install the free serial port emulator (emulator\free-virtual-serial-port-tools.exe)
  Select creat local bridge & configure:
    First port name: COM1
    Secound port name: COM2
  Create - select "Creat non-permanent device" checkbox and then OK
Run the emulator
  '''python3 emulator.py'''
Open the app and use on COM2

### Firmware

#### 23_0001_01_Rb

#### Passthrough
  
