/*
$fileHeader$
*/

/*! \file transformsChain.cpp
    \brief Implementation of the TransformsChain class.

*/

#include "../include/imebra/transformsChain.h"
#include "../implementation/transformsChainImpl.h"

namespace imebra
{

TransformsChain::TransformsChain(): Transform(std::make_shared<imebra::implementation::transforms::transformsChain>())
{
}

TransformsChain::~TransformsChain()
{
}

void TransformsChain::addTransform(const Transform& transform)
{
    ((imebra::implementation::transforms::transformsChain*)m_pTransform.get())->addTransform(transform.m_pTransform);
}

}
