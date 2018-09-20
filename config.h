// Preprocessor string concatenator
#define concatt(first, second) first second

// Mapping NodeMCU Ports to Arduino GPIO Pins
// Allows use of NodeMCU pin names
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define RX 3 // D9
#define TX 1 // D10
#define SD2 9
#define SD3 10

// Wifi Parameters
#define WIFI_SSID "wifiSSID"
#define WIFI_PASSWORD "wifiPassword"

// Static IP Parameters
#define STATIC_IP false
#define IP 192,168,1,100
#define GATEWAY 192,168,1,1
#define SUBNET 255,255,255,0

// MQTT Parameters
#define MQTT_BROKER "192.168.1.2"
#define MQTT_CLIENTID "ROOM"
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_PORT 1883

// OTA
#define OTA_HOSTNAME "ROOM"
#define OTA_PASSWORD ""
#define OTA_PORT 8266

// Relay Parameters
#define ACTIVE_HIGH_RELAY true

// Door Parameters
#define DOOR_ALIAS "Door"
#define MQTT_DOOR_ACTION_TOPIC "ROOM/door/action"
#define DOOR_OPEN_PIN D2
#define DOOR_CLOSE_PIN D2

// Temp/Humidity Sensor Parameters
#define MQTT_TEMP_TOPIC "ROOM/temperature"
#define MQTT_HUMID_TOPIC "ROOM/humidity"

// DHT Parameters
#define DHT_PIN D1
#define DHT_TYPE DHT22
#define DHT_CHECK_DELAY 2000
#define DHT_USE_F true

// Radar Sensor
#define MQTT_ACTIVE_MOTION_TOPIC "ROOM/motion"
#define MQTT_MOTION_TOPIC "ROOM/motion"
#define MQTT_MOTION_OFF "off"
#define MQTT_MOTION_ON "on"
#define RADAR_PIN D2
#define RADAR_TIMEOUT 60000 //60 seconds
#define RADAR_REPORT_INTERVAL 5000 //5 seconds
#define RADAR_REPORT_MAX 1800000 //30 minutes

// Load Sensor
#define MQTT_WEIGHT_TOPIC "ROOM/weight"
#define LOAD_PIN D1
#define LOAD_CLOCK_PIN D2
#define LOAD_SENSOR_2 true
#define LOAD_PIN_2 D3
#define LOAD_CLOCK_PIN_2 D4




// Trip Sensor
#define TRIP_1_PIN D0
#define TRIP_2_PIN D0
#define TRIP_MIN_VAL 0

// Trip Matrix
#define TRIP_MATRIX_SIZE 3
#define TRIP_ON_WAIT 20
#define TRIP_OFF_WAIT 20
#define TRIP_MATRIX_PIN_1 D1
#define TRIP_MATRIX_PIN_2 D2
#define TRIP_MATRIX_PIN_3 D3




