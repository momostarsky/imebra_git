/*
$fileHeader$
*/

/*! \file transformsHighBit.cpp
    \brief Implementation of the TransformsHighBit class.

*/

#include "../include/imebra/transformHighBit.h"
#include "../implementation/transformHighBitImpl.h"


namespace imebra
{

TransformHighBit::TransformHighBit(): Transform(std::make_shared<imebra::implementation::transforms::transformHighBit>())
{
}

TransformHighBit::~TransformHighBit()
{
}

}
