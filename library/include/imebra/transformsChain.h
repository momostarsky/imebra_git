/*
$fileHeader$
*/

/*! \file transformChain_swig.h
	\brief Declaration of transformsChain for SWIG.

*/

#if !defined(imebraTransformsChain_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraTransformsChain_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#ifndef SWIG

#include <memory>

namespace puntoexe
{
namespace imebra
{
namespace transforms
{
class transformsChain;
}
}
}

#endif

#include "transform.h"

namespace imebra
{

class TransformsChain: public Transform
{

public:
    TransformsChain();

#ifndef SWIG
    TransformsChain(std::shared_ptr<puntoexe::imebra::transforms::transformsChain> pTransformsChain);
#endif

    void addTransform(const Transform& transform);
};

}

#endif // imebraTransformsChain_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
