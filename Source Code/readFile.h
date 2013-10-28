#ifndef READFILE_H
#define READFILE_H

#include "parameters.h"
#include "logger.h"

class readFile
{
//Attributes
public:
private:
    logger m_log; ///< log instance
    unsigned int m_numColsRead; ///< number of columns read

//Functions
public:
    readFile();
    void set(parameters &parameters);

private:
    void validateDomains(parameters &parameters);
    template<typename temp>
    void line(
            const std::string &line,
            std::vector<std::string> &id,
            std::vector<temp> &output,
            const unsigned int iStart);
    void conversions(parameters &parameters);
    bool isNumber(const std::string &arg);
};

#endif // READFILE_H
