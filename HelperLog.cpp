/**
 * Includes. 
 */
#include "HelperLog.h"


/**
 * Global init. 
 */
HelperLogLevel HelperLog::level = HELPERLOG_LEVEL_INFO;


/**
 * Constructor.
 */
HelperLog::HelperLog()
{
}

/**
 * Log the message according to the policy.
 */
void HelperLog::Log(HelperLogLevel level, String s)
{
    if (level <= HelperLog::level)
    {
#ifdef WITH_DEBUG
        Serial.println(s.c_str());
#endif
    }
}

/**
 * Start the logger.
 */
void HelperLog::Begin()
{
#ifdef WITH_DEBUG
    Serial.begin(115200);
    while (!Serial) {};
#endif
}

/**
 * Log debug message (String).
 */
void HelperLog::LogError(String s)
{
    HelperLog::Log(HELPERLOG_LEVEL_ERROR, "[ERROR] " + s);
}

/**
 * Log debug message (const char*)
 */
void HelperLog::LogError(const char* s)
{
    if (s != NULL)
    {
        HelperLog::LogError(String(s));
    }
}

/**
 * Log info message (String).
 */
void HelperLog::LogInfo(String s)
{
    HelperLog::Log(HELPERLOG_LEVEL_INFO, "[INFO] " + s);
}

/**
 * Log info message (const char*).
 */
void HelperLog::LogInfo(const char* s)
{
    if (s != NULL)
    {
        HelperLog::LogInfo(String(s));
    }
}