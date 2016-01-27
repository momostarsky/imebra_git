/*
$fileHeader$
*/

/*! \file modalityVOILUT_swig.cpp
    \brief Implementation of the ModalityVOILUT class for SWIG.

*/


#include "../include/imebra/modalityVOILUT.h"
#include "../implementation/modalityVOILUTImpl.h"

namespace imebra
{

ModalityVOILUT::ModalityVOILUT(const DataSet& dataset): Transform(std::make_shared<imebra::implementation::transforms::modalityVOILUT>(dataset.m_pDataSet))
{
}

}
