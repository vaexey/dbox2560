#include <Arduino.h>
#include <Ethernet.h>
#include <MQTT.h>
#include "timeout.h"
#include "config.h"
#include "init.h"

uint8_t mac[] = ADDRESS_MAC;
IPAddress ip(ADDRESS_IP);
IPAddress gateway(ADDRESS_GW);
IPAddress dns(ADDRESS_GW);
IPAddress subnet(ADDRESS_SUBNET);
IPAddress mqtt_ip(MQTT_ADDRESS);

EthernetClient eth;
MQTTClient mqtt;

timeout mqtt_connect_timer(5000);

int binput_count = sizeof(binputs) / sizeof(binput);
int boutput_count = sizeof(boutputs) / sizeof(boutput);

void mqtt_on_message(String &topic, String &payload);
void mqtt_try_connect();

void setup() {
  // Start debug console
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Booting dbox2560...");

  // Setup eth & mqtt
  Ethernet.begin(mac, ip, dns, gateway, subnet);
  Serial.println("Ethernet started");
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());

  if(Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("WARN: Ethernet module could not be accessed");
  }

  if(Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println("WARN: No ethernet connection");
  }
  
  mqtt.begin(mqtt_ip, eth);
  mqtt.onMessage(mqtt_on_message);
  Serial.println("MQTT started");

  mqtt_connect_timer.now();
  mqtt_try_connect();

  // Setup pins
  Serial.print("Setting up ");
  Serial.print(binput_count + boutput_count);
  Serial.println(" I/O nodes...");

  for(int i = 0; i < binput_count; i++)
    binputs[i].setup();
  for(int i = 0; i < boutput_count; i++)
    boutputs[i].setup();

  Serial.println("Boot complete");
}

void mqtt_on_connect()
{
  Serial.println("Subscribing to output topics...");
}

void mqtt_try_connect()
{
  Serial.println("MQTT (re)connecting...");

  for(int i = 0; i < 2; i++)
  {
    if(mqtt.connect(MQTT_CLIENT_ID, SECRET_MQTT_USERNAME, SECRET_MQTT_PASSWORD))
    {
      Serial.println("OK");

      mqtt_on_connect();

      return;
    }

    Serial.print(".");
    delay(300);
  }
  
  Serial.print("FAILED (");
  Serial.print(mqtt.lastError());
  Serial.println(")");
}

void mqtt_on_message(String &topic, String &payload)
{
  Serial.print("Received message to \"");
  Serial.print(topic);
  Serial.print("\": \"");
  Serial.print(payload);
  Serial.println("\"");

  for(int i = 0; i < boutput_count; i++)
  {
    if(boutputs[i].set_topic == topic)
    {
      boutputs[i].message(payload);

      return;
    }
  }

  Serial.println("Could not find matching node");
}

void loop() {
  delay(1);

  if(mqtt.connected())
  {
    mqtt.loop();
  }
  else
  {
    if(mqtt_connect_timer.checkOrSet())
    {
      mqtt_try_connect();
    }
  }

  if(!mqtt.connected())
  {
    return;
  }

  for(int i = 0; i < binput_count; i++)
    binputs[i].loop();
  for(int i = 0; i < boutput_count; i++)
    boutputs[i].loop();
}