#ifndef _CONTROLLERSIGFOXCLIENT_H_
#define _CONTROLLERSIGFOXCLIENT_H_

/**
 * Includes.
 */
#include <ArduinoLowPower.h>


/**
 * Controller : Sigfox client.
 */
class ControllerSigfoxClient
{
private:
    ControllerSigfoxClient();

    static bool begin();
    static void end();
    static void sendString(String s);
    
public:
    ~ControllerSigfoxClient();
    
    static void DisplayBoardInformations();
    static void LogAtmelStatus();
    static void LogSigfoxStatus();
    static void SendInternalTemperature();
    static void WithDebug(bool b);
};

#endif