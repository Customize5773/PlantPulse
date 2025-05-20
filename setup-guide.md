# 🛠️ Setup Guide for PlantPulse: Smart Indoor Plant Monitoring System

This document provides step-by-step guidance to assemble, wire, and configure the PlantPulse system. By the end of this guide, you will have a fully functional indoor plant monitoring system capable of tracking soil moisture, temperature, and humidity, with real-time data sent to your Blynk IoT dashboard.

---

## 📦 Hardware Components

| No. | Component                        | Quantity | Estimated Cost (USD) | Notes |
|-----|----------------------------------|----------|------------------------|-------|
| 1   | ESP32 Dev Module                 | 1        | $6–$10                 | Wi-Fi capable MCU for cloud communication |
| 2   | Capacitive Soil Moisture Sensor | 1        | $3–$5                  | Better durability than resistive sensors |
| 3   | DHT22 Temperature & Humidity Sensor | 1     | $4–$6                  | Higher precision than DHT11 |
| 4   | Breadboard (Half-size)           | 1        | $3                     | For prototyping connections |
| 5   | USB Micro/Type-C Cable           | 1        | $2                     | For powering and programming ESP32 |
| 6   | Jumper Wires (Male-to-Male)      | ~15      | $2                     | For breadboard connections |
| 7   | 5V Power Adapter (optional)      | 1        | $5                     | For standalone operation (optional) |

**💰 Total Estimated Cost:** ~$25–$30 USD (excluding optional modules)

---

## 🧩 Assembly Overview

The system involves connecting environmental sensors to the ESP32 board and uploading firmware to handle data acquisition and transmission via Blynk Cloud.

---

## 🔌 Wiring Instructions

### ⚙️ Pin Mapping

| Module                 | Signal        | ESP32 Pin | Notes                                 |
|------------------------|---------------|-----------|----------------------------------------|
| Soil Moisture Sensor   | AOUT (analog) | GPIO 34   | ESP32 ADC input (adjustable)           |
|                        | VCC           | 3.3V      | Power supply                           |
|                        | GND           | GND       | Ground connection                      |
| DHT22 Sensor           | Data          | GPIO 4    | Digital data pin (can be changed)      |
|                        | VCC           | 3.3V/5V   | Preferably 3.3V for ESP32 safety        |
|                        | GND           | GND       | Ground connection                      |

> ⚠️ **Important:** ESP32 has multiple ADC and digital input pins. You may modify pin assignments in the code if needed, but avoid using pins like GPIO0, GPIO2, and GPIO15 unless you're certain.

---

## 🧪 Sensor Calibration Notes

### Soil Moisture Calibration:
1. Open Serial Monitor and note raw analog values for:
   - **Dry soil**: ~4095
   - **Fully wet soil**: ~1200
2. Update the `map()` function in `soil_sensor.h` accordingly:
   ```cpp
   int moisturePercent = map(raw, 4095, 1200, 0, 100); // Adjust as needed
   ```

---

## 💻 Software Configuration Steps

1. **Install Arduino IDE**

   * [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

2. **Install ESP32 Board Support**

   * In Arduino IDE:

     * Go to **File → Preferences**
     * Add this to "Additional Boards Manager URLs":

       ```
       https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
       ```
     * Then go to **Tools → Board → Boards Manager** and search "ESP32" → Install

3. **Install Required Libraries**
   In **Library Manager**, install:

   * `Blynk` (for Blynk IoT)
   * `DHT sensor library by Adafruit`
   * `Adafruit Unified Sensor`

4. **Configure Code**

   * Open `src/main.ino` and edit:

     ```cpp
     char ssid[] = "Your_SSID";
     char pass[] = "Your_PASSWORD";
     #define BLYNK_AUTH_TOKEN "Your_Blynk_Auth_Token"
     #define BLYNK_TEMPLATE_ID "Your_Template_ID"
     #define BLYNK_TEMPLATE_NAME "Your_Template_Name"
     ```

5. **Upload Code**

   * Select `ESP32 Dev Module` as your board.
   * Choose the correct COM port.
   * Click **Upload**.

6. **Verify Data on Blynk App**

   * Open the mobile app.
   * You should see live readings from your device.
   * Add `Gauge`, `Label`, or `History Graph` widgets and link to:

     * `V0`: Soil Moisture
     * `V1`: Temperature
     * `V2`: Humidity

---

## ✅ Troubleshooting

| Symptom                    | Possible Cause              | Solution                                     |
| -------------------------- | --------------------------- | -------------------------------------------- |
| No data on Blynk dashboard | Wi-Fi or token error        | Check `ssid`, `pass`, and `BLYNK_AUTH_TOKEN` |
| DHT22 returns `nan` or `0` | Loose wiring or power issue | Ensure 3.3V/5V supply and firm wiring        |
| Soil sensor gives 0/1023   | Wrong pin or shorted sensor | Check pin assignment & wiring                |

---

## 🧠 Tips

* Always test sensors individually before full integration.
* Use `Serial.println()` for debugging sensor values.
* ESP32 can tolerate 3.3V on analog inputs—avoid feeding 5V into ADC pins directly.

---

## 📎 References

* [Blynk IoT Documentation](https://docs.blynk.io)
* [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
* [Capacitive Soil Sensor Wiki](https://wiki.dfrobot.com/Capacitive_Soil_Moisture_Sensor_SKU_SEN0193)
