/*
$fileHeader$
*/

/*! \file transformChain.h
    \brief Declaration of TransformsHighBit.

*/

#if !defined(imebraTransformHighBit__INCLUDED_)
#define imebraTransformHighBit__INCLUDED_

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
class transformHighBit;
}
}
}

#endif

namespace imebra
{

class IMEBRA_API TransformHighBit: public Transform
{
public:
    TransformHighBit();

};

}

#endif // imebraTransformHighBit__INCLUDED_
