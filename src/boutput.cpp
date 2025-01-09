#include "boutput.h"
#include "config.h"

boutput::boutput(MQTTClient *mqtt, String topic, int pin, bool inverted, bool start_state)
    : mqtt(mqtt), topic(topic), pin(pin), inverted(inverted), start_state(start_state)
{
    state = start_state;
    push_update = true;

    set_topic = topic + "/set";
}

void boutput::setup()
{
    if(start_state ^ inverted)
    {
        digitalWrite(pin, HIGH);
    }

    pinMode(pin, OUTPUT);
    digitalWrite(pin, start_state ^ inverted);

    mqtt->subscribe(set_topic);
}

void boutput::loop()
{
    if(push_update)
    {
        Serial.print("Push state ");
        Serial.print(topic);
        Serial.print(" to ");
        Serial.println(state);

        if(state)
        {
            mqtt->publish(topic, MQTT_PAYLOAD_ON);
        } else {
            mqtt->publish(topic, MQTT_PAYLOAD_OFF);
        }

        push_update = false;
    }
}

void boutput::message(String &payload)
{
    if(payload.equalsIgnoreCase(MQTT_PAYLOAD_ON))
    {
        state = true;
        push_update = true;
        digitalWrite(pin, state ^ inverted);

        return;
    }

    if(payload.equalsIgnoreCase(MQTT_PAYLOAD_OFF))
    {
        state = false;
        push_update = true;
        digitalWrite(pin, state ^ inverted);

        return;
    }

    Serial.print("Malformed payload for ");
    Serial.print(topic);
    Serial.print(": \"");
    Serial.print(payload);
    Serial.println("\"");
}