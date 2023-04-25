# SOLARIS
The Submersible Oceanic Luminecent Analyzer of Reactive Intermediate Species is deep-sea chemical analyzer designed to measure reactive oxygen species (O<sup>2-</sup> & H<sub>2</sub>O<sub>2</sub>).

<table>
  <tr>
    <td>SOLARIS Pressure Testing</td>
     <td>System Schematic</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/220796370-8fd705e8-36ad-4265-8744-91ff943fbad6.jpeg" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/220803921-1aea62c2-e4da-48ba-9d18-7e5da49a30eb.jpg" width="425"></td>
  </tr>
</table>

## Hardware
SOLARIS is a complex assembly of mechanical electrical and fluidic components.

### Mechanical
The mechanical assembly of SOLARIS is broken into two sub-assemblies we reffer to as the analyzer assembly and the reagent assembly. 

#### Reagent Assembly
<table>
  <tr>
    <td>Reagent Assembly</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/220811167-8a5c0d3d-fa57-4d1d-abc4-ac9f06bc5743.jpg" width="425"></td>
    <td>The Reagent assembly</td>
  </tr>
</table>

#### Analyzer Assembly
<table>
  <tr>
     <td>Analyzer Assembly</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/220812175-405a97de-7c42-4121-8cdf-d5d6d8e77be0.jpg" width="425"></td>
    <td>The analyzer assembly is designed to be minipulated by a under water vehicle to be positioned near the area of interest to be analyzed.</td>
  </tr>
</table>
<table>
  <tr>
    <td>Flow Cell</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/232751656-f4d872fa-7657-4072-81d9-6cc6c155dd05.png" width="425"></td>
    <td>The Seawater sample and the chemiluminecent reagent mix within a spiral flow cell that is monitoured by a PMT</td>
  </tr>
</table>

### Electrical
<table>
  <tr>
    <td>Electronics Chassis</td>
    <td>Electronics Chassis Side</td>
    <td>Electronics Chassis Bottom</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/221905541-a28609d9-468d-432d-add3-6194d1183711.jpeg" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/221906765-5e6ef349-78a8-43af-8dff-a729d776e08b.jpeg" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/221905622-6b551655-f970-4499-a129-cb16d45f7079.jpeg" width="425"></td>
  </tr>
</table>


#### 23-0001-01 Custom Printed Circuit Board
<table>
  <tr>
    <td>Front PCB</td>
     <td>Bottom PCB</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/221744480-f4e89983-004e-480c-bb05-4f278c4421dd.png" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/221744126-222b4f41-e5ff-4b7d-b988-05a71c9bbba1.png" width="425"></td>
  </tr>
</table>



#### Motors & Controllers
The 7 pumps on SOLARIS are driven by motors and controled with [All Motion](https://www.allmotion.com/) [EZ10EN stepper motor driver](https://www.allmotion.com/ez10en). The 7 motor controllers share a parallel RS485 serial bus and are comunicated with a serial port on the 23-0001 controller through a [RS323 to RS485 converter](https://www.allmotion.com/rs485-ne).
#### Temperature Controller
The SOTs temperature control uses a Wavelength Electronics [RHM5K-CH termprature controller](https://www.teamwavelength.com/product/rhm5k-ch-5-a-unipolar-chassis-mt-temp-controller/) in combination with a resistive heater and thermistor. In order to maintain temperature stability we decided to remove the the integration capacitor.

#### Cables
[tubing](https://www.mcmaster.com/5549K55/) used with [MCPBOF](https://www.macartney.com/what-we-offer/systems-and-products/connectors/subconn/subconn-micro-circular-series/subconn-micro-circular-2-3-4-5-6-and-8-contacts-and-g2-2-3-and-4-contacts/)

### Fluidic 

#### Pump Heads
The [100CPT parastaltic pump heads](https://www.wmcpumps.com/100cpt-series-micro-peristaltic-pump) were purchased from Williamson Manufacturing Company and used with the [100 Series Tube Sets](https://www.wmcpumps.com/100200220-series-tube-sets)

#### [tubing](https://www.mcmaster.com/5384K515/)

## Software

### The Application

#### Start up page
#### Real-Time GUI
#### Autonomous Mission Planning

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
  
