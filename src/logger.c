#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "logger.h"

LogLevel logLevel = LOG_ERROR;

void logMessage(LogLevel level, const char *message, va_list arg)
{
    if (level <= logLevel)
    {
        switch (level)
        {
        case LOG_ERROR:
            fprintf(stderr, "ERROR: ");
            vfprintf(stderr, message, arg);
            break;
        case LOG_WARN:
            fprintf(stderr, "WARN: ");
            vfprintf(stderr, message, arg);
            break;
        case LOG_INFO:
            fprintf(stderr, "INFO: ");
            vfprintf(stderr, message, arg);
            break;
        case LOG_DEBUG:
            fprintf(stderr, "DEBUG: ");
            vfprintf(stderr, message, arg);
            break;
        }
    }
}

void logError(const char *message, ...)
{
    va_list arg;
    va_start(arg, message);
    logMessage(LOG_ERROR, message, arg);
    va_end(arg);
}

void logWarn(const char *message, ...)
{
    va_list arg;
    va_start(arg, message);
    logMessage(LOG_WARN, message, arg);
    va_end(arg);
}

void logInfo(const char *message, ...)
{
    va_list arg;
    va_start(arg, message);
    logMessage(LOG_INFO, message, arg);
    va_end(arg);
}

void logDebug(const char *message, ...)
{
    va_list arg;
    va_start(arg, message);
    logMessage(LOG_DEBUG, message, arg);
    va_end(arg);
}

void setLogLevel(LogLevel level)
{
    logLevel = level;
}
