/*
$fileHeader$
*/

/*! \file transformsChain_swig.cpp
    \brief Implementation of the TransformsChain class for SWIG.

*/

#include "../include/imebra/transformHighBit.h"
#include "../implementation/transformHighBitImpl.h"


namespace imebra
{

TransformHighBit::TransformHighBit(): Transform(std::make_shared<imebra::implementation::transforms::transformHighBit>())
{
}

TransformHighBit::TransformHighBit(std::shared_ptr<imebra::implementation::transforms::transformHighBit> pTransform): Transform(pTransform)
{}

}
