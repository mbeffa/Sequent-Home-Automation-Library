# Sequent-Home-Automation-Library
Arduino library for Sequent Microsystems [Home Automation 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/raspberry-pi-home-automation-card)

## Install
To download click <>Code > Download ZIP button, rename the uncompressed folder to "SM_Home_Automation" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see Sequent Home Automation HAT inside. 
 The library will be compiled with sketches that use it. Open an arduino sketch, go to File > Examples > Sequent Home Automation HAT > and chose your example to run.

## Usage
There are three ways to control the Home Automation Card from the Arduino environment.

### Method 1: No aditional hardware required.
You can use this method with any Arduino card with an I2C port by connecting the I2C signals, power and ground, as shown in the following table.
      
| SIGNAL | PIN# |CONN| PIN# | SIGNAL|
|---|---|---|---|---|
| | --1 | O - O | 2-- |  +5V | 
| I2C SDA | --3| O - O | 4-- |  +5V |
| I2C SCL |-- 5|O - O| 6--|  GND |
|  |-- 7|O - O| 8--||
| GND |-- 9|O - O|10--||
| |--11|O - O|12--||
| |--13|O - O|14--| GND|
| |--15|O - O|16--||
||--17|O - O|18--||
||--19|O - O|20--|  GND|
||--21|O - O|22--||
||--23|O - O|24--||
|GND |--25|O - O|26--||
||--27|O - O|28--||
||--29|O - O|30--|  GND|
||--31|O - O|32--||
||--33|O - O|34--|  GND|
||--35|O - O|36--||
||--37|O - O|38--||
|GND |--39|O - O|40--||
 
### Method 2: Using the SM Arduino Raspberry Pi Replacement Kit
Sequent Microsystems [Arduino Uno, Nano, Teensy, Feather or ESP32 Raspberry Pi Replacement Kit](https://sequentmicrosystems.com/products/raspberry-pi-replacement-card) is an inexpensive adapter which can be used to control any of our HATs with five Arduino cards: Uno, Nano, Teensy, Feather or ESP32. Simply plug the Home Automation HAT into the 40 pin connector of the adapter and run your Arduino software.

### Method 3: Using the SM ESP32-Pi Raspberry Pi Alternative
Coming soon: ESP32-Pi, a Raspberry Pi alternate solution which could connect directly to the Home Automation HAT.
In your sketchbook set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1
