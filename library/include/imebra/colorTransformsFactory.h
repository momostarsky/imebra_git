/*
$fileHeader$
*/

/*! \file colorTransformsFactory_swig.h
	\brief Declaration of the class ColorTransformsFactory for SWIG.

*/

#if !defined(imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#include "transform.h"

class ColorTransformsFactory
{

public:

	static std::wstring normalizeColorSpace(std::wstring colorSpace);

	static bool isMonochrome(std::wstring colorSpace);

	static bool isSubsampledX(std::wstring colorSpace);

	static bool isSubsampledY(std::wstring colorSpace);

	static bool canSubsample(std::wstring colorSpace);

	static std::wstring makeSubsampled(std::wstring colorSpace, bool bSubsampleX, bool bSubsampleY);

	static int getNumberOfChannels(std::wstring colorSpace);

	static Transform getTransform(std::wstring startColorSpace, std::wstring endColorSpace);

};

#endif // imebraColorTransformsFactory_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
