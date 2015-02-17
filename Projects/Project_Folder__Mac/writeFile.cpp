/*! \file writeFile.cpp
    \brief write the statistics and log outputs into files

    \see logger
*/
/*! \fn writeFile::writeFile(const string &path)
    \brief initilaise the internal parameters

    \param path the folder path for writing the outputs
*/
/*! \fn void writeFile::setStatLog(const parameters &parameters)
    \brief set the statistics log

    \param parameters in instance of the parameters
    \see logger::timestamp
*/
/*! \fn void writeFile::outputStatLog(
        const vector<parameters::strcStatisticalValues> &stats)
    \brief output the statistics logs

    \param stats the list of stats to be printed
    \see parameters::strcStatisticalValues
*/
/*! \fn void writeFile::outputAppLog()
    \brief outputs the appliction log into a file

    \see logger
*/
/*! \fn string writeFile::configs2String()
    \brief return the input and configuration settings as readable text format

    \return the app settings in string format
*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "writeFile.h"


using namespace std;

writeFile::writeFile(const string &path)
{
    m_log.reset();
    m_path = path + PATH_SUB_CHAR + FILE_OUTPUT_STATS;
}

void writeFile::setStatLog(const parameters &parameters)
{
    stringstream ss;
    m_parameters = parameters;
    //Set timestamp
    m_time = "_Time_" + m_log.timestamp() + "_Report_";

    //Prepare header row
    for(char i = 0;
        i < sizeof(OUTPUT_TITLES)/sizeof(*OUTPUT_TITLES);
        i++)
    {
        ss << OUTPUT_TITLES[i];
        ss << FILE_OUTPUT_DELIMITER;
    }
    m_header = ss.str();
}

void writeFile::outputStatLog(
        const vector<parameters::strcStatisticalValues> &stats)
{
    unsigned short numFiles = ceil((float)stats.size() / MAX_OUTPUT_ROWS);
    vector<parameters::strcStatisticalValues>
            ::const_iterator rp = stats.begin();//row Pointer
    std::vector<unsigned char>::const_iterator cp; //combination pointer
    stringstream ss;

    //for each output file...
    for(unsigned int f = 1, c = 0; f <= numFiles; f++)
    {
        //Set file
        ofstream file;
        ss.str(""); ss << f;
        file.open((m_path + m_time + ss.str() + FILE_OUTPUT_EXTEN).c_str(),
              fstream::out);

        //check file
        if(!file)
        {
            m_log.appendMsg("The output file can not be accessed!\n", true);
            return;
        }

        //set write settings
        file.precision(10);
        file.setf(ios::showpoint);

        //write header
        file << m_header << endl;
        //write stat rows
        for(unsigned int i=0 ;
            rp != stats.end() && i < MAX_OUTPUT_ROWS;
            rp++, i++)
        {
            //Write a row of stats
            ss.str("");
            for (cp = (*rp).comb.begin();
                 cp != (*rp).comb.end();
                 cp++)
            {
                ss << m_parameters.m_inputs.fsIDs.at(*cp) << "_";
            }

            file << ++c << FILE_OUTPUT_DELIMITER//counter
                 << ss.str() << FILE_OUTPUT_DELIMITER//the search-query's combination
                 << (*rp).comb.size() << FILE_OUTPUT_DELIMITER//the combination size
                 << (*rp).combSensitivity << FILE_OUTPUT_DELIMITER//= Relevancy / X
                 << (*rp).combPrecision << endl;//= Relevancy / Sum;
        }
        file.close();
    }
}

void writeFile::outputAppLog()
{
    //produce log string
    stringstream ss;
    ss << APP_NAME << endl;
    ss << "Timestamp: " <<  m_time << endl;
    ss << "Configurations: " << endl;
    ss << configs2String() << endl << endl;
    ss <<  "Logs: \n" << m_log.flush() << endl;

    //Set File
    ofstream file;
    file.open((m_path + "_" + FILE_OUTPUT_LOG + m_time + ".log").c_str(),
              fstream::out);

    //check file
    if(!file)
    {
        m_log.appendMsg("The output file can not be accessed!\n", true);
        return;
    }else
    {
        //set write settings
        file.precision(10);
        file.setf(ios::showpoint);
        //write
        file << ss.str();
    }

    file.close();
}

string writeFile::configs2String()
{
    stringstream ss;

    ss << "Input File: \""
       << m_parameters.m_config.inputFile << "\"" << endl;
    ss <<  "Output Path: \""
        << m_parameters.m_config.outputDir << "\"" << endl;
    ss << "Default Data Configurations: " << std::boolalpha
       << m_parameters.m_config.defaultInputDataConfig << endl;
    ss <<  "Number of Documents: "
        << m_parameters.m_config.numDocs
        << " out of " << m_parameters.m_inputs.numDocs << endl;
    ss << "Number of Relevant Documents: "
          << m_parameters.m_config.totalDocRelevancy << endl;
    ss <<  "Number of Search Queries: "
        << m_parameters.m_config.numFSs
        << " out of " << m_parameters.m_inputs.numFSs << endl;
    ss <<  "Combinations - The starting point: "
        << m_parameters.m_config.combStart << endl;
    ss <<  "Combinations - The number of Additional Smaller Neighbours: "
        << m_parameters.m_config.combSmaller << endl;
    ss <<  "Acceptable Minimum Sensitivity: "
        << m_parameters.m_config.minSensitiviy << endl;
    ss <<  "Filter Output by minimising search strategies length  "
        << std::boolalpha << m_parameters.m_config.filterMinimizeLength << endl;
    ss << "Filter Output in within Sensitivity Range of "
       << m_parameters.m_config.filterSensRange << "%" << endl;

    return ss.str();
}
