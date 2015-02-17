#ifndef MANAGER_H
#define MANAGER_H

#ifndef Q_MOC_RUN
#include <boost/date_time/posix_time/posix_time.hpp>
#endif //Q_MOC_RUN
#include "parameters.h"
#include "logger.h"
#include "writeFile.h"
#include "readFile.h"
#include "algorithm.h"

class manager
{
public:
private:
    algorithm m_algorithm; ///< algorithm instance
    logger m_log; ///< log instance
    parameters m_parameters; ///< parameters instance
    std::vector<parameters::strcStatisticalValues> m_stats; ///< [stats & Docs]
    unsigned short m_maxSensitivity; ///< current max sensitivity
    writeFile *m_write; ///< write instance
    readFile m_read; ///< read instance
    short m_iteration; ///< current iteration of the algorithm
    unsigned short m_numComb; ///< length of the current combination calculation
    boost::posix_time::ptime m_stopWatch; ///< stop-watch parameter

public:
    manager();
    logger::strcAlgoReport set(const parameters &param);
    logger::strcAlgoReport run();
private:
    void combinationOne();
    void initializeCombinations();
    bool largerCombinations();
    bool smallerCombinations();
    bool additionalCombinations();
    void sortFilterOutput();
    void filterCombinations();
    bool filterCombLimitRange(
            const parameters::strcStatisticalValues &stat,
            float &maxSensitivity,
            float &delta);
    bool filterCombByPrecision(
            const parameters::strcStatisticalValues &stat,
            std::vector<parameters::strcStatisticalValues> &tempStats,
            float &delta,
            float &tempSens,
            float &tempPrec,
            unsigned short &tempCombSize);
    std::string stopWatch(bool start);
};

#endif // MANAGER_H
