**LMIC Linear Motor IoT Controller

------------

LMIC is a DC Linear Motor IoT Controller, based on an ESP8266, with Hardware Safety Features.  This board is designed to interface any Home Automation System.

![Display-Type-B](https://ditronix.net/wp-content/uploads/2022/11/LMIC-ESP8266-SDK-v1-2210-104-OLED-Bring-Up-scaled.jpg?raw=true)


The board has three DC Linear Motor Outputs (all paralleled to the L6205 Dual DMOS Full Bridge Driver).

- Low voltage DC input (10-32V), is fed via the terminal block (not populated), or you may optionally solder the power supply cable tails directly to the PCB.
- Solar Panel Tracking maybe used using the OPTO input.
- Hardware Safety Circuit.
- Power for the board may either be provided via the Micro USB (for flashing, debugging etc.).

An OPTO sensor input is provided for Solar Tracking, so you may connect a daylight sensor such as the a 3DU5C, TSL257 or GL5528.  This could be mounted on the SDK or wired remotely. OPTO not included.

An I2C 2.54mm header is provided in the middle of the board, which will allow an OLED display (such as a SSD1306 I2C), to be directly mounted / connected on the board.  OLED not included.

**Principle Safety Requirements**

Linear motors have an incredible torque and with the added extremes of weather or possible jams, the DC motor driver (ST L6205 DMOS dual full bridge IC), safety features are fed into a hardware safety circuit.

- Protection from over current, such as jamming
- Protection from over temperature, with Thermal Shutdown
- Protection from Cross Conduction
- Under Voltage Lockout
- Robust DC Driver(s)
- Plug in an external I2C temperature sensor for separate measuring ambient temperature
- The dedicated hardware safety circuit included on the board sets a flag to a GPIO, on an alert trip. From this alert signal you can then action as needed – ideally STOP!

**Solar Tracking**

In controlling Solar Panels, a nice to have feature is not only integration into the Home Automation system, but also to maximise the sunlight light and protect from high winds. This in in effect Solar Tracking.

1) With sunlight, one could obviously measure the panel outputs but in your have a number of panel strings, then this may not be totally reliable. A solution was to add a photo transistor or diode input, into the controller.

Solar tracking works OK with the single photo diode. It would be good to average more but how far does one go. Either way, a time period needs to be added in between (dwell), so that the panels do not constantly move back and forth – stressing the linear motors unnecessarily. Some hysteresis could ideally be included in the code. All part of experimenting.

2) Controlling the panels and safely lowering in high winds, at night or other scenarios, can be via the Home Automation system and coupled with a weather station anemometer (for example), ticks the box.


All test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed.  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

Further information can be found:

- **Website** https://ditronix.net/
- **WIKI**  https://ditronix.net/wiki/
- **GitHub**  https://github.com/DitroniX/
- **Shop**  https://ditronix.net/shop/

Dave Williams | G8PUO | DitroniX 1981-2022 | ditronix.net
