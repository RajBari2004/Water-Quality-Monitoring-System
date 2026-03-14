# 💧 Water Quality Monitoring System

🚰 **Smart Arduino-based system for monitoring water quality in real time.**

This project measures **Temperature**, **Total Dissolved Solids (TDS)**, and **Turbidity** using sensors connected to an Arduino.
The system analyzes these parameters and determines whether the water quality is **Excellent, Good, Poor, or Unsafe**.

Sensor data is displayed on a **16x2 I2C LCD** and updated every few seconds.

---

# 📊 Parameters Monitored

| Parameter      | Sensor           | Description                         |
| -------------- | ---------------- | ----------------------------------- |
| 🌡 Temperature | DS18B20          | Measures water temperature          |
| 💧 TDS         | TDS Sensor       | Indicates dissolved solids in water |
| 🌫 Turbidity   | Turbidity Sensor | Measures water clarity              |

---

# 🧠 Features

✅ Real-time water monitoring
✅ Temperature compensation for TDS accuracy
✅ Noise filtering for stable sensor readings
✅ Automatic water quality classification
✅ LCD display output
✅ Serial monitor data logging
✅ Modular and clean embedded code

---

# 🛠 Hardware Used

* 🔹 Arduino UNO
* 🔹 DS18B20 Temperature Sensor
* 🔹 TDS Sensor
* 🔹 Turbidity Sensor
* 🔹 16x2 LCD Display (I2C)
* 🔹 Connecting wires & breadboard

---

# 🔌 Circuit Connections

### DS18B20 Temperature Sensor

VCC → 5V
GND → GND
DATA → D2

### TDS Sensor

VCC → 5V
GND → GND
AOUT → A0

### Turbidity Sensor

VCC → 5V
GND → GND
AOUT → A1

### LCD (I2C)

VCC → 5V
GND → GND
SDA → A4
SCL → A5

---

# 📟 Example Output

LCD Display:

Temp: 25.6 C
TDS: 340 ppm

Turb: 2.1 NTU
Water: Good

Serial Monitor:

Temp: 25.6 C | TDS: 340 ppm | Turbidity: 2.1 NTU | Water Quality: Good

---

# 📂 Project Structure

Water-Quality-Monitoring-System
│
├── WaterQualityMonitor.ino
├── README.md
├── circuit_diagram.png
└── .gitignore

---

# 📸 Project Images

Add images of your project here.

Example:

/images

* circuit.jpg
* lcd_output.jpg
* prototype.jpg

---

# 🚀 Future Improvements

📡 IoT cloud monitoring
📱 Mobile app dashboard
⚠ Water quality alert system
🌍 Smart environmental monitoring

---

Embedded Systems & IoT Enthusiast

---


