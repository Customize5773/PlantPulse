#ifndef BLYNK_INTERFACE_H
#define BLYNK_INTERFACE_H

#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "PlantPulse Monitor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Blynk.h>

char ssid[] = "Your_SSID";
char pass[] = "Your_PASSWORD";

BlynkTimer timer;

void setupBlynk() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void pushToBlynk(int soil, float temp, float hum) {
  Blynk.virtualWrite(V0, soil);
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);
}

#endif
