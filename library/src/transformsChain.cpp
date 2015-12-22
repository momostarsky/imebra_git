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

TransformsChain::TransformsChain(): Transform(std::make_shared<puntoexe::imebra::transforms::transformsChain>())
{
}

TransformsChain::TransformsChain(std::shared_ptr<puntoexe::imebra::transforms::transformsChain> pTransform): Transform(pTransform)
{}

void TransformsChain::addTransform(const Transform& transform)
{
    ((puntoexe::imebra::transforms::transformsChain*)m_pTransform.get())->addTransform(transform.m_pTransform);
}

}
