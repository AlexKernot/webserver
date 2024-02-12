#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <ostream>
# include <string>

class Logger {
public:
        enum reportLevel {
                level_debug,
                level_info,
                level_warning,
                level_error,
                level_fatal
        };

        Logger();
        Logger(const reportLevel listen);
        Logger(std::ostream& fileStream, const reportLevel listen);
        Logger(const Logger& copy);
        ~Logger();

        void debug(std::string message);
        void info(std::string message);
        void warning(std::string message);
        void error(std::string message);
        void fatal(std::string message);

        void flush();
private:
        void write(reportLevel level, std::string levelColor, std::string message);
        std::string generateTimestamp();
        
        std::ostream& stream;
        const reportLevel listenFor;

        enum outputTo {file, stdout};
        outputTo where;

        // * ostream cannot be assigned, therefore operator= cannot function
        Logger& operator=(const Logger&);
};

#endif // LOGGER_HPP
