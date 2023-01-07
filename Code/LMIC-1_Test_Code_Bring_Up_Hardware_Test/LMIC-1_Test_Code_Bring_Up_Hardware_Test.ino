/*
  Dave Williams, DitroniX 2019-2023 (ditronix.net)
  LMIC-1 Linear Motor IoT Controller v1.0
  Features include ESP8266 DC Linear Motor Driver Voltage OLED I2C Safety Lockout
  PCA v1.00 - Test Code Firmware v1 - 6th January 2023
  
  Simplified Board Bring Up Test - Hardware Motor and Safety Circuit Test, with or without OLED Display 

  This code will initialise the linear motor driver and toggle back and forth the output.
  During the motor movment, the LMIC safety circuit will be monitored and if triggered, will warn the user and reboot the ESP
  Both the serial monitor and any connected OLED display, wil be updated.
  Note.  See FaultConditionCheck, for important option relating to hardware fault checking.

  **IMPORTANT**
  It is important that you observe the FaultConditionCheck and DelayFaultCheck functions and use it in your code, 
  in order to detect a hardware driver fault, such as shorted outputs, over-load, thermal trip etc.
  
  Remember!
  - Set the BOARD to ESP8266 DEV Module (Wemos D1 or similar).
  - You can also set the BAUD rate up to 921600 to speed up flashing.
  - The SDK does NOT need external power to flash.  It will take Power from the USB 5V.
  
  The purpose of this test code is to cycle through the various main functions of the board as part of bring up testing.
  
  This test code is OPEN SOURCE and formatted for easier viewing.  Although is is not intended for real world use, it may be freely used, or modified as needed.
  It is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

  Further information, details and examples can be found on our website wiki pages ditronix.net/wiki and github.com/DitroniX
*/

// Libraries
#include <GyverOLED.h>  // Download via Managed Libraries

// OLED Instance. You will need to select your OLED Display.Â 
// Uncomment/Comment as needed.
//GyverOLED<SSD1306_128x32, OLED_BUFFER> oled; // 0.6" Lower Resolution
//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;  // 0.6" Higher Resolution
//GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
//GyverOLED<SSH1106_128x64> oled;

// ****************  VARIABLES / DEFINES / STATIC ****************

// Constants
const int LoopDelay = 1;  // Loop Delay in Seconds

// **************** INPUTS ****************
#define ADC A0    // ADC
#define SFLAG 14  // SFLAG (Safety Flag) Input Port
#define UButton 16 // User Button (Disabled if Sleep Enabled)

// **************** OUTPUTS ****************
#define LED_Blue 2  // Blue Status LED
#define EN_1 15     // Driver Enable
#define OUT_1A 12   // Motor Driver A
#define OUT_1B 13   // Motor Driver B

// **************** IO ****************

// Define I2C (Expansion Port)
#define I2C_SDA 4
#define I2C_SCL 5

// **************** FUNCTIONS AND ROUTINES ****************

// IMPORTANT.  This detects a hardware fault in the driver, such as shorted outputs, over-load, temperate etc.
// Monitor the Hardware Safety Circuit Flag (SFLAG on GPIO 14).  Force Motor Driver to be disabled and reboot.
// May be set to 'tripped' and only reset on power cycle / hard reset - or not.  See IMPORTANT OPTION.
void FaultConditionCheck() {

  // WDT (Watch Dog Timer) Reset
  yield();

  // Check SFLAG.  If High Disable Driver
  if (digitalRead(SFLAG) == HIGH) {

    // IMPORTANT OPTION
    // Make EN_1 LOW to LATCH on fault - will force Power Cycle or hard reset, to clear. Force Motor Driver to be disabled.
    // Make EN_1 HIGH will automatically reset latch on soft/hard reboot and continue working - No latch .
    digitalWrite(EN_1, LOW);

    // Sets Motor Driver Outputs Low
    digitalWrite(OUT_1A, LOW);
    digitalWrite(OUT_1B, LOW);

    // Update the OLED Display
    oled.clear();
    oled.setScale(3);
    oled.setCursor(0, 0);
    oled.println(" CHECK ");
    oled.println("FAULT!!");
    oled.update();

    // Update Serial Display
    Serial.println("Motor Driver Safety Flag Activated");
    Serial.println("Disabled both Motor Driver Ports");
    Serial.println("ESP8266 Will Be Soft Restarted");

    // Blue Status LED Flash Alert
    for (int x = 0; x <= 20; x++) {
      delay(250);
      digitalWrite(LED_Blue, LOW);
      delay(250);
      digitalWrite(LED_Blue, HIGH);
    }

    // Update the OLED Display
    oled.clear();
    oled.setScale(3);
    oled.setCursor(0, 0);
    oled.println("REBOOTG");
    if (digitalRead(SFLAG) == LOW && digitalRead(EN_1) == LOW) {
      oled.println("LATCHED");
      oled.setScale(2);
      oled.println("PowerCycle");
      Serial.println("LATCHED Fault.  Power Cycle or Hard Reset to Clear");
    }
    oled.update();

    // Reset ESP8266
    // Declare reset function at address 0
    void (*resetFunc)(void) = 0;
    //Call Reset
    resetFunc();
  }
}

// Delay by X seconds and keep checking SFLAG on GPIO 14
void DelayFaultCheck(int sDelay) {
  unsigned long currentMillis;
  currentMillis = millis();

  while ((millis() - currentMillis) < (sDelay * 1000)) {
    FaultConditionCheck();
  }
}

void ScanI2C() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning I2C Bus for Devices ...");

  nDevices = 0;
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address Decimal ");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.print(address, HEX);
      if (address == 0x3C || address == 0x3D) Serial.print(" (OLED Display Found)");
      Serial.println();
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address Decimal ");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address);
      Serial.print(" = Hex 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
}

// **************** SETUP ****************
void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial)
    ;
  Serial.println("");

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Blue, OUTPUT);

  // LED Default Off State
  digitalWrite(LED_Blue, HIGH);

  // Safety Flag
  pinMode(SFLAG, INPUT);

  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  ScanI2C();

  // Initialize Output Ports Driver (L6205 Inputs)
  pinMode(EN_1, OUTPUT);
  pinMode(OUT_1A, OUTPUT);
  pinMode(OUT_1B, OUTPUT);

  // Sets Motor Driver Outputs Low and Disable
  digitalWrite(EN_1, LOW);
  digitalWrite(OUT_1A, LOW);
  digitalWrite(OUT_1B, LOW);

  // OLED
  oled.init();
  oled.clear();
  oled.setCursor(18, 0);
  oled.setScale(5);
  oled.print("LMIC");
  oled.update();

  // Check for Fault Condition
  DelayFaultCheck(2);  // Delay for X seconds but keep monitoring the Safety Flag

  Serial.println("LMIC Ready");
}

// **************** LOOP ****************
void loop() {

  // Update the OLED Display
  oled.clear();
  oled.setScale(3);
  oled.setCursor(0, 0);
  oled.println("1A High");
  oled.println("< < <  ");
  oled.update();
  Serial.println("LMIC Motor Driver Output 1A High");

  // Sets Motor Driver Outputs 1A High
  digitalWrite(EN_1, HIGH);
  digitalWrite(OUT_1A, HIGH);
  digitalWrite(OUT_1B, LOW);
  DelayFaultCheck(2);  // Delay for X seconds but keep monitoring the Safety Flag

  // Update the OLED Display
  oled.clear();
  oled.setScale(3);
  oled.setCursor(0, 0);
  oled.println("1B High");
  oled.println("  > > >");
  oled.update();
  Serial.println("LMIC Motor Driver Output 1B High");

  // Sets Motor Driver Outputs 1B High
  digitalWrite(EN_1, HIGH);
  digitalWrite(OUT_1A, LOW);
  digitalWrite(OUT_1B, HIGH);
  DelayFaultCheck(2);  // Delay for X seconds but keep monitoring the Safety Flag

  // Sets Motor Driver Outputs Low and Disable
  digitalWrite(EN_1, LOW);
  digitalWrite(OUT_1A, LOW);
  digitalWrite(OUT_1B, LOW);

  // Heat Beat Blue Status LED
  delay(250);
  digitalWrite(LED_Blue, LOW);
  delay(10);
  digitalWrite(LED_Blue, HIGH);

  // Loop Delay
  DelayFaultCheck(2);  // Delay for X seconds but keep monitoring the Safety Flag
}
