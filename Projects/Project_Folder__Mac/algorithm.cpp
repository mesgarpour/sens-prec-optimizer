/*! \file algorithm.cpp
    \brief the algorithm is applying the algorithm

    \see manager.cpp
    \see logger
*/
/*! \fn algorithm auto constructor
*/
/*! \fn void algorithm::set(const parameters &param,
        std::vector<parameters::strcStatisticalValues> &stats,
        unsigned short &maxSensitivity)
    \brief initialise the parameters and files for running the algorithm

    \param parameters an instance of the parameters
    \param stats the combinations statistics' container
    \param maxSensitivity the maximum sensivity throughout the runtime
    \see parameters
    \see logger
*/
/*! \fn void algorithm::combsGroupOne()
    \brief Calculate the statistics for combinations of length one

    \see algorithm::setCounter
    \see algorithm::combStats_Manager
*/
/*! \fn bool algorithm::combsGroups(
        unsigned short &numComb1,
        const unsigned short numComb2,
        const bool reverse,
        const bool tillImprove,
        const bool zeroImprove,
        const bool appendLast)
    \brief calculate the statistis for combinations of a length range

    \param numComb1 the first boundry for the length range
    \param numComb2 the second boundry for the length range
    \param reverse if the length range is in reverse order
    \param tillImprove true if the improvement in sensitivity is important
    \param zeroImprove true if equality in the comparison of sensitivities must
        be considered
    \param appendLast true if the cashed stats from the previous call needs to
        appended
    \return true if at least one combination length is calculated
    \see algorithm::setCounter
    \see algorithm::combStats_Manager
*/
/*! \fn bool algorithm::combStats_Manager(
        std::vector<parameters::strcStatisticalValues> &stats,
        float epsilon)
    \brief run the worker threads to calculate individual combinations
    \param stats the cached stats
    \param value of epsilon for comparoson of sensitivities
    \return true if at least one improvement in the sensitivity
    \see algorithm::e_combStats_Worker
*/
/*! \fn extern void e_combStats_Worker(
        const algorithm::strcConstParameters &constParameters,
        const std::vector<unsigned char> &counter,
        parameters::strcStatisticalValues *stats)
    \brief calculate the statistics for individual combinations
*/
/*! \fn void algorithm::initMatrix()
    \brief initialise the ublas matrices
*/
/*! \fn bool algorithm::nextCounter()
    \brief set the next combination counter
    \return true if there is one
    \see algorithm::setCounter
*/
/*! \fn void algorithm::setCounter(
        const unsigned short &combSize,
        const unsigned short &subCombSize)
    \brief initialise the combination counter
*/

#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <numeric>
#include <functional>
#include <math.h>
#ifndef Q_MOC_RUN
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/io.hpp>
#endif //Q_MOC_RUN
#include "algorithm.h"
#include "global.h"

using namespace std;
namespace bst = boost;
namespace bnu = boost::numeric::ublas;

algorithm::algorithm()
{
}

void algorithm::set(const parameters &param,
                    std::vector<parameters::strcStatisticalValues> &stats,
                    unsigned short &maxSensitivity)
{
    m_parameters = param;
    m_stats = &stats;
    m_maxSensitivity = &maxSensitivity;
    (*m_maxSensitivity) = 0;
    (*m_stats).clear();
    m_cachedStats.clear();
    m_log.reset();
    initMatrix();

    //reserve memory
    (*m_stats).reserve(RESERVED_MEM_STATS);
    m_cachedStats.reserve(RESERVED_MEM_CACHED_STATS);
}

void algorithm::combsGroupOne()
{
    bool combImproved;
    m_cachedStats.clear();

    setCounter(m_parameters.m_config.numFSs, 1);
    if(m_log.getErrors()) return;

    combImproved = combStats_Manager(
                m_cachedStats, -1 * EPSILON);
    if(m_log.getErrors()) return;

    (*m_stats).insert((*m_stats).end(),
                      m_cachedStats.begin(),
                      m_cachedStats.end());
    return;
}

bool algorithm::combsGroups(
        unsigned short &numComb1,
        const unsigned short numComb2,
        const bool reverse,
        const bool tillImprove,
        const bool zeroImprove,
        const bool appendLast)
{
    bool improved = false;
    unsigned short comb = numComb1;
    unsigned short combEnd = numComb2;
    stringstream ss;

    //adjust the start counter and end condition
    reverse ? combEnd-- : combEnd++;
    comb = max(2, (int)comb);
    combEnd = max(1, (int)combEnd);

    //Append last cached
    if(appendLast)
    {
        (*m_stats).insert((*m_stats).end(),
                          m_cachedStats.begin(),
                          m_cachedStats.end());
    }else
    {
        m_cachedStats.clear();
    }

    //Generate
    for(bool combImproved = true;
        comb != combEnd && (combImproved || !tillImprove);
        reverse?comb--:comb++)
    {
        numComb1 = comb;
        ss << "Processing combinations with length of " << comb << ".\n";
        m_log.appendMsg(ss.str());

        //Clear
        m_cachedStats.clear();
        ss.str("");

        //Initialise the counter to the size of FSs and combinations
        //FSs are the search queries
        setCounter(m_parameters.m_config.numFSs, comb);
        if(m_log.getErrors()) return false;

        //Calculate stats for the combinations
        combImproved = combStats_Manager(m_cachedStats,
                                         zeroImprove ? -1 * EPSILON : EPSILON);
        if(m_log.getErrors()) return false;

        //add the group of combinations if they improve or
        //tillImprove is FALSE
        try{
            if(combImproved
                    || !tillImprove)
            {
                (*m_stats).insert((*m_stats).end(),
                                  m_cachedStats.begin(),
                                  m_cachedStats.end());
                improved = true;
                m_cachedStats.clear();
            }
        }catch(...)
        {
            m_log.appendMsg("Memory Error!", true);
            return false;
        }
    }
    return improved;
}


bool algorithm::combStats_Manager(
        std::vector<parameters::strcStatisticalValues> &stats,
        float epsilon)
{
    QFuture<void> future[MAX_THREADS];
    parameters::strcStatisticalValues t_stats[MAX_THREADS];
    unsigned short thread;
    unsigned short maxSensitivity = *m_maxSensitivity;
    bool improved = false;
    bool noComb = false;

    while(true)
    {
        //dispatch threaded job-batches
        for(thread=0;
            thread < MAX_THREADS && !noComb;
            thread++)
        {
            //calculate stats (threaded)
            try
            {
                future[thread] = QtConcurrent::run(
                            e_combStats_Worker,
                            m_constParameters,
                            m_comb.counter,
                            &t_stats[thread]);
            }catch(...)
            {
                m_log.appendMsg("Algorithm is interupted unexpectedly!", true);
                return false;
            }

            //Next Counter
            if(nextCounter() != true)
                noComb = true;
        }

        //If NO more combinations
        if(thread == 0 && noComb)
            break;

        //wait for threads and collect stats
        for(unsigned short t = 0; t < thread; t++)
        {
            try
            {
                future[t].waitForFinished();//wait
            }catch(...)
            {
                m_log.appendMsg("Algorithm is interupted unexpectedly!", true);
                return false;
            }

            //add the combination if sensitivity improved
            if(t_stats[t].combSensitivity >=
                    m_parameters.m_config.minSensitiviy)
            {
                stats.push_back(t_stats[t]);//append
            }

            //Update max sensitivity
            if((t_stats[t].combSensitivity - *m_maxSensitivity) > epsilon)
            {
                improved = true;
                if((t_stats[t].combSensitivity - maxSensitivity) > epsilon)
                    maxSensitivity = t_stats[t].combSensitivity;
            }
        }
    }

    *m_maxSensitivity = maxSensitivity;
    return improved;
}

extern void e_combStats_Worker(
        const algorithm::strcConstParameters &constParameters,
        const std::vector<unsigned char> &counter,
        parameters::strcStatisticalValues *stats)
{
    //Init
    unsigned int combSum; //total number of 1s for each combination
    unsigned int combRelevancy; //total number of 1s produced by (Comb AND Rel)
    bnu::vector<bool> sumRow;
    bnu::matrix<bool> row;
    bnu::matrix<bool> orRows =
            bnu::subrange(constParameters.matrix,
                          counter.at(0), counter.at(0) + 1,
                          0, constParameters.matrix.size2());
    bnu::matrix<bool> orRowsTrans =
            bnu::subrange(constParameters.matrixTrans,
                          counter.at(0), counter.at(0) + 1,
                          0, constParameters.matrixTrans.size2());
    stats->comb = counter; //ToDo: fix the copy

    //OR operation of rows of doc-matched
    //using the ublas vector operation
    if(counter.size() > 1)
    {
        for(std::vector<unsigned char>::const_iterator i = counter.begin() + 1;
            i != counter.end();
            i++)
        {
            row = bnu::subrange(constParameters.matrix,
                                *i, *i + 1,
                                0, constParameters.matrix.size2());
            orRows = orRows + row;

            row = bnu::subrange(constParameters.matrixTrans,
                                *i, *i + 1,
                                0, constParameters.matrixTrans.size2());
            orRowsTrans = orRowsTrans + row;
        }
    }

    //cumulative matches of each doc
    sumRow = bnu::matrix_vector_slice<bnu::matrix<bool> >
            (orRows,
             bnu::slice(0,0,orRows.size2()),
             bnu::slice(0,1,orRows.size2()));
    combSum = accumulate(sumRow.begin(), sumRow.end(), 0);

    //cumulative relevancy of each doc
    sumRow = bnu::matrix_vector_slice<bnu::matrix<bool> >
            (orRowsTrans,
             bnu::slice(0,0,orRowsTrans.size2()),
             bnu::slice(0,1,orRowsTrans.size2()));
    combRelevancy = accumulate(sumRow.begin(), sumRow.end(), 0);

    //Percentage
    stats->combSensitivity = float(combRelevancy) /
            constParameters.totalRelevancy * 100;
    if(combSum == 0)
    {
        stats->combPrecision = 0;
    }else
    {
        stats->combPrecision = float(combRelevancy) /
                combSum * 100;
    }
}

void algorithm::initMatrix()
{
    bnu::matrix<bool> matrix
            (m_parameters.m_config.numFSs,
             m_parameters.m_config.numDocs);
    bnu::matrix<bool> matrixTrans
            (m_parameters.m_config.numFSs,
             m_parameters.m_config.numDocs);
    bnu::matrix<bool> relevMatrix
            (1,
             m_parameters.m_config.numDocs);

    for (unsigned int j=0 ; j < matrix.size2(); j++)
    {
        relevMatrix(0, j) = (bool)m_parameters.m_inputs.
                docsRelevancy.at(j);
    }

    for (unsigned int i=0 ; i < matrix.size1(); i++)
    {
        for (unsigned int j=0 ; j < matrix.size2(); j++)
        {
            matrix(i, j) = (bool)m_parameters.m_inputs.
                    docsFSs.at(i).at(j);
            matrixTrans(i, j) = matrix(i, j) && relevMatrix(0, j);
        }
    }

    m_constParameters.totalRelevancy =
            m_parameters.m_config.totalDocRelevancy;
    m_constParameters.matrix = matrix;
    m_constParameters.matrixTrans = matrixTrans;
}

bool algorithm::nextCounter()
{
    unsigned short cnt = 0;

    for(unsigned short c = 0; c < m_comb.counter.size(); c++, cnt++)
    {
        if(m_comb.counter.at(c) > c)
        {
            //update the counter
            m_comb.counter.at(c) --;
            for(int i = cnt - 1, j = 1;
                i >= 0;
                i--, j++)
                m_comb.counter.at(i) =
                        max(0, m_comb.counter.at(c) - j);
            return true;
        }
    }
    return false;
}

void algorithm::setCounter(
        const unsigned short &combSize,
        const unsigned short &subCombSize)
{
    //Validate
    if(combSize < subCombSize || subCombSize < 1)
    {
        m_log.appendMsg("Invalid number of subcombinations!\n",
                        true);
        return;
    }

    //Init
    m_comb = strcCombinationCounter();
    m_comb.size = combSize;
    m_comb.subSize = subCombSize;

    //Initialising the combination counter
    for(unsigned short i = 0, cnt = m_comb.size - m_comb.subSize;
        i < m_comb.subSize;
        i++, cnt++)
    {
        m_comb.counter.push_back(cnt);
    }
}
