# 🌱 PlantPulse: Smart Indoor Plant Monitoring System

**PlantPulse** is a modular, IoT-enabled Arduino-based system for real-time monitoring of indoor plant health. It provides continuous data collection and cloud integration to track **soil moisture**, **temperature**, and **humidity**, with a remote dashboard powered by **Blynk IoT**.

---

## 📸 Project Overview

Indoor plants play a vital role in enhancing air quality, regulating humidity, and improving indoor aesthetics and well-being. However, maintaining optimal environmental conditions—such as adequate soil moisture, temperature, and humidity—can be challenging due to variability in indoor climates and user oversight.

PlantPulse addresses this challenge by implementing a smart, sensor-driven monitoring system capable of continuously tracking key environmental parameters critical to plant health. The system leverages a Wi-Fi-enabled microcontroller (ESP32) to interface with multiple environmental sensors, including a capacitive soil moisture sensor, a DHT22 temperature and humidity sensor, and optionally a light sensor for luminance monitoring.

Sensor data is acquired in real time and processed by the ESP32. This data is then transmitted to a cloud-based IoT platform (Blynk) over Wi-Fi, enabling users to access a remote dashboard via a mobile application or web interface. The dashboard provides visual feedback, historical graphing, and the ability to set thresholds for critical parameters.

The PlantPulse system promotes proactive plant care by:
- Providing real-time monitoring and alerts when environmental conditions deviate from plant-healthy ranges.
- Enabling data-driven decisions through historical tracking of environmental trends.
- Supporting modular extensibility, allowing the integration of additional sensors, actuators (e.g., automated watering), and data services (e.g., cloud logging).

By combining embedded sensing, wireless communication, and cloud-based visualization, PlantPulse serves as a practical and scalable solution for precision indoor horticulture, home automation, and environmental monitoring. It is especially relevant in the contexts of smart homes, urban gardening, and sustainable living initiatives.

---

## 📦 Features

- 🌡️ Temperature and humidity monitoring (DHT22)
- 💧 Soil moisture sensing (capacitive sensor)
- 📲 Real-time IoT dashboard (via Blynk)
- 🛠️ Modular and extensible code architecture
- 🔔 Alert-ready design (notifications, LEDs, buzzers)
- 📊 Cloud data logging and visualization (via Blynk History Graphs)

---

## ⚙️ Hardware Requirements

| Component                  | Description                                                   |
|---------------------------|---------------------------------------------------------------|
| **ESP32 Dev Board**       | Microcontroller with Wi-Fi for IoT connectivity               |
| **DHT22 Sensor**          | Temperature and humidity sensor                               |
| **Capacitive Soil Sensor**| More accurate and corrosion-resistant than resistive types    |
| **Breadboard & Jumper Wires** | For circuit prototyping                                 |
| **USB Cable**             | For programming the ESP32                                     |
| **Power Adapter (5V)**    | For continuous operation                                      |

Optional:
- **BH1750 or LDR** for light intensity monitoring
- **Buzzer / RGB LED** for local alerts
- **I2C LCD (16x2)** for on-device display

---

## 🧠 System Architecture

```plaintext
Sensors ──> ESP32 ──> Blynk Cloud ──> Mobile Dashboard
                │
        [Modular Sensor Code]
```

---

![System Architecture](https://github.com/user-attachments/assets/09677f21-1fa6-4db0-b8b9-aea9f5188b04)

---

## 🛠️ Setup Instructions

### 1. 📲 Blynk IoT Setup

1. Go to [https://blynk.cloud](https://blynk.cloud) and create a new account.
2. Create a **new Template**:

   * Name: `PlantPulse Monitor`
   * Hardware: `ESP32 Dev Board`
   * Connection: `WiFi`
3. Create **Datastreams**:

   * V0 → Soil Moisture (Integer)
   * V1 → Temperature (Float)
   * V2 → Humidity (Float)
4. Deploy to a **new device** and copy the:

   * `BLYNK_TEMPLATE_ID`
   * `BLYNK_TEMPLATE_NAME`
   * `AUTH_TOKEN`

### 2. 🧰 Arduino Setup

* Install the following libraries using the Arduino Library Manager:

  * `Blynk` (Blynk IoT v1.1.0+)
  * `DHT sensor library by Adafruit`
  * `Adafruit Unified Sensor`
* Set the board to **ESP32 Dev Module**

### 3. 🧾 Code Configuration

In `blynk_interface.h`, update:

```cpp
#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "PlantPulse Monitor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";
```

---

## 🧪 Sensor Calibration

### Soil Moisture Calibration:

Adjust `map()` in `soil_sensor.h` using your sensor's dry/wet readings:

```cpp
int moisturePercent = map(raw, 4095, 1200, 0, 100); // Adjust as needed
```

Use `Serial.println(analogRead(SOIL_PIN))` to get raw values.

---

## 📲 Mobile Dashboard Design (Blynk App)

* Add **Gauge Widgets** or **Labels**
* Bind to:

  * V0 → Soil Moisture
  * V1 → Temperature
  * V2 → Humidity
* Use **History Graph** or **Notification Widget** as needed

---

## 🧩 Extending the Project

| Feature       | Add-On Module            | Description                                 |
| ------------- | ------------------------ | ------------------------------------------- |
| Light sensing | `light_sensor.h`         | Monitor ambient light (BH1750 or LDR)       |
| Alerts        | `alert_module.h`         | Add buzzer/LED when thresholds are exceeded |
| Data logging  | Firebase / Google Sheets | Store readings to external database         |
| Display       | LCD Module (I2C)         | Show readings on a local display            |

---

## 📸 Screenshots

| Dashboard Example                             | Circuit Diagram                        |
| --------------------------------------------- | -------------------------------------- |
| ![Dashboard](https://tutorials-raspberrypi.com/wp-content/uploads/Smart-Agriculture-System-Dashboard.webp) | Coming soon |

---

## 📄 License

This project is licensed under the MIT License.

---

## 🤝 Contributing

Contributions are welcome! Feel free to fork this repository, improve it, and open a pull request. Suggestions for new modules and integrations are highly encouraged.

---

## 🔗 Useful Links

* [Blynk Cloud](https://blynk.cloud)
* [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
* [Capacitive Soil Sensor Guide](https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193)
* [DHT22 Datasheet](https://www.adafruit.com/product/385)
