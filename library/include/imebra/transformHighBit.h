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

///
/// \brief The TransformHighBit transform shifts the input image's values
///        so they match the high-bit settings of the Transform output image.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API TransformHighBit: public Transform
{
    TransformHighBit(const TransformHighBit&) = delete;
    TransformHighBit& operator=(const TransformHighBit&) = delete;

public:
    /// \brief Constructor.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    TransformHighBit();

};

}

#endif // imebraTransformHighBit__INCLUDED_
