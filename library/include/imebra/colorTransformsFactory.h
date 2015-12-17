/*
$fileHeader$
*/

/*! \file colorTransformsFactory_swig.h
	\brief Declaration of the class ColorTransformsFactory for SWIG.

*/

#if !defined(imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#include "transform.h"

namespace imebra
{

class ColorTransformsFactory
{

public:

    static std::wstring normalizeColorSpace(const std::wstring& colorSpace);

    static bool isMonochrome(const std::wstring& colorSpace);

    static bool isSubsampledX(const std::wstring& colorSpace);

    static bool isSubsampledY(const std::wstring& colorSpace);

    static bool canSubsample(const std::wstring& colorSpace);

    static std::wstring makeSubsampled(const std::wstring& colorSpace, bool bSubsampleX, bool bSubsampleY);

    static int getNumberOfChannels(const std::wstring& colorSpace);

    static Transform getTransform(const std::wstring& startColorSpace, const std::wstring& endColorSpace);

};

}

#endif // imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
