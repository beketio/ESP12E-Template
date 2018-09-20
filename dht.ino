#include "DHT.h"

// Temp and Humid
DHT dht(DHT_PIN, DHT_TYPE);
unsigned long lastTimeTemp;

void setupTempHumid() {
  pinMode(DHT_PIN, INPUT);
}

void checkTempHumid() {
  if (millis() - lastTimeTemp >= DHT_CHECK_DELAY) {
    lastTimeTemp = millis();
    float humid = dht.readHumidity();
    float temp = dht.readTemperature(DHT_USE_F);
    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" *F\t");
    if (!isnan(temp)) {
      char buf[6];
      sprintf(buf, "%f", temp);
      client.publish(MQTT_TEMP_TOPIC, buf, true);
      sprintf(buf, "%f", humid);
      client.publish(MQTT_HUMID_TOPIC, buf, true);
    }
  }
}
