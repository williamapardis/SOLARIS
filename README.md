# SOLARIS
The Submersible Oceanic Luminecent Analyzer of Reactive Intermediate Species (SOLARIS) is a developmental instrument designed to make measurements in the ocean of a fleetingly scarce compound called superoxide(O<sup>2-</sup>), a reactive oxygen species(ROS) and made the first measurements of this chemical in the deep sea. SOLARIS utilizes the properties of chemiluminescence, a chemical reaction that produces light. Analysis involves mixing a chemical reagent with the seawater to be analyzed, after which a reaction occurs and produces light proportional to the level of superoxide. Measuring this light with a highly sensitive optical detector, a photon counting photomultiplier tube(PMT), we can very precisely determine how much superoxide is in the environment. Peristaltic pumps dispense reagents and seawater, which are encased in housings filled with (incompressible) oil to protect them from the corrosive environment. Electronics are encased in hermetically sealed pressure vessels held at atmospheric pressure  to protect them from both the seawater and hydrostatic pressure, allowing operation to depths of up to 4500 meters, corresponding to pressures of greater than 400 atmospheres.
SOALRIS has also been adapted to measure hydrogen peroxide (H<sub>2</sub>O<sub>2</sub>) and made some of the first ever measurments of this ROS species in the deep sea.
<p align="center"></p>
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
<p></p>

## Hardware
SOLARIS is a complex assembly of mechanical electrical and fluidic components.

### Mechanical
The mechanical assembly of SOLARIS is broken into two sub-assemblies we reffer to as the Analyzer Assembly and the Reagent Assembly. 

#### Analyzer Assembly
The analyzer assembly is designed to be minipulated by a under water vehicle to be positioned near the area of interest to be analyzed.
<table>
  <tr>
    <td>Drawing</td>
    <td>On Deck</td>
    <td>In Water</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/235912806-09846072-f4d4-4bf0-9a48-110488b5ab2b.png" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/235913738-1f5c2f63-d759-43f2-9447-79da88a62b7f.jpg" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/221905622-6b551655-f970-4499-a129-cb16d45f7079.jpeg" width="425"></td>
  </tr>
</table>
<table>
  <tr>
    <td>Flow Cell</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/232751656-f4d872fa-7657-4072-81d9-6cc6c155dd05.png" width="425"></td>
    <td>The Seawater sample and the chemiluminecent reagent (MCLA for measurement of O<sup>2-</sup>) enter the center of the spiral flow cell from their respective ports. This cell is optically monitoured through a optically clear saphire window by the PMT</td>
  </tr>
</table>




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



### Electrical
#### Main Electrical Housing (Reagent Assembly)
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

#### PMT Electrical Housing (Analyzer Assembly)
<table>
  <tr>
    <td>Full View PCB</td>
     <td>Zoomed View</td>
  </tr>
  <tr>
    <td><img src="https://user-images.githubusercontent.com/57682790/235890826-91f8cac9-96cd-42dd-b490-ef582570b7f4.jpg" width="425"></td>
    <td><img src="https://user-images.githubusercontent.com/57682790/235890962-8c4e7799-e145-4ed3-bef4-0770eeab9a5e.jpg" width="425"></td>
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
![image](https://user-images.githubusercontent.com/57682790/235923643-7d9d430f-be96-4041-9941-de09d2f8111d.png)

#### Autonomous Mission Planning

### Using the Emulator

Download & install the free serial port emulator (emulator\free-virtual-serial-port-tools.exe)
  Select creat local bridge & configure:
    First port name: COM1
    Secound port name: COM2
  Create - select "Creat non-permanent device" checkbox and then OK
Run the emulator
  '''python3 emulator.py'''
Select previous datafile using explorer
Open the app and use on COM2

#### Dependencies
'''pip3 install scipy'''


### Firmware

#### 23_0001_01_Rb

#### Passthrough
  
