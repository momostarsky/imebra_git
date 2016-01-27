/*
$fileHeader$
*/

/*! \file VOILUT_swig.h
	\brief Declaration of the class VOILUT for SWIG.

*/

#if !defined(imebraVOILUT_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraVOILUT_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#include "transform.h"
#include "definitions.h"

namespace imebra
{

class DataSet;

class IMEBRA_API VOILUT: public Transform
{

public:
    VOILUT(const DataSet& dataset);

    std::uint32_t getVOILUTId(std::uint32_t VOILUTNumber) const;
    std::wstring getVOILUTDescription(std::uint32_t VOILUTId) const;
    void setVOILUT(std::uint32_t VOILUTId);
    void applyOptimalVOI(Image inputImage, std::uint32_t topLeftX, std::uint32_t topLeftY, std::uint32_t width, std::uint32_t height);
	//void setLUT(std::shared_ptr<lut> pLut);
    void setCenterWidth(std::int32_t center, std::int32_t width);
    std::int32_t getCenter() const;
    std::int32_t getWidth() const;


};

}

#endif // imebraVOILUT_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
