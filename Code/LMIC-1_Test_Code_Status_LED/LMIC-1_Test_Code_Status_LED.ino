/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  LMIC-1 Linear Motor IoT Controller v1.0
  Features include ESP8266 DC Linear Motor Driver Voltage OLED I2C Safety Lockout 
  PCA v1.00 - Test Code Firmware v1 - 30th September 2022
  
  Simplified Board Bring Up Test - Status LED
  
  Remember!
  - Set the BOARD to ESP8266 DEV Module (or similar).
  - You can also set the BAUD rate up to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  
  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.
  
  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and github.com/DitroniX
*/

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1; // Loop Delay in Seconds

// **************** OUTPUTS ****************
#define LED_Blue 2 // Blue LED

// **************** INPUTS ****************

void setup() {

  // Stabalise
  delay(250);

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Blue, OUTPUT);

  // LEDs Default Off State
  digitalWrite(LED_Blue, HIGH);
}

void loop() {

  // Test Blue Status LED

  // Blue
  digitalWrite(LED_Blue, LOW);

  // Loop Delay
  delay(LoopDelay * 1000);
  
  digitalWrite(LED_Blue, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);

}
