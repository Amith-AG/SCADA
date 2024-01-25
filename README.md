# Design and Implementation of a Miniature SCADA System for Industrial Parameter Monitoring and Control

Abstract:
This abstract presents a mini model Supervisory Control and Data Acquisition (SCADA) project consisting of eight interconnected block units. The project aims to develop a compact SCADA system that monitors critical parameters in a factory environment, such as temperature, humidity, and gas leakage, while providing control capabilities and warnings for enhanced safety and efficiency.

The microcontroller unit serves as the central processing unit, continuously monitoring the factory's critical parameters and controlling them. In the event of a gas leakage, it provides warnings and connects to the internet for remote monitoring and control. The project utilizes the NodeMCU ESP8266 development board, equipped with the ESP8266 chip, supporting a 32-bit LX106 RISC microprocessor with adjustable clock frequency.

The display unit presents real-time data of the monitored parameters, including temperature and humidity, providing operators with an overview of the factory conditions. The power supply unit ensures a stable 5V input voltage for the microcontroller and other components, utilizing a 9V battery and a 7805 IC voltage regulator.

The gas sensing unit employs the MQ4 gas sensor, which detects gas leakage and sends a high input signal to the NodeMCU for appropriate actions. The temperature and humidity sensing unit utilizes the DHT22 sensor to collect relevant data for precise environmental monitoring.

The heating system, comprising an incandescent light bulb, provides supplementary heat if the temperature falls below a user-defined critical range. Similarly, the cooling system, utilizing a 12V DC fan, offers cooling support if the temperature rises above the critical range.

Furthermore, the project includes a warning system that combines a buzzer and an LED to provide audible and visual alerts in the event of a gas leak, ensuring prompt response and enhanced safety measures.

This mini SCADA project offers a cost-effective solution for real-time monitoring and control of critical parameters in a factory environment. It showcases the utilization of microcontrollers, sensors, and actuators to enable efficient decision-making and rapid response to abnormal conditions. This abstract sets the stage for a detailed exploration of the project's methodology, results, and potential future enhancements.
The provided code is an Arduino sketch written for an ESP8266 microcontroller board using the Arduino IDE. Let's go through the code section by section to understand its functionality:

1. Libraries:
```cpp
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
```
This section includes the necessary libraries for the code. The `ESP8266WiFi` library provides functions for connecting to Wi-Fi networks, the `LiquidCrystal_I2C` library allows communication with the I2C-based LCD display, the `BlynkSimpleEsp8266` library provides the Blynk IoT platform integration, and the `DHT` library is used for reading temperature and humidity from the DHT22 sensor.

2. Pin Definitions:
```cpp
#define DHTPIN D5
#define DHTTYPE DHT22
#define GAS_SEN A0
#define FAN D1
#define LIGHT D2
#define Buzzer D7
```
These lines define the pin mappings for various components used in the circuit, such as the DHT22 sensor (connected to pin D5), gas sensor (connected to analog pin A0), fan (connected to pin D1), light (connected to pin D2), and buzzer (connected to pin D7).

3. Variable Declarations and Initialization:
```cpp
int gas = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
char auth[] = "AMku9sLLkOIXPGKhhzMUMzD0yYREyckm";
char ssid[] = "OnePlus 6";
char pass[] = "renjiths";
float TEMP_SET_MAX = 35;
float TEMP_SET_MIN = 33;
float h, t;
int x, GAS_SENSE_VALUE = 0;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
```
This section declares and initializes various variables used in the code, including gas (for gas leakage detection), an instance of the LiquidCrystal_I2C class for controlling the LCD display, authentication token, Wi-Fi credentials, temperature and humidity variables (h and t), gas sensor value (GAS_SENSE_VALUE), an instance of the DHT class for reading temperature and humidity values, and a BlynkTimer object for scheduling periodic events.

4. Function Definitions:
```cpp
void myTimerEvent()
{
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, GAS_SENSE_VALUE);
  
  if (gas == 1) {
    Blynk.notify("GAS Leakage Happened !");
  }
}

void setup()
{
  // Initialization code
}

void loop()
{
  // Main code
}

void TEMP_MAINTAIN()
{
  // Temperature maintenance code
}

void GAS_LEAK()
{
  // Gas leakage detection code
}
```
These lines define the functions used in the code. `myTimerEvent()` is a function that is called periodically by the `timer` object. It sends the temperature, humidity, and gas sensor values to the Blynk app and sends a notification if a gas leakage is detected. `setup()` is the setup function that runs once when the microcontroller starts. `loop()` is the main function that runs repeatedly after the setup. `TEMP_MAINTAIN()` and `GAS_LEAK()` are helper functions for handling temperature maintenance and gas leakage detection, respectively.

5. Setup Function:
```cpp
void setup()
{
  Serial.begin(9600);
  
  pinMode(GAS_SEN, INPUT

);
  pinMode(Buzzer, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(LIGHT, OUTPUT);
  
  digitalWrite(LIGHT, LOW);
  digitalWrite(FAN, LOW);
  
  lcd.begin(D4, D3);
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Connecting Blynk");
  
  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(5000L, myTimerEvent);
  
  lcd.setCursor(0, 1);
  lcd.print(" connected ");
  
  delay(3000);
  
  dht.begin();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Services Started");
  
  digitalWrite(Buzzer, HIGH);
  delay(50);
  digitalWrite(Buzzer, LOW);
  delay(50);
  digitalWrite(Buzzer, HIGH);
  delay(50);
  digitalWrite(Buzzer, LOW);
  delay(50);
  digitalWrite(Buzzer, HIGH);
  delay(50);
  digitalWrite(Buzzer, LOW);
  
  delay(2000);
  lcd.clear();
}
```
The setup function is responsible for initializing various components, setting up the LCD display, connecting to Wi-Fi, and initializing the Blynk integration. It also sets the interval for the `myTimerEvent()` function to be called every 5 seconds. The LCD display shows messages indicating the status of the setup process.

6. Loop Function:
```cpp
void loop()
{
  Blynk.run();
  timer.run();
  
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Sensor Error");
    lcd.setCursor(3, 1);
    lcd.print("Restarting");
    delay(2000);
    ESP.restart();
  }
  
  GAS_LEAK();
  
  if (gas == 0) {
    TEMP_MAINTAIN();
    delay(4000);
    lcd.clear();
    // Display temperature and humidity on LCD
  }
}
```
The loop function is the main part of the code that runs repeatedly. It calls the `Blynk.run()` and `timer.run()` functions to handle Blynk communication and timer events, respectively. It also reads temperature and humidity values from the DHT22 sensor. If the sensor readings are valid, it proceeds to check for gas leakage using the `GAS_LEAK()` function. If no gas leakage is detected, it calls the `TEMP_MAINTAIN()` function to handle temperature maintenance and displays temperature and humidity readings on the LCD display.

That's a summary of the provided code. It combines Wi-Fi connectivity, sensor readings, LCD display control, Blynk integration, and control of various components based on sensor values.
