#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <string>
#include <vector>
#include "global.h"


class parameters
{
//atributes
public:
    struct strcConfigParameters ///< struct of configuration parameters
    {
        //path
        std::string inputFile; ///< path to the input file
        std::string outputDir; ///< path to the output file
        //Data Configs
        bool defaultInputDataConfig; ///< option: default input configuration
        bool defaultMinSensitivity; ///< option: default min sensitivity
        unsigned int totalDocRelevancy; ///< total number of relevant documents
        unsigned int numFSs; ///< number of search queries
        unsigned int numDocs; ///< number of documents
        //Algo Configs
        unsigned short combStart; ///< the starting combination (in iteration 2)
        unsigned short combSmaller; ///< number of additional smaller combinations
        float minSensitiviy; ///< acceptable min sensitivity
        //output
        bool filterMinimizeLength; ///< option: minimize search strategies length
        unsigned short filterSensRange; ///< range of filtering the sensitivity
    };

    struct strcInputParameters{ ///< struct of input parameters
        unsigned int totalDocRelevancy; ///< total number of relevant documents
        unsigned int numFSs; ///< number of search queries
        unsigned int numDocs; ///< number of documents
        std::vector<unsigned int> docsIDs; ///< document IDs
        std::vector<std::string> fsIDs; ///< search queries IDs
        std::vector<std::string> relvancyIDs; ///< ID of relevancy row (obsolete)
        std::vector<bool> docsRelevancy; ///< documnets relevancies
        std::vector< std::vector<bool> > docsFSs; ///< relvancy of search queries
    };

    struct strcStatisticalValues{
        std::vector<unsigned char> comb; ///< vector of combinations

        float combSensitivity; ///< Sensitivity = cumulative relevancy of
                                ///< each doc / total relevance * 100
        float combPrecision; ///< Precision = cumulative relevancy of
                                ///< each doc / cumulative matched of each doc * 100
    };

    /*
     * Comparison of 'Sensitivity' then 'precision' for the STL sort
     * return(ascending): the return of conditions on a > conditions on b
     */
    struct CompBySensitivity { ///< Comparison of 'Sensitivity' then 'precision'
                                ///< for the STL sort. The return is ascending: the
                                ///< return of conditions on a > conditions on b
        bool operator()(const strcStatisticalValues &a,
                        const strcStatisticalValues &b) const {
            float delta = b.combSensitivity - a.combSensitivity;

            if((delta <= EPSILON) && (delta >= -EPSILON)){
                return ((b.combPrecision - a.combPrecision) < -EPSILON);
            }else{
                return (delta < -EPSILON);
            }
        }
    };

    struct CompByPrecision { ///< Comparison of 'Precision' then 'sensitivity'
                               ///< for the STL sort
        bool operator()(const strcStatisticalValues &a,
                        const strcStatisticalValues &b) const {
            float delta = b.combPrecision - a.combPrecision;

            if((delta <= EPSILON) && (delta >= -EPSILON)){
                return ((b.combSensitivity - a.combSensitivity) < -EPSILON);
            }else{
                return (delta < -EPSILON);
            }
        }
    };

    strcInputParameters m_inputs; ///< input parameters
    strcConfigParameters m_config; ///< configuration parameters

//functions
public:
    parameters();
    void reset();
};

#endif // PARAMETERS_H
