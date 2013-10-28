#ifndef ALGORITHM_H
#define ALGORITHM_H
#ifndef Q_MOC_RUN
#include <boost/numeric/ublas/matrix.hpp>
#endif //Q_MOC_RUN
#include "parameters.h"
#include "logger.h"

class algorithm
{
//variables
public:
    struct strcConstParameters{ ///< struct of constant parameters (in threading)
        boost::numeric::ublas::matrix<bool> matrix; ///< [FSs & Docs]
        boost::numeric::ublas::matrix<bool> matrixTrans; ///< [FSs & relev & Docs]
        unsigned int totalRelevancy;
    };
private:
    struct strcCombinationCounter ///< struct of combination counter parameters
    {
        std::vector<unsigned char> counter; ///< implicit counter for combinations
        unsigned char size; ///< max length of combinations
        unsigned char subSize; ///< current length of the combination
    };

    logger m_log; ///< log instance
    parameters m_parameters; ///< parameters instance
    strcCombinationCounter m_comb; ///< current combination
    strcConstParameters m_constParameters; ///< constant parameters(in threading)
    std::vector<parameters::strcStatisticalValues> *m_stats; ///< [stats & Docs]
    std::vector<parameters::strcStatisticalValues> m_cachedStats; ///< cached [stats & Docs]
    unsigned short *m_maxSensitivity; ///< current max sensitivity

//functions
public:
    algorithm();
    void set(const parameters &param,
             std::vector<parameters::strcStatisticalValues> &stats,
             unsigned short &maxSensitivity);
    void combsGroupOne();
    bool combsGroups(
            unsigned short &numComb1,
            const unsigned short numComb2,
            const bool reverse = false,
            const bool zeroImprove = false,
            const bool tillImprove = true,
            const bool appendLast = false);
private:
    bool combStats_Manager(
            std::vector<parameters::strcStatisticalValues> &stats,
            float epsilon);
    void setCounter(const unsigned short &combSize,
                    const unsigned short &subCombSize);
    void initMatrix();
    bool nextCounter();
};

//Note: stats must be passed by pointer
extern void e_combStats_Worker(
        const algorithm::strcConstParameters &constParameters,
        const std::vector<unsigned char> &counter,
        parameters::strcStatisticalValues *stats);

#endif // ALGORITHM_H
