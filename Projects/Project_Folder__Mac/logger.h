#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include "parameters.h"

class logger
{
public:
    struct strcAlgoReport{ ///< struct of log parameters for a log instance
        std::string timestamp; ///< time stamp
        std::string message; ///< message
        bool errors; ///< TRUE if there is any error
        bool improved; ///< TRUE if an 'step' in a 'iteration' is improved
        short iteration; ///< the algorithm's 'iteration' id number
    };
private:
    static strcAlgoReport m_log; ///< main log cache
    static std::vector<strcAlgoReport> m_logCache; ///< log instance cache

public:
    logger();
    void appendMsg(std::string message,
                bool errors = false);
    void setState(bool improved,
                  short iteration);
    strcAlgoReport getLog();
    std::string getMessage();
    bool getErrors();
    bool getImproved();
    short getIteration();
    void reset();
    std::string flush();
    std::string timestamp();
private:
    void cache();
};

#endif // LOGGER_H
