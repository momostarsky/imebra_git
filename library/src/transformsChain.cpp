/*
$fileHeader$
*/

/*! \file transformsChain_swig.cpp
    \brief Implementation of the TransformsChain class for SWIG.

*/

#include "../include/imebra/transformsChain.h"
#include "../implementation/transformsChainImpl.h"

namespace imebra
{

TransformsChain::TransformsChain(): Transform(std::make_shared<imebra::implementation::transforms::transformsChain>())
{
}

TransformsChain::TransformsChain(std::shared_ptr<imebra::implementation::transforms::transformsChain> pTransform): Transform(pTransform)
{}

void TransformsChain::addTransform(const Transform& transform)
{
    ((imebra::implementation::transforms::transformsChain*)m_pTransform.get())->addTransform(transform.m_pTransform);
}

}
