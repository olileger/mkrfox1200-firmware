#ifndef _CONTROLLERAPP_H_
#define _CONTROLLERAPP_H_

/**
 * Includes. 
 */
#include <ArduinoLowPower.h>


/**
 * Main Arduino app handler.
 */
class ControllerApp
{
private:
    unsigned long   nextLoop;

    bool isTimeToRun() const;
    void setNextLoop();

public:
    ControllerApp();
    ~ControllerApp();

    void Setup();
    void Loop();
};

#endif