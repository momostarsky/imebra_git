/*
$fileHeader$
*/

/*! \file transformChain_swig.h
	\brief Declaration of transformsChain for SWIG.

*/

#if !defined(imebraTransformHighBit_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraTransformHighBit_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

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

#ifndef SWIG
    TransformHighBit(std::shared_ptr<imebra::implementation::transforms::transformHighBit> pTransformsHighBit);
#endif
};

}

#endif // imebraTransformHighBit_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
