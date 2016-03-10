/*
$fileHeader$
*/

/*! \file colorTransformsFactory.h
    \brief Declaration of the class ColorTransformsFactory.

*/

#if !defined(imebraColorTransformsFactory__INCLUDED_)
#define imebraColorTransformsFactory__INCLUDED_

#include <string>
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

    static std::uint32_t getNumberOfChannels(const std::string& colorSpace);

    static Transform getTransform(const std::string& startColorSpace, const std::string& endColorSpace);

};

}

#endif // imebraColorTransformsFactory__INCLUDED_
