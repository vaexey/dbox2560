#include "Arduino.h"
#include <MQTTClient.h>

class binput
{
public:
    String topic;

    int pin;
    bool inverted;
    bool pullup;
    int minimum_time;

    binput(MQTTClient *mqtt, String topic, int pin, bool inverted, bool pullup, int minimum_time);

    void setup();
    void loop();

private:
    MQTTClient *mqtt;

    bool last_state;
    bool pending_state;
    unsigned long change_time;
    bool pending_change;

};