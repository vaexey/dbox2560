#include "timeout.h"

timeout::timeout(int ms)
{
    defaultMs = ms;

    set(ms);
}

void timeout::now()
{
    time = millis() - 1;
}

void timeout::never()
{
    time = __LONG_MAX__;
}

void timeout::set()
{
    set(defaultMs);
}

void timeout::set(int ms)
{
    time = millis() + ms;
}

bool timeout::check()
{
    return millis() > time;
}

bool timeout::checkOrSet()
{
    return checkOrSet(defaultMs);
}

bool timeout::checkOrSet(int ms)
{
    if(millis() > time)
    {
        set(ms);
        
        return true;
    }

    return false;
}