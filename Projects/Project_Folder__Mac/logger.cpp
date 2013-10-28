/*! \file logger.cpp
    \brief implements the log management

    \see logger
*/
/*! \fn logger::logger()
    \brief initialise the looger
    The log cache consists of instances which can be appended, and the instance
    only moves forward when reset is called. The cached instances can be flushed
    and cleared.
    \see logger::reset
*/
/*! \fn void logger::appendMsg(std::string message,
                    bool errors)
    \brief append a message to the current instance of the log

    \param message the message to be logged
    \param errors true if it is an error message
*/
/*! \fn void logger::setState(bool improved,
        short iteration)
    \brief set state message which logs the state of the algorithm

    \param improved true if the internal 'improve' flag is been set to true
    \param iteration the current iteration of the algorithm
    \see algorithm
*/
/*! \fn logger::strcAlgoReport logger::getLog()
    \brief return the current instance of the log

    \return the current log instance
    \see logger::strcAlgoReport
*/
/*! \fn string logger::getMessage()
    \brief get the message for the current log instance

    \return the message
    \see logger::strcAlgoReport
*/
/*! \fn bool logger::getErrors()
    \brief get the error flag  for the current log instance

    \return the error flag
    \see logger::strcAlgoReport
*/
/*! \fn bool logger::getImproved()
    \brief get the improved flag for the current log instance

    \return the improved
    \see logger::strcAlgoReport
*/
/*! \fn short logger::getIteration()
    \brief get the iteration number for the current log instance

    \return the iteration number
    \see logger::strcAlgoReport
*/
/*! \fn void logger::cache()
    \brief cache the current instance of the log

    \see logger::strcAlgoReport
*/
/*! \fn void logger::reset()
    \brief reset the log instance

    \see logger::strcAlgoReport
*/
/*! \fn string logger::flush()
    \brief flush and clear all the log instances

    \see logger::strcAlgoReport
*/
/*! \fn std::string logger::timestamp()
    \brief calculate the present date and time

    \return the date and time
*/

#include <sstream>
#include <ctime>
#include "logger.h"

using namespace std;

logger::strcAlgoReport logger::m_log;
std::vector<logger::strcAlgoReport> logger::m_logCache;

logger::logger()
{
    reset();
}

void logger::appendMsg(std::string message,
                       bool errors)
{
    m_log.message += message;
    if(!m_log.errors)
        m_log.errors = errors;
}

void logger::setState(bool improved,
                      short iteration)
{
    m_log.timestamp = timestamp();
    m_log.improved = improved;
    m_log.iteration = iteration;
}
logger::strcAlgoReport logger::getLog()
{
    return m_log;
}

string logger::getMessage()
{
    return m_log.message;
}

bool logger::getErrors()
{
    return m_log.errors;
}

bool logger::getImproved()
{
    return m_log.improved;
}

short logger::getIteration()
{
    return m_log.iteration;
}

void logger::cache()
{
    m_logCache.push_back(m_log);
}

void logger::reset()
{
    cache();
    m_log.timestamp = timestamp();
    m_log.message = "";
    m_log.errors = false;
    m_log.improved = false;
    m_log.iteration = -1;
}

string logger::flush()
{
    stringstream ss;
    strcAlgoReport tempLog;

    //flush
    for(vector<strcAlgoReport>::const_iterator
        r = m_logCache.begin();
        r != m_logCache.end();
        r++)
    {
        ss << (*r).timestamp << "..." <<endl;
        if(tempLog.message != (*r).message)
            ss << "Message: " << (*r).message << endl;
        if(tempLog.errors != (*r).errors)
            ss << "Error: " <<  std::boolalpha << (*r).errors << endl;
        if(tempLog.improved != (*r).improved)
            ss << "Improved: " <<  std::boolalpha << (*r).improved << endl;
        if(tempLog.iteration != (*r).iteration)
            ss << "Iteration: " << (*r).iteration << endl << endl;
        tempLog = *r;
    }

    //reset
    reset();
    m_logCache.clear();
    return ss.str();
}

std::string logger::timestamp()
{
    stringstream ss;
    time_t t = time(0); //present time
    struct tm strcTime;

    //Get the time
    #ifdef __APPLE__  //the compiler in Mac
        localtime_r(&t, &strcTime);
    #elif _WIN32 //__MINGW32__ //MinGW compiler in windows
        localtime_s(&strcTime, &t);
    #elif __GNUC__ //GCC compiler in Linux
        localtime_r(&t, &strcTime);
    #else
        #error "Unknown platform in the global header!"
    #endif

    //time to string
    ss << (strcTime.tm_year + 1900) << "_" <<
          (strcTime.tm_mon + 1) << "_" <<
          strcTime.tm_mday << "__" <<
          strcTime.tm_hour << "_" <<
          strcTime.tm_min << "_" <<
          strcTime.tm_sec;

    return ss.str();
}
