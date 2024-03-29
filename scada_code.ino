#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN D5
#define DHTTYPE DHT22
#define GAS_SEN A0
#define FAN D1
#define LIGHT D2
#define Buzzer D7
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
void myTimerEvent()
{
 
Blynk.virtualWrite(V0,t);
 
Blynk.virtualWrite(V1,h);
 
Blynk.virtualWrite(V2,GAS_SENSE_VALUE);
if (gas == 1) {
 
Blynk.notify("GAS Leakage Happened !");
 
}
}
void setup()
{
 
Serial.begin(9600);
 
pinMode(GAS_SEN, INPUT);
 
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
 
delay(50);
 
delay(2000);
 
lcd.clear();
}
void loop()
{
 
Blynk.run();
 
timer.run(); // Initiates BlynkTimer
 
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
 
lcd.setCursor(0, 0);
 
lcd.print("Temp:");
 
lcd.setCursor(6, 0);
 
lcd.print(t);
 
lcd.setCursor(12, 0);
lcd.print((char)223);
 
lcd.setCursor(13, 0);
 
lcd.print("C");
 
lcd.setCursor(0, 1);
 
lcd.print("Hum :");
 
lcd.setCursor(6, 1);
 
lcd.print(h);
 
lcd.setCursor(12, 1);
 
lcd.print("%");
 
delay(4000);
 
}
}
void TEMP_MAINTAIN() {
 
if (t > TEMP_SET_MIN && t < TEMP_SET_MAX) {
 
lcd.clear();
 
lcd.setCursor(2, 0);
 
lcd.print("Temperature");
 
lcd.setCursor(5, 1);
 
lcd.print("Normal");
 
digitalWrite(FAN, LOW);
 
digitalWrite(LIGHT, LOW);
 
}
 
if (t > TEMP_SET_MAX) {
 
lcd.clear();
 
lcd.setCursor(0, 0);
 
lcd.print("Temperature High");
 
lcd.setCursor(1, 1);
 
lcd.print("Fan Turned ON");
 
digitalWrite(FAN, HIGH);
 
digitalWrite(LIGHT, LOW);
 
}
 
if (t < TEMP_SET_MIN) {
 
lcd.clear();
 
lcd.setCursor(0, 0);
lcd.print("Temperature Low");
 
lcd.setCursor(0, 1);
 
lcd.print("Heater Turned ON");
 
digitalWrite(LIGHT, HIGH);
 
digitalWrite(FAN, LOW);
 
}
}
void GAS_LEAK() {
 
GAS_SENSE_VALUE = analogRead(GAS_SEN);
 
if (GAS_SENSE_VALUE < 5) {
 
lcd.clear();
 
lcd.setCursor(2, 0);
 
lcd.print("MQ5 Sensor");
 
lcd.setCursor(2, 1);
 
lcd.print("Read Error");
 
}
 
if (GAS_SENSE_VALUE > 500) {
 
gas = 1;
 
digitalWrite(Buzzer, HIGH);
 
digitalWrite(FAN, HIGH);
 
digitalWrite(LIGHT, LOW);
 
lcd.clear();
 
lcd.setCursor(3, 0);
 
lcd.print("GAS Leakage");
 
lcd.setCursor(4, 1);
 
lcd.print("happened");
 
delay(100);
 
digitalWrite(Buzzer, LOW);
 
delay(100);
 
}
 
if (GAS_SENSE_VALUE < 500 && gas == 1) {
 
gas = 0;
 
digitalWrite(FAN, LOW);
 
}}
