/*
$fileHeader$
*/

/*! \file transformChain.h
    \brief Declaration of TransformsChain.

*/

#if !defined(imebraTransformsChain__INCLUDED_)
#define imebraTransformsChain__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"
#include "transform.h"

namespace imebra
{
namespace implementation
{
namespace transforms
{
class transformsChain;
}
}
}

#endif

namespace imebra
{

class DrawBitmap;

class IMEBRA_API TransformsChain: public Transform
{
    TransformsChain(const TransformsChain&) = delete;
    TransformsChain& operator=(const TransformsChain&) = delete;

public:
    TransformsChain();

    void addTransform(const Transform& transform);
};

}

#endif // imebraTransformsChain__INCLUDED_
