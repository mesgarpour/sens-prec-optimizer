/*! \file parameters.cpp
    \brief the structured parameters that are being used by the algorithm
*/
/*! \fn parameters::parameters()
    \brief initilaise the parameters
*/
/*! void parameters::reset()
    \brief reset the inputs and configs parameters
*/
#include "parameters.h"

using namespace std;

parameters::parameters()
{
    reset();
}

void parameters::reset()
{
    m_inputs = strcInputParameters();
    m_config = strcConfigParameters();
}
