#include <MQTTClient.h>
#include "binput.h"
#include "boutput.h"

extern MQTTClient mqtt;

#define NEW(pin, topic) binput(&mqtt, "dbox2560/" topic, pin, true, true, 50)
binput binputs[] = {
};
#undef NEW

#define NEW(topic, pin) boutput(&mqtt, topic, pin, true, false)
boutput boutputs[] = {
    NEW("dbox2560/onboard_led", 13),
};
#undef NEW