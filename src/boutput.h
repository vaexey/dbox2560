#include "Arduino.h"
#include <MQTTClient.h>

class boutput
{
public:
    String topic;
    String set_topic;

    int pin;
    bool inverted;
    bool start_state;

    boutput(MQTTClient *mqtt, String topic, int pin, bool inverted, bool start_state);

    void setup();
    void loop();
    void message(String &payload);

private:
    MQTTClient *mqtt;
    bool state;
    
    bool push_update;
};