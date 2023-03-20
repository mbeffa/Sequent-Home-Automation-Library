# Sequent-Home-Automation-Library
Easy to use Arduino library for Sequent Microsystems [Home Automation 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/raspberry-pi-home-automation-card)

## Install
To download click <>Code > DOWNLOAD ZIP button, rename the uncompressed folder to "SM_Home_Automation" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see Sequent Home Automation HAT inside. 
 The library will be compiled with sketches that use it. Open a arduino sketch, fo to File > Examples > Sequent Home Automation HAT > and chose your example to run.

## Usage
This library can be used with any Arduino card that have I2C port but you need to wire them up or with some Sequent Microsystems adapter cards.

### Method 1:
Connect I2C SDA, I2C SCL, 5V and GND from Arduino card to Home automation hat, pin map below
      
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
 
### Method 2:
Use Sequent Microsystems [Uno/Nano/Teensy/Feather/ESP32 Raspberry Pi Replacement Kit](https://sequentmicrosystems.com/collections/accessories/products/raspberry-pi-replacement-card) with prefered arduino processor then plug The Home Automation Card into the 40 pin header.
 
### Method 3:
Use Sequent Microsysstems [ESP32 Pi Replacement Card](https://sequentmicrosystems.com) connected directly with the Home Automation card.
In your sketchbook set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1
