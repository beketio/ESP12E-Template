// Motion
int radar_val;
unsigned long firstTimeMotion = 0;
unsigned long lastTimeMotion = 0;
int motionDiff;
int publishedMotionDiff;

void setupRadar() {
  pinMode(RADAR_PIN, INPUT);
  digitalWrite(D4, HIGH);
}

void checkRadar() {
    // Check Motion
  radar_val = analogRead(RADAR_PIN);
  if (radar_val > 50 && lastTimeMotion == 0) {
    client.publish(MQTT_MOTION_TOPIC, MQTT_MOTION_ON, false);
    digitalWrite(D4, LOW);
    lastTimeMotion = millis();
  }
  else if (radar_val > 50) {
    lastTimeMotion = millis();
  }
  else if (lastTimeMotion > 0 && millis() - lastTimeMotion >= RADAR_TIMEOUT) {
    client.publish(MQTT_MOTION_TOPIC, MQTT_MOTION_OFF, true);
    digitalWrite(D4, HIGH);
    lastTimeMotion = 0;
  }
}
