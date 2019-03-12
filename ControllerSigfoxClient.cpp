/**
 * Includes.
 */
#include "ControllerSigfoxClient.h"
#include <SigFox.h>
#include "HelperLog.h"


/**
 * Constants.
 */
#define B_0000    0x00
#define B_0001    0x01
#define B_0010    0x02
#define B_0011    0x03
#define B_0100    0x04
#define B_0101    0x05
#define B_0110    0x06
#define B_0111    0x07
#define B_1000    0x08
#define B_1001    0x09
#define B_1010    0x0a
#define B_1011    0x0b
#define B_1100    0x0c
#define B_1101    0x0d
#define B_1110    0x0e
#define B_1111    0x0f


/**
 * Constructor.
 */
ControllerSigfoxClient::ControllerSigfoxClient()
{

}

/**
 * Destructor.
 */
ControllerSigfoxClient::~ControllerSigfoxClient()
{

}

/**
 * Begin the Sigfox usage.
 */
bool ControllerSigfoxClient::begin()
{
    if (!SigFox.begin())
    {
        HelperLog::LogError("[SIGFOX] Shield error or not present !");
        return false;
    }

    return true;
}

/**
 * Close the Sigfox usage.
 */
void ControllerSigfoxClient::end()
{
    SigFox.end();
}

/**
 * Send a String message to the Sigfox backend.
 */
void ControllerSigfoxClient::sendString(String s)
{
    HelperLog::LogInfo("[SIGFOX] Sending : " + s);

    SigFox.beginPacket();
    SigFox.print(s);
    SigFox.endPacket();
    
    ControllerSigfoxClient::LogAtmelStatus();
    ControllerSigfoxClient::LogSigfoxStatus();
}

/**
 * Display the board configuration to the log.
 */
void ControllerSigfoxClient::DisplayBoardInformations()
{
    if (!ControllerSigfoxClient::begin())
    {
        return;
    }

    HelperLog::LogInfo("[SIGFOX] ATMEL version : " + SigFox.AtmVersion());
    HelperLog::LogInfo("[SIGFOX] SIGFOX Version : " + SigFox.SigVersion());
    HelperLog::LogInfo("[SIGFOX] ID : " + SigFox.ID());
    HelperLog::LogInfo("[SIGFOX] PAC : " + SigFox.PAC());
    HelperLog::LogInfo("[SIGFOX] T : " + String(SigFox.internalTemperature()));

    ControllerSigfoxClient::end();
}

/**
 * Log the ATMEL board status.
 */
void ControllerSigfoxClient::LogAtmelStatus()
{
    int status = SigFox.statusCode(ATMEL);

    String str = String("PA ") + ((status & B_0001) ? "on" : "off");
    status = status >> 1;

    if (status & B_0001)
    {
        str += "; CMD error or not supported";
    }
    if (status & B_0010)
    {
        str += "; Generic error";
    }
    if (status & B_0011)
    {
        str += "; Frequency error";
    }
    if (status & B_0100)
    {
        str += "; Usage error";
    }
    if (status & B_0101)
    {
        str += "; Openning error";
    }
    if (status & B_0110)
    {
        str += "; Closing error";
    }
    if (status & B_0111)
    {
        str += "; Send error";
    }
    status = status >> 4;

    str += (status & B_0001) ? "; Frame sent" : "";
    status = status >> 1;

    str += (status & B_0001) ? "; System ready" : "; System NOT ready";

    HelperLog::LogInfo("[SIGFOX] ATMEL status : " + str);
}

/**
 * Log the SigFox modem status.
 */
void ControllerSigfoxClient::LogSigfoxStatus()
{
    int status = SigFox.statusCode(SIGFOX);
    String str;

    switch (SigFox.statusCode(SIGFOX))
    {
        case 0x00:
            str = "No error";
            break;
        case 0x01:
            str = "Manufacturer error";
            break;
        case 0x02:
            str = "ID or key error";
            break;
        case 0x03:
            str = "State machine error";
            break;
        case 0x04:
            str = "Frame size error";
            break;
        case 0x05:
            str = "Manufacturer send error";
            break;
        case 0x06:
            str = "Get voltage/temperature error";
            break;
        case 0x07:
            str = "Close issues encountered";
            break;
        case 0x08:
            str = "API error indication";
            break;
        case 0x09:
            str = "Error getting PN9";
            break;
        case 0x0A:
            str = "Error getting frequency";
            break;
        case 0x0B:
            str = "Error building frame";
            break;
        case 0x0C:
            str = "Error in delay routine";
            break;
        case 0x0D:
            str = "callback causes error";
            break;
        case 0x0E:
            str = "timing error";
            break;
        case 0x0F:
            str = "frequency error";
            break;
        default:
            str = "Don't know (" + String(status) + ")";
            break;
    }

    HelperLog::LogInfo("[SIGFOX] SIGFOX status : " + str);
}

/**
 * Send the internal temperature to the Sigfox backend.
 */
void ControllerSigfoxClient::SendInternalTemperature()
{
    if (!ControllerSigfoxClient::begin())
    {
        return;
    }
    ControllerSigfoxClient::sendString(String(SigFox.internalTemperature()));
    ControllerSigfoxClient::end();
}

/**
 * Activate / Deactivate the debug on the board.
 */
void ControllerSigfoxClient::WithDebug(bool b)
{
    if (b)
    {
        SigFox.debug();
    }
    else
    {
        SigFox.noDebug();
    }
}