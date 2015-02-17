#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <string>
#include <vector>
#include "logger.h"
#include "parameters.h"
#include "global.h"

class writeFile
{
public:
private:
    logger m_log; ///< log instance
    std::string m_path; ///< path of output
    std::string m_header; ///< header row for statistics output
    std::string m_time; ///< time stamp
    parameters m_parameters; ///< parameters instance

public:
    writeFile(const std::string &path);
    void setStatLog(
            const parameters &parameters);
    void outputStatLog(
            const std::vector<parameters::strcStatisticalValues> &stats);
    void outputAppLog();
    std::string configs2String();
private:
};

#endif // WRITEFILE_H
