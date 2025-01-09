#include "Arduino.h"

class timeout
{
private:
    unsigned long time;
    int defaultMs;

public:
    timeout(int ms);
    
    void now();
    void never();
    void set();
    void set(int ms);
    bool check();
    bool checkOrSet();
    bool checkOrSet(int ms);
};