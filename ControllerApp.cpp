/**
 * Includes. 
 */
#include "ControllerApp.h"
#include "ControllerSigfoxClient.h"
#include "HelperLog.h"


/**
 * Constructor.
 */
ControllerApp::ControllerApp():
nextLoop(0)
{

}

/**
 * Destructor.
 */
ControllerApp::~ControllerApp()
{

}

/**
 * Check whether it's time to run.
 */
bool ControllerApp::isTimeToRun() const 
{
    return millis() >= this->nextLoop;
}

/**
 * Set the next timer value for the next loop exec.
 */
void ControllerApp::setNextLoop()
{
    // Current loop is set to each 160 secs (~2min40sec).
    // This to be allowed to send 140 msg during 6 consecutive hours.
    this->nextLoop = millis() + (160 * 1000);
}

/**
 * Setup the manager.
 */
void ControllerApp::Setup()
{
    HelperLog::Begin();
    HelperLog::LogInfo("Running Setup()");

    // Put the board on the debug mode as she's
    // powered by the USB cable.
    ControllerSigfoxClient::WithDebug(true);

    ControllerSigfoxClient::LogAtmelStatus();
    ControllerSigfoxClient::LogSigfoxStatus();
    ControllerSigfoxClient::DisplayBoardInformations();

    HelperLog::LogInfo("End of Setup()");
}

/**
 * Main loop.
 */
void ControllerApp::Loop()
{
    if (!this->isTimeToRun())
    {
        return;
    }

    ControllerSigfoxClient::SendInternalTemperature();

    this->setNextLoop();
}