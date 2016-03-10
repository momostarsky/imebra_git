/*
$fileHeader$
*/

/*! \file VOILUT.h
    \brief Declaration of the class VOILUT.

*/

#if !defined(imebraVOILUT__INCLUDED_)
#define imebraVOILUT__INCLUDED_

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
    double getCenter() const;
    double getWidth() const;


};

}

#endif // imebraVOILUT__INCLUDED_
