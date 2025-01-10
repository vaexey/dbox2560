#include <MQTTClient.h>
#include "binput.h"
#include "boutput.h"

extern MQTTClient mqtt;

#define NEW(pin, topic) binput(&mqtt, "dbox2560/" topic, pin, true, true, 50)
binput binputs[] = {
    NEW(26, "A1"), // Beta Main Bottom
    NEW(27, "A2"),
    NEW(28, "A3"),
    NEW(29, "A4"),

    NEW(30, "B1"),
    NEW(31, "B2"),
    NEW(32, "B3"),
    NEW(33, "B4"),

    NEW(34, "C1"),
    NEW(35, "C2"),
    NEW(36, "C3"),
    NEW(37, "C4"),

    NEW(38, "D1"),
    NEW(39, "D2"),
    NEW(40, "D3"),
    NEW(41, "D4"),

    NEW(42, "R1U"),
    NEW(43, "R1D"),

    NEW(44, "R2U"),
    NEW(45, "R2D"),
};
#undef NEW

#define NEW(topic, pin) boutput(&mqtt, topic, pin, true, false)
boutput boutputs[] = {
    NEW("dbox2560/onboard_led", 13),

    NEW("dbox2560/LL", 18),
    NEW("dbox2560/LP", 19),

    NEW("dbox2560/R1", 20),
    NEW("dbox2560/R1D", 21),
    NEW("dbox2560/R2", 22),
    NEW("dbox2560/R2D", 17),
    NEW("dbox2560/R3", 24),
    NEW("dbox2560/R3D", 25)
};
#undef NEW