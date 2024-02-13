#include "Logger.hpp"

#include "ColourCodes.hpp"
#include "itos.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

// Delegation constructors are incompatable with c++ 98 :(
Logger::Logger()
        : stream(std::cout), listenFor(level_info)
{
        where = stdout;
}

Logger::Logger(const reportLevel listen)
        : stream(std::cout), listenFor(listen)
{
        where = stdout;
}

Logger::Logger(std::ostream& fileStream, const reportLevel listen) 
        : stream(fileStream), listenFor(listen)
{
        if (stream.fail() == true) {
                std::cerr << generateTimestamp() << " [Error]: Logger output"
                << " stream failed. Logging will be disabled." << std::endl;
        }
        where = file;
        debug("Logger constructed");

}

Logger::Logger(const Logger& copy)
        : stream(copy.stream), listenFor(copy.listenFor)
{
        where = copy.where;
        debug("Logger copied");
}

Logger::~Logger()
{
        flush();
        debug("Logger destructed");
}

std::string Logger::generateTimestamp()
{
        const std::time_t time = std::time(NULL);
        std::tm *local = std::localtime(&time);
        std::string output;
        output = itos(1900 + local->tm_year) + "-" + itos(local->tm_mon + 1);
        output += "-" + itos(local->tm_mday) + " " + itos(local->tm_hour) + ":";
        output += itos(local->tm_min) + ":" + itos(local->tm_sec);
        return output;
}

void Logger::write(reportLevel level, std::string levelColor, std::string message)
{
        if (stream.fail() == true)
                return;
        if (level < listenFor)
                return;
        std::string color = "";
        if (where == stdout)
                color = levelColor;
        const std::string time = generateTimestamp();
        stream << time << " ";
        switch (level) {
        case level_debug:
                stream << color << "  [Debug]: ";
                break;
        case level_info:
                stream << color << "   [Info]: ";
                break;
        case level_warning:
                stream << color << "[Warning]: ";
                break;
        case level_error:
                stream << color << "  [Error]: ";
                break;
        case level_fatal:
                stream << color << "  [FATAL]: ";
                break;
        default:
                stream << "An unknown error was logged: ";
        }
        stream << message;
        if (color != "")
                stream << CRESET;
        stream << "\n";
}

void Logger::debug(std::string message)
{
        write(level_debug, HBLU, message);
}

void Logger::info(std::string message)
{
        write(level_info, CRESET, message);
}

void Logger::warning(std::string message)
{
        write(level_warning, YEL, message);
}

void Logger::error(std::string message)
{
        write(level_error, RED, message);
}

void Logger::fatal(std::string message)
{
        write(level_fatal, BHRED, message);
        if (where == file)
                std::cerr << generateTimestamp()
                << BHRED<< "   [FATAL]: " << message 
                << CRESET << std::endl;
        flush();
}

void Logger::flush()
{
        stream.flush();
        if (stream.fail() == true)
                std::cerr << RED << "[Error]: Logger unable to flush to stream" 
                << CRESET << std::endl;
}
