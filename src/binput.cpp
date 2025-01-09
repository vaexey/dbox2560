#include "binput.h"
#include "config.h"

binput::binput(MQTTClient *mqtt, String topic, int pin, bool inverted, bool pullup, int minimum_time)
    : mqtt(mqtt), topic(topic), pin(pin), inverted(inverted), pullup(pullup), minimum_time(minimum_time)
{
    last_state = inverted;
    pending_state = inverted;
    pending_change = false;
    change_time = 0;
}

void binput::setup()
{
    if(pullup)
    {
        pinMode(pin, INPUT_PULLUP);
    } else {
        pinMode(pin, INPUT);
    }

    mqtt->publish(topic, MQTT_PAYLOAD_OFF);
}

void binput::loop()
{
    bool state = digitalRead(pin) ^ inverted;

    bool changed = state != last_state;

    if(changed)
    {
        if(pending_change)
        {
            if(pending_state != state)
            {
                pending_change = false;
            }
        }
        else
        {
            pending_state = state;
            pending_change = true;
        }

        last_state = state;
        change_time = millis() + minimum_time;
    }

    if(pending_change)
    {
        if(millis() > change_time)
        {
            pending_change = false;

            Serial.print("Trigger ");
            Serial.print(topic);
            Serial.print(" ");
            Serial.println(pending_state);

            if(pending_state)
            {
                mqtt->publish(topic, MQTT_PAYLOAD_ON);
            } else {
                mqtt->publish(topic, MQTT_PAYLOAD_OFF);
            }
        }
    }
}
