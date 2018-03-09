//
// Created by MTesseracT on 9-3-2018.
//

#ifndef VULKANENGINEFIXED_LOGGER_HPP
#define VULKANENGINEFIXED_LOGGER_HPP

#include <string>

namespace mt
{
    enum LogLevel{
        All = 0,
        Debug = 1,
        Info = 2,
        Error = 3,
        Off = 4
    };

    enum LogType
    {
        LogDebug = 1,
        LogInfo  = 2,
        LogError = 3,
    };

    class Logger
    {
        LogLevel m_level;

        /*
         * Constructor and destructor
         */
        Logger(): m_level(All) {} ;
        ~Logger() = default;


        void printLog(std::string m_prefix, std::string p_message);

        static Logger& get();

    public:
        static void log(std::string p_message, LogType p_level = LogInfo);

        static void setLogLevel(LogLevel p_level);

        static LogLevel getLogLevel();
    };
}




#endif //VULKANENGINEFIXED_LOGGER_HPP
