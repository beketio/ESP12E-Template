#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting ROOM...");
  
  setupWifi();
  setupOta();
  setupMqtt();
  
  setupRadar();
  setupTempHumid();
  setupDoor();
}

void loop() {
  handleMqtt();
  handleOta();
  
  checkTempHumid();
  checkRadar();
  checkDoor();
}

void subscribeMQTT() {
  // Subscribe to the action topics to listen for action messages
  Serial.print("Subscribing to ");
  //Serial.print(mqtt_door1_action_topic);
  Serial.println("...");
  client.subscribe(MQTT_DOOR_ACTION_TOPIC);
}

// Callback when MQTT message is received; calls triggerDoorAction(), passing topic and payload as parameters
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  String topicToProcess = topic;
  payload[length] = '\0';
  String payloadToProcess = (char*)payload;
  triggerDoorAction(topicToProcess, payloadToProcess);
}

// Wifi setup function
void setupWifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  WiFi.hostname("KitchenESP");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(" WiFi connected - IP address: ");
  Serial.println(WiFi.localIP());
}

// MQTT
//String availabilityBase = MQTT_CLIENTID;
//String availabilitySuffix = "/availability";
//String availabilityTopicStr = availabilityBase + "/availability";
//const char* availabilityTopic = availabilityTopicStr.c_str();
const char* availabilityTopic = concatt(MQTT_CLIENTID, "/availability");
const char* birthMessage = "online";
const char* lwtMessage = "offline";

void setupMqtt() {
  //String availabilityBase = MQTT_CLIENTID;
  //strcpy(availabilityTopic, MQTT_CLIENTID);
  //strcat(availabilityTopic, "/availability");
  //String availabilitySuffix = "/availability";
  //String availabilityTopicStr = availabilityBase + "/availability";
  //availabilityTopic
  client.setServer(MQTT_BROKER, 1883);
  client.setCallback(callback);
}

// Function that publishes birthMessage
void publishBirthMessage() {
  // Publish the birthMessage
  Serial.print("Publishing birth message \"");
  Serial.print(birthMessage);
  Serial.print("\" to ");
  Serial.print(availabilityTopic);
  Serial.println("...");
  client.publish(availabilityTopic, birthMessage, true);
}

// Function that runs in loop() to connect/reconnect to the MQTT broker, and publish the current door statuses on connect
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD, availabilityTopic, 0, true, lwtMessage)) {
      Serial.println("Connected!");
      // Publish the birth message on connect/reconnect
      publishBirthMessage();
      subscribeMQTT();
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setupOta() {
  ArduinoOTA.setHostname(OTA_HOSTNAME);
  ArduinoOTA.setPort(OTA_PORT);
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(2, OUTPUT);
}

void handleMqtt() {
  // Connect/reconnect to the MQTT broker and listen for messages
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void handleOta() {
  ArduinoOTA.handle();
}

