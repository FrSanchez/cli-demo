typedef enum
{
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

void logError(const char *message, ...);
void logWarn(const char *message, ...);
void logInfo(const char *message, ...);
void logDebug(const char *message, ...);
void setLogLevel(LogLevel level);
