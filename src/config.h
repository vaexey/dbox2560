#ifndef CONFIG
#define CONFIG

#include "secrets.h"

#define SERIAL_BAUD_RATE 115200

#define ADDRESS_MAC { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }
#define ADDRESS_IP 192, 168, 1, 3
#define ADDRESS_GW 192, 168, 1, 1
#define ADDRESS_SUBNET 255, 255, 255, 0

#define MQTT_ADDRESS 192, 168, 1, 2
#define MQTT_CLIENT_ID "dbox2560"

#define MQTT_PAYLOAD_ON F("ON")
#define MQTT_PAYLOAD_OFF F("OFF")

#endif