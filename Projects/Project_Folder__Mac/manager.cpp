/*! \file manager.cpp
    \brief the manager is responsible for the control of the algorithm execution
        as well as the output filtering

    \see algorithm
    \see logger
*/
/*! \fn manager::manager()
    \brief initialise the internal parameters
*/
/*! \fn logger::strcAlgoReport manager::set(const parameters &param)
    \brief initialise the algorithm

    \param param an instance of the parameters
    \return the current instance of the log
    \see parameters
    \see read
    \see read::set
    \see write
    \see write::setLog
    \see algorithm
    \see algorithm::set
*/
/*! \fn logger::strcAlgoReport manager::run()
    \brief in each call it can run an iteration of the algorithm

    \return the current instance of the log
    \see manager::combinationOne
    \see manager::initialiseCombinations
    \see manager::largeCombinations
    \see manager::smallerCombinations
    \see manager::additionalCombinations
    \see manager::sortFilterOutput
    \see manager::stopWatch
    \see logger
    \see logger::strcAlgoReport
*/
/*! \fn void manager::combinationOne()
    \brief calculate the statistics for combination length of one

    \see algorithm::combsGroupOne
*/
/*! \fn void manager::initializeCombinations()
    \brief calculate the statring combination which the the length is specified
        as percentage by the user

    \see algorithm::combsGroups
*/
/*! \fn bool manager::largerCombinations()
    \brief calculate the larger combinations from the starting point until the
        condition of improvement or filtering criteria are not satsfied

    \return true, if it improved
    \see algorithm::combsGroups
*/
/*! \fn bool manager::smallerCombinations()
    \brief calculate the smaller combinations from the starting point until the
        condition of improvement or filtering criteria are not satsfied

    \return true, if it improved
    \see algorithm::combsGroups
*/
/*! \fn bool manager::additionalCombinations()
    \brief calculate additional combinations from the stopping point until the
        condition of improvement or filtering criteria are not satsfied

    \return true, if it improved
    \see algorithm::combsGroups
*/
/*! \fn void manager::sortFilterOutput()
    \brief sort and filter the output based on the defined settings

    \see manager::filterCombinations
*/
/*! \fn void manager::filterCombinations()
    \brief filter combinations by the sensitivity range and precision.

    \see manager::filterCombLimitRange
    \see manager::filterCombByPrecision
*/
/*! \fn bool manager::filterCombLimitRange(
        const parameters::strcStatisticalValues &stat,
        float &maxSensitivity,
        float &delta)
    \brief check if the precision is in the range for a combination

    \param stat the statistics for the combination
    \param maxSensitivity the maxSensitivity, minus the acceptable range
    \param delta a reference memory for value of delta
    \return true if the precision is not in the defined range
    \see parameters::strcStatisticalValues
*/
/*! \fn bool manager::filterCombByPrecision(
        const parameters::strcStatisticalValues &stat,
        std::vector<parameters::strcStatisticalValues> &tempStats,
        float &delta,
        float &tempSens,
        float &tempPrec,
        unsigned short &tempCombSize)
    \brief filter the combinations by precision and length

    \param stat the statistics for the combination
    \param tempStats the vector of statistics that are potentially accepted
    \param delta a reference memory for value of delta
    \param tempSens a reference memory for value of the sensitivity
    \param tempPrec a reference memory for value of the precision
    \param tempCombSize a reference memory for value of  combSize
    \see parameters::strcStatisticalValues
*/
/*! \fn std::string manager::stopWatch(bool start)
    \brief a stopwatch using the boost::posix_time

    \return return the delta time if the input argument is false
    \param start true if you like to set the watch
    \see boost::posix_time
*/

#include "manager.h"
#include "global.h"

using namespace std;
namespace bst = boost;

manager::manager():
    m_iteration(-1)
{
}

logger::strcAlgoReport manager::set(const parameters &param)
{
    //set parameters
    m_iteration = 1;
    m_parameters = param;
    m_log.reset();

    //read
    m_read.set(m_parameters);
    if(m_log.getErrors() == true)
        return m_log.getLog();
    m_algorithm.set(m_parameters, m_stats, m_maxSensitivity);

    //initialize write
    m_write = new writeFile(m_parameters.m_config.outputDir);
    m_write->setStatLog(m_parameters);
    return m_log.getLog();
}

logger::strcAlgoReport manager::run()
{
    bool improved;

    m_log.reset();
    switch(m_iteration)
    {
    case 1:
        m_log.appendMsg("Configurations: \n" +
                        m_write->configs2String() +
                        "\nInitialising...\n");
        break;
    case 2:
        stopWatch(true);
        combinationOne();
        break;
    case 3:
        initializeCombinations();
        break;
    case 4:
        improved = largerCombinations();
        break;
    case 5:
        improved = smallerCombinations();
        break;
    case 6:
        improved = additionalCombinations();
        m_log.appendMsg("Algorithm's Runtime: " + stopWatch(false) +
                        "  (hours: minutes : seconds . microseconds)\n");
        m_log.appendMsg("Filtering and outputting...\n");
        break;
    case 7:
        sortFilterOutput();
        m_iteration = -2;
        break;
    default:
        m_iteration = -2;
    }
    m_iteration++;

    m_log.setState(improved, m_iteration);
    if(m_iteration > 0) m_log.appendMsg("\nNext Process...");
    return m_log.getLog();
}

void manager::combinationOne()
{
    stringstream ss;
    m_numComb = 1;

    m_algorithm.combsGroupOne();
    //if defaultMinSensitivity
    //then set the acceptable min sensitivity to the max sensitivity
    if(m_parameters.m_config.defaultMinSensitivity)
    {
        m_parameters.m_config.minSensitiviy = m_maxSensitivity;
    }

    ss << "Combinations of length 1 is calculated!\n";
    m_log.appendMsg(ss.str());
}

void manager::initializeCombinations()
{
    bool improved;
    stringstream ss;

    m_numComb = m_parameters.m_config.combStart;
    improved = m_algorithm.combsGroups(
                m_numComb, m_numComb); //Generate
    if(m_log.getErrors()) return;

    ss << "Initialised by combinations of length " << m_numComb <<
          ".\n";
    m_log.appendMsg(ss.str());
    m_numComb++; //next combination
}

bool manager::largerCombinations()
{
    bool improved;
    stringstream ss;

    improved = m_algorithm.combsGroups
            (m_numComb, m_parameters.m_config.numFSs); //Generate
    if(m_log.getErrors()) return false;

    ss <<"The larger combinations improved upto "
      << m_numComb << " length.\n";
    m_log.appendMsg(ss.str());
    m_numComb--; //next combination
    return improved;
}

bool manager::smallerCombinations()
{
    bool improved;
    stringstream ss;

    m_numComb = m_parameters.m_config.combStart - 1;
    improved = m_algorithm.combsGroups(
                m_numComb, 2, true, true); //Generate
    if(m_log.getErrors()) return false;

    ss <<"The smaller combinations calculated down to "
      << m_numComb << " length.\n";
    m_log.appendMsg(ss.str());
    return improved;
}

bool manager::additionalCombinations()
{
    bool improved;
    stringstream ss;

    m_numComb--;
    short endComb = m_numComb - m_parameters.m_config.combSmaller;
    endComb = max((short)2, endComb);
    if(m_numComb < 2 ||
            m_parameters.m_config.combSmaller == 0)
        return false;

    //Generate
    improved = m_algorithm.combsGroups(
                m_numComb, endComb, true,
                false, false, true);
    if(m_log.getErrors()) return false;

    ss <<"The additional smaller combinations calculated down to "
      << m_numComb  << " length.\n";
    m_log.appendMsg(ss.str());
    return improved;
}

void manager::sortFilterOutput()
{
    //Sort
    sort(m_stats.begin(), m_stats.end(),
         parameters::CompBySensitivity());
    //Filter
    filterCombinations();
    //Output
    m_write->outputStatLog(m_stats);
    m_write->outputAppLog();
    m_log.appendMsg("Complete!\n");
}

void manager::filterCombinations()
{
    std::vector<parameters::strcStatisticalValues> cachedStats;
    std::vector<parameters::strcStatisticalValues> tempStats;
    float delta;
    float tempSens;
    float tempPrec;
    float tempMaxSensitivity =
            max(0, (int)(m_maxSensitivity - m_parameters.m_config.filterSensRange));
    unsigned short tempCombSize;

    //Initialize
    if(m_stats.size() > 0)
    {
        tempSens = m_stats.at(0).combSensitivity;
        tempPrec = m_stats.at(0).combPrecision;
        tempCombSize = m_stats.at(0).comb.size();
    }

    //filter
    for(vector<parameters::strcStatisticalValues>
        ::const_iterator s = m_stats.begin();
        s != m_stats.end();
        s++)
    {
        if(!filterCombLimitRange(*s, tempMaxSensitivity, delta))
        {
            if(m_parameters.m_config.filterMinimizeLength)
            {
                if(!filterCombByPrecision(*s, tempStats, delta,
                                          tempSens, tempPrec, tempCombSize))
                {
                    cachedStats.insert(cachedStats.end(),
                                       tempStats.begin(),
                                       tempStats.end());
                    tempStats.clear();
                }
            }else
            {
                cachedStats.push_back(*s);
            }
        }
    }

    cachedStats.insert(cachedStats.end(),
                       tempStats.begin(),
                       tempStats.end());
    m_stats = cachedStats;

    cachedStats.clear();
    tempStats.clear();
}

bool manager::filterCombLimitRange(
        const parameters::strcStatisticalValues &stat,
        float &maxSensitivity,
        float &delta)
{
    delta = maxSensitivity - stat.combSensitivity;
    if(delta < EPSILON)
        return false;
    else
        return true;
}

bool manager::filterCombByPrecision(
        const parameters::strcStatisticalValues &stat,
        std::vector<parameters::strcStatisticalValues> &tempStats,
        float &delta,
        float &tempSens,
        float &tempPrec,
        unsigned short &tempCombSize)
{
    //if sensitivy decreasing then update the decision parameters
    //and return true to write up the cache
    delta = tempSens - stat.combSensitivity;
    if(delta > EPSILON)
    {
        tempSens = stat.combSensitivity;
        tempPrec = stat.combPrecision;
        tempCombSize = stat.comb.size();
        return false;
    }
    //else: similar sensitivity
    else
    {
        delta = tempPrec - stat.combPrecision;
        //if similar precision then apply the filter
        if(delta < EPSILON && delta > -EPSILON)
        {
            //similar sizes then cache it
            if(tempCombSize == stat.comb.size())
            {
                tempStats.push_back(stat);
            }
            //smaller combination size then cache it after resetting
            else if(tempCombSize > stat.comb.size())
            {
                tempStats.clear();
                tempStats.push_back(stat);
                tempCombSize = stat.comb.size();
            }
            //else: Ignore larger combinations
            return true;
        }
        //else: precision is decreasing then ignore
        else
        {
            return false;
        }
    }
}

std::string manager::stopWatch(bool start)
{
    if(start == true)
    {
        m_stopWatch = bst::posix_time::microsec_clock::local_time();
        return "";
    }else
    {
        const bst::posix_time::ptime stopWatch =
                bst::posix_time::microsec_clock::local_time();
        const bst::posix_time::time_duration deltaTime =
                stopWatch - m_stopWatch;
        stringstream ss;
        ss << deltaTime;
        return ss.str();
    }
}
