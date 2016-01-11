/*
$fileHeader$
*/

/*! \file colorTransformsFactory_swig.h
	\brief Declaration of the class ColorTransformsFactory for SWIG.

*/

#if !defined(imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#include "transform.h"
#include "definitions.h"

namespace imebra
{

class IMEBRA_API ColorTransformsFactory
{

public:

    static std::string normalizeColorSpace(const std::string& colorSpace);

    static bool isMonochrome(const std::string& colorSpace);

    static bool isSubsampledX(const std::string& colorSpace);

    static bool isSubsampledY(const std::string& colorSpace);

    static bool canSubsample(const std::string& colorSpace);

    static std::string makeSubsampled(const std::string& colorSpace, bool bSubsampleX, bool bSubsampleY);

    static int getNumberOfChannels(const std::string& colorSpace);

    static Transform getTransform(const std::string& startColorSpace, const std::string& endColorSpace);

};

}

#endif // imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
