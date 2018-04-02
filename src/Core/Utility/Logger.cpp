//
// Created by MTesseracT on 9-3-2018.
//

#include "Logger.hpp"
#include <iostream>
#include <sstream>

namespace mt
{
    Logger &Logger::get()
    {
        static Logger instance;
        return instance;
    }

    void Logger::printLog(const std::string& m_prefix, const std::string& p_message)
    {
        std::stringstream output;
        output << "[" << m_prefix << "] " << p_message;
        std::cout << output.str() << std::endl;
    }

    void Logger::printError(const std::string& m_prefix, const std::string& p_message)
    {
        //This makes sure that everything printed from cout is done before the cerr is done
        std::cout << std::flush;
        std::stringstream output;
        output << "[" << m_prefix << "] " << p_message;
        std::cerr << output.str() << std::endl;
    }

    void Logger::log(const std::string& p_message, LogType p_level)
    {
        Logger logger = get();

        if (static_cast<int>(p_level) < static_cast<int>(logger.m_level)) return;

        switch (p_level)
        {

            case LogDebug:
                logger.printLog("Debug", p_message);
                break;
            case LogInfo:
                logger.printLog("Info", p_message);
                break;
            case LogError:
                logger.printError("Error", p_message);
                break;
        }
    }

    void Logger::setLogLevel(LogLevel p_level)
    {
        get().m_level = p_level;
    }

    LogLevel Logger::getLogLevel()
    {
        return get().m_level;
    }
}