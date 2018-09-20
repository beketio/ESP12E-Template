// Relay
const int relayActiveTime = 500;
unsigned long door1_lastSwitchTime = 0;
int debounceTime = 2000;

void setupDoor() {
  pinMode(DOOR_OPEN_PIN, OUTPUT);
}

void checkDoor() {
    
}

void triggerDoorAction(String requestedDoor, String requestedAction) {
  if (requestedDoor == MQTT_DOOR_ACTION_TOPIC && requestedAction == "OPEN") {
    Serial.print("Triggering ");
    Serial.print(DOOR_ALIAS);
    Serial.println(" OPEN relay!");
    toggleRelay(DOOR_OPEN_PIN);
  }
  else if (requestedDoor == MQTT_DOOR_ACTION_TOPIC && requestedAction == "CLOSE") {
    Serial.print("Triggering ");
    Serial.print(DOOR_ALIAS);
    Serial.println(" CLOSE relay!");
    toggleRelay(DOOR_CLOSE_PIN);
  }
  else if (requestedDoor == MQTT_DOOR_ACTION_TOPIC && requestedAction == "STATE") {
    Serial.print("Publishing on-demand status update for ");
    Serial.print(DOOR_ALIAS);
    Serial.println("!");
    publishBirthMessage();
  }
  else {
    Serial.println("Unrecognized action payload... taking no action!");
  }
}

void toggleRelay(int pin) {
  if (ACTIVE_HIGH_RELAY) {
    digitalWrite(pin, HIGH);
    delay(relayActiveTime);
    digitalWrite(pin, LOW);
  }
  else {
    digitalWrite(pin, LOW);
    delay(relayActiveTime);
    digitalWrite(pin, HIGH);
  }
}
