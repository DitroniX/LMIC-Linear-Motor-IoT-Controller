**LMIC ESP8266 Linear Motor IoT Controller**

------------

This folder contains LMIC Example Source Code.

Simplified Board Bring Up Test - Hardware Motor and Safety Circuit Test, with or without OLED Display 

The code example is used to test the LMIC harware:

- Power Up
- LED Test
- I2C Scan Test
- OLED Test (if connected)
- Motor Driver - Both directions
- Hardware Safety Circuit.  Tripped and non tripped.

Notes:

- For the 0.6" OLD, use the GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
- FaultConditionCheck routine has two options
	- Latch on fault.  Hardware has to be power cycled, or hard reset - to reset
	- Non Latch. Hardware will auto reset upon soft reboot.
- Normal operation of this code will drive the linear motor in both directions for 2 second cycle, back and forth.


**IMPORTANT**
It is important that you observe the FaultConditionCheck and DelayFaultCheck functions and use it in your code, in order to detect a hardware driver fault, shorted outputs, over-load, thermal trip etc.

Example
https://ditronix.net/wiki/lmic-esp8266-hardware-motor-and-safety-circuit-test/



  Remember!
  - Set the BOARD to ESP8266 DEV Module (Wemos D1 or similar).
  - You may set the BAUD rate to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  
  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.


Further information can be found:

- **Website** https://ditronix.net/
- **WIKI**  https://ditronix.net/wiki/
- **GitHub**  https://github.com/DitroniX/
- **Shop**  https://ditronix.net/shop/

Dave Williams | G8PUO | DitroniX 1981-2023 | ditronix.net
