## LMIC Linear Motor IoT Controller

LMIC is a DC Linear Motor IoT Controller, based on an ESP8266, with Hardware Safety Features.  This board is designed to interface any Home Automation System.

![Display-Type-B](https://ditronix.net/wp-content/uploads/2022/11/LMIC-ESP8266-SDK-v1-2210-104-OLED-Bring-Up-scaled.jpg?raw=true)


The board has three DC Linear Motor Outputs (all paralleled to the L6205 Dual DMOS Full Bridge Driver).

- Low voltage DC input (10-32V), is fed via the terminal block (not populated), or you may optionally solder the power supply cable tails directly to the PCB.
- On-board 3V3 Buck Regulator
- Solar Panel Tracking maybe used using the OPTO input.
- Hardware Safety Circuit.
- Power for the board may be provided via the Micro USB (for flashing, debugging etc.).  

An OPTO sensor input is provided for Solar Tracking, so you may connect a daylight sensor such as the a 3DU5C, TSL257 or GL5528.  This could be mounted on the SDK or wired remotely. OPTO not included.

An I2C 2.54mm header is provided in the middle of the board, which will allow an OLED display (such as a SSD1306 I2C), to be directly mounted / connected on the board.  OLED not included.

![Display-Type-B](https://ditronix.net/wp-content/uploads/2023/01/LMIC-ESP8266-SDK-v1-2212-105-Enclosure-scaled.jpg?raw=true)

**Principle Safety Requirements**

Linear motors have an incredible torque and with the added extremes of weather or possible jams, the DC motor driver (ST L6205 DMOS dual full bridge IC), safety features are fed into a hardware safety circuit.

- Protection from over current, such as jamming
- Protection from over temperature, with Thermal Shutdown
- Protection from Cross Conduction
- Under Voltage Lockout
- Robust DC Driver(s)
- Plug in an external I2C temperature sensor for separate measuring ambient temperature
- The dedicated hardware safety circuit included on the board sets a flag to a GPIO, on an alert trip. From this alert signal you can then action as needed – ideally STOP!

![Display-Type-B](https://ditronix.net/wp-content/uploads/2023/01/LMIC-ESP8266-SDK-v1-2211-105-OLED-LATCHED.jpg?raw=true)

**Solar Tracking**

In controlling Solar Panels, a nice to have feature is not only integration into the Home Automation system, but also to maximise the sunlight light and protect from high winds. This in in effect Solar Tracking.

1) With sunlight, one could obviously measure the panel outputs but in your have a number of panel strings, then this may not be totally reliable. A solution was to add a photo transistor or diode input, into the controller.

Solar tracking works OK with the single photo diode. It would be good to average more but how far does one go. Either way, a time period needs to be added in between (dwell), so that the panels do not constantly move back and forth – stressing the linear motors unnecessarily. Some hysteresis could ideally be included in the code. All part of experimenting.

2) Controlling the panels and safely lowering in high winds, at night or other scenarios, can be via the Home Automation system and coupled with a weather station anemometer (for example), ticks the box.

**LMIC 'What Is In The Shipping Box'**
![Display-Type-B](https://ditronix.net/wp-content/uploads/2023/01/LMIC-ESP8266-In-The-Box-scaled.jpg?raw=true)


All test code is OPEN SOURCE and although is is not intended for real world use, it may be freely used, or modified as needed.  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.


## **Further Information**

Additional information, and other technical details on this project, maybe found in the related repository pages.

**Repository Folders**

 - **Code** *(Code examples for Arduino  IDE and PlatformIO)*
 -  **Datasheets and Information** *(Component Datasheets, Schematics, Board Layouts, Photos, Technical Documentation)*
 - **Certification** *(Related Repository Project or Part, Certification Information)*

**Repository Tabs**

 - **Wiki** *(Related Repository Wiki pages and Technical User Information)*
 - **Discussions** *(Related Repository User Discussion Forum)*
 - **Issues** *(Related Repository Technical Issues and Fixes)*

***

We value our Customers, Users of our designs and STEM Communities, all over the World . Should you have any other questions, or feedback to share to others, please feel free to:

* Visit the related [Project](https://github.com/DitroniX?tab=repositories) *plus the related* **Discussions** and **Wiki** Pages.  See tab in each separate repository.
* **Project Community Information** can be found at https://www.hackster.io/DitroniX
* [DitroniX.net Website - Contact Us](https://ditronix.net/contact/)
* **Twitter**: [https://twitter.com/DitroniX](https://twitter.com/DitroniX)
* [Supporting the STEM Projects - BuyMeACoffee](https://www.buymeacoffee.com/DitroniX)
*  **LinkedIN**: [https://www.linkedin.com/in/g8puo/](https://www.linkedin.com/in/g8puo/)

***Dave Williams, Eastbourne, UK.***

Electronics Engineer | Software Developer | R&D Support | RF Engineering | Product Certification and Testing | STEM Ambassador

## STEM

**Supporting [STEM Learning](https://www.stem.org.uk/)**

Life is one long exciting learning curve, help others by setting the seed to knowledge.

![DitroniX Supporting STEM](https://hackster.imgix.net/uploads/attachments/1606838/stem_ambassador_-_100_volunteer_badge_edxfxlrfbc1_bjdqharfoe1_xbqi2KUcri.png?auto=compress%2Cformat&w=540&fit=max)
