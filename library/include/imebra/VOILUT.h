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

    unsigned int getVOILUTId(unsigned int VOILUTNumber) const;
    std::wstring getVOILUTDescription(int VOILUTId) const;
	void setVOILUT(int VOILUTId);
    void applyOptimalVOI(Image inputImage, unsigned int topLeftX, unsigned int topLeftY, unsigned int width, unsigned int height);
	//void setLUT(std::shared_ptr<lut> pLut);
	void setCenterWidth(int center, int width);
    int getCenter() const;
    int getWidth() const;


};

}

#endif // imebraVOILUT_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
