/*! \file readFile.cpp
    \brief read the input file and set the inputs and configs parameters

    \see parameters
    \see mainwindow
    \see logger
*/
/*! \fn readFile::readFile()
    \brief initialise the internal parameters
*/
/*! \fn void readFile::set(
        parameters &parameters)
    \brief read the input file and set the parameters

    \param parameters an instance of the parameters
    \see readFile::validateDomains
    \see readFile::line
    \see readFile::conversions
*/
/*! \fn void readFile::validateDomains(parameters &parameters)
    \brief validate the configured domins based on the input file

    \param parameters an instance of the parameters
*/
/*! \fn void readFile::line(
        const string &line,
        vector<string> &id,
        vector<temp> &output,
        const unsigned int iStart)
    \brief read a row of the file

    \param line the current line
    \param id the row header
    \param output the row values as a vector
    \param iStart the number of the first cell that holds a value
*/
/*! \fn void readFile::conversions(parameters &parameters)
    \brief apply the conversions on the parameetrs

    \param parameters an instance of the parameters
*/
/*! \fn bool readFile::isNumber(const string &arg)
    \brief check if the input argument is number

    \return true if the input argument is number
*/
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <math.h>
#include <numeric>
#ifndef Q_MOC_RUN
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#endif //Q_MOC_RUN
#include "readFile.h"
#include "Global.h"

using namespace std;
namespace bst = boost;

readFile::readFile():
    m_numColsRead(0)
{
    m_log.reset();
}

void readFile::set(
        parameters &parameters)
{
    m_log.reset();
    ifstream file(parameters.m_config.inputFile.c_str());
    string line;
    string strLineStream;
    stringstream lineStream;
    parameters.m_inputs.numFSs = 0;
    m_numColsRead = 0;

    //Read
    do
    {
        if(!file)
        {
            m_log.appendMsg("Invalid input file!\n", true);
            return;
        }

        //get lines
        lineStream << file.rdbuf();
        file.close();

        //Correct EOF: replace "\r or" "\r\n" by "\n"
        strLineStream = lineStream.str();
        bst::replace_all(strLineStream, "\r\n", "\n");
        bst::replace_all(strLineStream, "\r", "\n");
        lineStream.str(strLineStream);

        //read first line (headers)
        getline(lineStream, line);
        this->line<unsigned int>(line, parameters.m_inputs.relvancyIDs,
                        parameters.m_inputs.docsIDs, 1);
        if(m_log.getErrors()) break;

        //read second line (relevancies)
        getline(lineStream, line);
        this->line<bool>(line, parameters.m_inputs.relvancyIDs,
                         parameters.m_inputs.docsRelevancy, 1);
        if(m_log.getErrors()) break;

        //read the FSs&Docs (search queries relevancies for docs)
        while(getline(lineStream, line))
        {
            parameters.m_inputs.docsFSs.push_back(vector<bool>());
            this->line<bool>(line, parameters.m_inputs.fsIDs,
                       parameters.m_inputs.docsFSs.
                       at(parameters.m_inputs.numFSs), 1);
            if(m_log.getErrors()) break;
            parameters.m_inputs.numFSs ++;
        };

        //set num docs (columns) and FSs (rows) have been read
        parameters.m_inputs.numDocs =
                parameters.m_inputs.docsFSs.at(0).size();

        //Set total relevancy
        parameters.m_inputs.totalDocRelevancy =
                    accumulate(parameters.m_inputs.docsRelevancy.begin(),
                               parameters.m_inputs.docsRelevancy.begin() +
                               parameters.m_inputs.numDocs,
                               0);

        //Set Default Configs
        parameters.m_config.numDocs = parameters.m_inputs.numDocs;
        parameters.m_config.numFSs = parameters.m_inputs.numFSs;
        if(parameters.m_config.defaultInputDataConfig)
        {
            parameters.m_config.totalDocRelevancy =
                    parameters.m_inputs.totalDocRelevancy;
        }
    }while(false);

    file.close();
    conversions(parameters);
    validateDomains(parameters);
}

void readFile::validateDomains(parameters &parameters)
{
    if(m_log.getErrors())
    {
        m_log.appendMsg("File structure Could not be recognised!\n", true);
        return;
    }

    if(parameters.m_inputs.numDocs == 0 ||
            parameters.m_inputs.numDocs == 0 ||
            parameters.m_inputs.numDocs > MAX_DOCS ||
            parameters.m_inputs.numDocs > MAX_DOCS ||
            parameters.m_inputs.numDocs < parameters.m_config.numDocs ||
            parameters.m_inputs.numFSs > MAX_FSS ||
            parameters.m_inputs.numFSs < parameters.m_config.numFSs ||
            parameters.m_config.totalDocRelevancy < 0)
    {
        m_log.appendMsg("Invalid files's parameter(s) defined!\n", true);
        return;
    }
}

//ToDo: catch the exception for string to int
template <typename temp>
void readFile::line(
        const string &line,
        vector<string> &id,
        vector<temp> &output,
        const unsigned int iStart)
{
    bst::char_separator<char> seperator(FILE_INPUT_DELIMITER);
    bst::tokenizer<bst::char_separator<char> > cells(line, seperator);
    unsigned int cntCell = 0;

    BOOST_FOREACH(const string& cell, cells)
    {
        cntCell++;
        //skip the cells
        if(cntCell < iStart)
            continue;
        //push the cells
        if(cell.size() < 1 || cell.compare("") == 0)
        {
            m_numColsRead = 0;
            break;
        }
        //read id
        if(cntCell == iStart)
        {
            id.push_back(cell.c_str());
            continue;
        }
        //read record
      //if(is_base_of<temp, string>::value != 1 && isNumber(cell))
        output.push_back(atoi(cell.c_str()));
    }
    //validate number of columns read
    if(m_numColsRead == 0)
        m_numColsRead = cntCell;
    else if(m_numColsRead != cntCell)
    {
        m_log.appendMsg("Invalid cell(s) in the file!\n", true);
        return;
    }

}

//Conversions
void readFile::conversions(parameters &parameters)
{
    parameters.m_config.combStart = ceil(
                parameters.m_config.combStart *
                parameters.m_config.numFSs * 0.01);//ToDo: Move it to the algo

    if(parameters.m_config.combStart < 2)
        parameters.m_config.combStart = 2;
    else if(parameters.m_config.combStart >
            parameters.m_config.numFSs)
        parameters.m_config.combStart =
                parameters.m_config.numFSs;
}

//Check if the argumnent is number using std::isdigit function
bool readFile::isNumber(const string &arg)
{
    if(arg.empty())
        return false;
    for(string::const_iterator s = arg.begin();
        s != arg.end();
        s++)
    {
        if(!isdigit(*s))
            return false;
    }
    return true;
}
