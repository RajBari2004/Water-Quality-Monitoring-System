/*
  Water Quality Monitoring System
  --------------------------------
  Measures:
  - Temperature (DS18B20)
  - Total Dissolved Solids (TDS)
  - Turbidity (NTU)

  Hardware:
  - Arduino UNO
  - DS18B20 Temperature Sensor
  - TDS Sensor
  - Turbidity Sensor
  - 16x2 LCD (I2C)

  Author: Raj B
  Update Interval: 3 seconds
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// -------- LCD --------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------- Pins --------
#define ONE_WIRE_BUS 2
#define TDS_PIN A0
#define TURBIDITY_PIN A1

// -------- Sensors --------
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// -------- Variables --------
float temperature = 0;
float tdsValue = 0;
float turbidityValue = 0;
String waterQuality = "";

// -------- Average Reading Function --------
int getAverageReading(int pin) {

  long total = 0;

  for (int i = 0; i < 10; i++) {
    total += analogRead(pin);
    delay(5);
  }

  return total / 10;
}

// -------- Setup --------
void setup() {

  Serial.begin(9600);

  sensors.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Water Monitor");

  lcd.setCursor(0,1);
  lcd.print("System Ready");

  delay(2000);
  lcd.clear();
}

// -------- Main Loop --------
void loop() {

  readTemperature();
  readTDS();
  readTurbidity();
  classifyWater();

  displayPage1();
  delay(3000);

  displayPage2();
  delay(3000);

  printSerialData();
}

// -------- Temperature --------
void readTemperature() {

  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  if (temperature == -127) {
    Serial.println("Temperature sensor error");
    temperature = 0;
  }
}

// -------- TDS --------
void readTDS() {

  int tdsRaw = getAverageReading(TDS_PIN);

  float voltage = tdsRaw * (5.0 / 1023.0);

  // Temperature compensation
  float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
  float compensationVoltage = voltage / compensationCoefficient;

  tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage
            - 255.86 * compensationVoltage * compensationVoltage
            + 857.39 * compensationVoltage) * 0.5;

  if (tdsValue < 0) tdsValue = 0;
  if (tdsValue > 2000) tdsValue = 2000;
}

// -------- Turbidity --------
void readTurbidity() {

  int turbRaw = getAverageReading(TURBIDITY_PIN);

  float turbVoltage = turbRaw * (5.0 / 1023.0);

  turbidityValue = -1120.4 * turbVoltage * turbVoltage
                   + 5742.3 * turbVoltage
                   - 4352.9;

  if (turbidityValue < 0) turbidityValue = 0;
  if (turbidityValue > 3000) turbidityValue = 3000;
}

// -------- Water Classification --------
void classifyWater() {

  if (tdsValue < 300 && turbidityValue < 2)
    waterQuality = "Excellent";
  else if (tdsValue < 500 && turbidityValue < 5)
    waterQuality = "Good";
  else if (tdsValue < 1000)
    waterQuality = "Poor";
  else
    waterQuality = "Unsafe";
}

// -------- LCD Page 1 --------
void displayPage1() {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0,1);
  lcd.print("TDS:");
  lcd.print(tdsValue);
  lcd.print("ppm");
}

// -------- LCD Page 2 --------
void displayPage2() {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Turb:");
  lcd.print(turbidityValue);
  lcd.print("NTU");

  lcd.setCursor(0,1);
  lcd.print(waterQuality);
}

// -------- Serial Output --------
void printSerialData() {

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | ");

  Serial.print("TDS: ");
  Serial.print(tdsValue);
  Serial.print(" ppm | ");

  Serial.print("Turbidity: ");
  Serial.print(turbidityValue);
  Serial.print(" NTU | ");

  Serial.print("Water Quality: ");
  Serial.println(waterQuality);
}
