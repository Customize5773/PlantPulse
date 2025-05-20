#include <ArduinoOTA.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// =============== Configuration Section =============== //
// Blynk Configuration
#define BLYNK_TEMPLATE_ID     "YourTemplateID"
#define BLYNK_TEMPLATE_NAME   "PlantPulse Monitor"
#define BLYNK_AUTH_TOKEN      "YourAuthToken"

// WiFi Configuration
const char* ssid     = "Your_SSID";
const char* password = "Your_PASSWORD";

// Hardware Configuration
#define DHTPIN          4
#define DHTTYPE         DHT22
#define SOIL_MOIST_PIN  34
#define UPDATE_INTERVAL 5000  // 5 seconds

// Soil Moisture Calibration (Customize based on your sensor)
const int AIR_VALUE   = 4095;  // Value in air (dry)
const int WATER_VALUE = 1200;  // Value in water (wet)
const int SOIL_SAMPLES = 5;    // Number of samples for averaging

// ================ Global Objects ================ //
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
WidgetLED pumpLed(V3);

// ================ Sensor Functions ================ //
float readTemperature() {
  float temp = dht.readTemperature();
  if (isnan(temp)) {
    Serial.println("Failed to read temperature!");
    return -999.9;
  }
  return temp;
}

float readHumidity() {
  float hum = dht.readHumidity();
  if (isnan(hum)) {
    Serial.println("Failed to read humidity!");
    return -999.9;
  }
  return hum;
}

int readSoilMoisture() {
  // Analog read with averaging
  int soilRaw = 0;
  for(int i = 0; i < SOIL_SAMPLES; i++) {
    soilRaw += analogRead(SOIL_MOIST_PIN);
    delay(10);
  }
  soilRaw /= SOIL_SAMPLES;

  // Constrain and map to percentage
  soilRaw = constrain(soilRaw, WATER_VALUE, AIR_VALUE);
  return map(soilRaw, AIR_VALUE, WATER_VALUE, 0, 100);
}

// ================ System Functions ================ //
void sendSensorData() {
  static int errorCount = 0;
  
  float temp = readTemperature();
  float hum = readHumidity();
  int soilMoisture = readSoilMoisture();

  // Validate sensor readings
  if(temp == -999.9 || hum == -999.9) {
    errorCount++;
    if(errorCount > 3) Blynk.logEvent("sensor_error");
    return;
  }
  errorCount = 0;  // Reset error counter on successful read

  // Send to Blynk
  Blynk.virtualWrite(V0, soilMoisture);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);

  // Serial output
  Serial.printf("Soil: %d%% | Temp: %.1f°C | Humidity: %.1f%%\n",
                soilMoisture, temp, hum);
}

void checkBlynkStatus() {
  static bool connected = false;
  if (Blynk.connected() != connected) {
    connected = !connected;
    Serial.println(connected ? "Blynk connected" : "Blynk disconnected");
    pumpLed.setValue(connected ? 255 : 0);
  }
}

void setupOTA() {
  ArduinoOTA.setHostname("PlantPulse-Monitor");
  ArduinoOTA
    .onStart([]() {
      String type = ArduinoOTA.getCommand() == U_FLASH ?
                    "sketch" : "filesystem";
      Serial.println("Start updating " + type);
    })
    .onEnd([]() { Serial.println("\nEnd"); })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
  ArduinoOTA.begin();
}

// ================ Main Functions ================ //
void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  
  // Initialize Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect(3000);  // Timeout 3 seconds
  
  // Setup OTA
  setupOTA();

  // Configure timer
  timer.setInterval(UPDATE_INTERVAL, sendSensorData);
  timer.setInterval(1000L, checkBlynkStatus);
}

void loop() {
  Blynk.run();
  timer.run();
  ArduinoOTA.handle();
  
  // Add non-blocking delay
  static unsigned long lastMillis = 0;
  if (millis() - lastMillis > 100) {
    lastMillis = millis();
    // Add background tasks here if needed
  }
}
