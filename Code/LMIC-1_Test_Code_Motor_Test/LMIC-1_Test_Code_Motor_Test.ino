/*
  Dave Williams, DitroniX 2019-2022 (ditronix.net)
  LMIC-1 Linear Motor IoT Controller v1.0
  Features include ESP8266 DC Linear Motor Driver Voltage OLED I2C Safety Lockout
  PCA v1.00 - Test Code Firmware v1 - 
  .
  Simplified Board Bring Up Test - Motor Test
  .
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

// **************** INPUTS ****************
#define ADC A0 // ADC
#define SFLAG 14 // SFLAG (Safety Flag) Input Port

// **************** OUTPUTS ****************
#define LED_Blue 2 // Blue LED
#define EN_1 15 // Driver Enable
#define OUT_1A 12 // Motor Driver A
#define OUT_1B 13 // Motor Driver B

// **************** IO ****************

// Define I2C (Expansion Port)
#define I2C_SDA 4
#define I2C_SCL 5

void setup() {

  // Stabalise
  delay(250);

  // Initialise UART
  Serial.begin(115200, SERIAL_8N1);  //115200
  while (!Serial);
  Serial.println("");  

  //  Configures the specified LED GPIO as outputs
  pinMode(LED_Blue, OUTPUT);

  // LED Default Off State
  digitalWrite(LED_Blue, HIGH);

  // Initialize Output Ports Driver (L6205 Inputs)
  pinMode (EN_1, OUTPUT);
  pinMode (OUT_1A, OUTPUT);
  pinMode (OUT_1B, OUTPUT);

  // Sets Motor Driver Outputs Low and Disable
  digitalWrite(EN_1, LOW);
  digitalWrite(OUT_1A, LOW);
  digitalWrite(OUT_1B, LOW);

  pinMode (SFLAG, INPUT); // Safety Flag

}

void FaultConditionCheck()
{
  if (digitalRead(SFLAG) == HIGH)
  {
    Serial.println("Motor Driver Safety Flag");
    Serial.println("Disable both Motor Driver Ports");

    // Red LED Flash Alert
    for (int x = 0; x <= 10; x++) {
      delay(250);
      digitalWrite(LED_Blue, LOW);
      delay(250);
      digitalWrite(LED_Blue, HIGH);
    }

    // Reset ESP
    Serial.println("> RESTARTING ESP");
    delay(2000);
    void(* resetFunc) (void) = 0;//declare reset function at address 0
    resetFunc(); //call reset
  }
}

void loop() {

  // Check for Fault Condition
  FaultConditionCheck();

  // Enable both Motor Driver Ports
  digitalWrite(EN_1, HIGH);
  digitalWrite(OUT_1A, HIGH);
  digitalWrite(OUT_1B, LOW);
  delay(1000);

  digitalWrite(OUT_1A, LOW);
  digitalWrite(OUT_1B, HIGH);
  delay(2000);

  // Enable both Motor Driver Ports
  digitalWrite(EN_1, LOW);

  // Heat Beat Blue LED
  delay(250);
  digitalWrite(LED_Blue, LOW);
  delay(10);
  digitalWrite(LED_Blue, HIGH);

  // Loop Delay
  delay(LoopDelay * 1000);

}
