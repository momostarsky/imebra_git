/*
$fileHeader$
*/

/*! \file VOILUT_swig.h
	\brief Declaration of the class VOILUT for SWIG.

*/

#if !defined(imebraVOILUT_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraVOILUT_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

#include "transform.h"

namespace imebra
{

class DataSet;

class VOILUT: public Transform
{

public:
    VOILUT(const DataSet& dataset);

    int getVOILUTId(int VOILUTNumber) const;
    std::wstring getVOILUTDescription(int VOILUTId) const;
	void setVOILUT(int VOILUTId);
	void applyOptimalVOI(Image inputImage, int topLeftX, int topLeftY, int width, int height);
	//void setLUT(std::shared_ptr<lut> pLut);
	void setCenterWidth(int center, int width);
    int getCenter() const;
    int getWidth() const;


};

}

#endif // imebraVOILUT_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_
