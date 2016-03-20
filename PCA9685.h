/*  PCA9685 library for Arduino
    Copyright (C) 2012 Kasper Skårhøj    <kasperskaarhoj@gmail.com> 

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PCA9685_H
#define PCA9685_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Wire.h"

/**
  Version 1.0.0
	(Semantic Versioning)
**/
 
//Register defines from data sheet
#define PCA9685_MODE1 0x00 // location for Mode1 register address
#define PCA9685_MODE2 0x01 // location for Mode2 reigster address
#define PCA9685_LED0 0x06 // location for start of LED0 registers

// mode1 register parameters.

// restart
#define MODE1_RESTART_ENABLE   0x80
#define MODE1_RESTART_DISABLE  0
// external clock
#define MODE1_EXTCLK_ENABLE    0
#define MODE1_EXTCLK_DISABLE   0x40
// auto-increment
#define MODE1_AI_ENABLE        0x20
#define MODE1_AI_DISABLE       0
// sleep (low power) mode
#define MODE1_SLEEP_ENABLE     0x10
#define MODE1_SLEEP_DISABLE    0
// respond to I2C subaddresses 1, 2, and 3
#define MODE1_SUB1_ENABLE      0x08
#define MODE1_SUB1_DISABLE     0
#define MODE1_SUB2_ENABLE      0x04
#define MODE1_SUB2_DISABLE     0
#define MODE1_SUB3_ENABLE      0x02
#define MODE1_SUB3_DISABLE     0
// respond to I2C all-call address
#define MODE1_ALLCALL_ENABLE   0x01
#define MODE1_ALLCALL_DISABLE  0

// mode2 register parameters. 

// inverse logic
#define MODE2_INVRT_ENABLE      0x10
#define MODE2_INVRT_DISABLE     0
// when outputs are changed
#define MODE2_OCH_ON_STOP       0
#define MODE2_OCH_ON_ACK        0x08
// how the outputs are configured
#define MODE2_OUTDRV_OPEN_DRAIN 0
#define MODE2_OUTDRV_TOTEM_POLE 0x04
// the behaviour when OE is high
#define MODE2_OUTNE_HIGH_Z      0x03 // LEDn is HIGH_Z
#define MODE2_OUTNE_HIGH        0      // LEDn is LOW
#define MODE2_OUTNE_LOW         0x01    // when MODE2_OUTDRV_TOTEM_POLE is enabled, LEDn becomes HIGH_Z


#define PCA9685_I2C_BASE_ADDRESS B1000000

class PCA9685
{
  public:
    //NB the i2c address here is the value of the A0, A1, A2, A3, A4 and A5 pins ONLY
    //as the class takes care of its internal base address.
    //so i2cAddress should be between 0 and 63
    PCA9685();
    void begin(int i2cAddress);
    bool init(int mode1Register=0x01, int mode2Register=0xA0);

	void setLEDOn(int ledNumber);
	void setLEDOff(int ledNumber);
	void setLEDDimmed(int ledNumber, byte amount);
	void writeLED(int ledNumber, word outputStart, word outputEnd);
	
  private:
	void writeRegister(int regaddress, byte val);
	word readRegister(int regAddress);
	// Our actual i2c address:
	byte _i2cAddress;
};
#endif 
