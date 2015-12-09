/*
$fileHeader$
*/

/*! \file image_swig.h
    \brief Declaration of the class image for SWIG.

*/

#if !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#ifndef SWIG

#include "../../implementation/baseObjectImpl.h"

namespace puntoexe
{
namespace imebra
{
class image;
}
}
#endif

#include "dataHandler.h"

class Image
{
public:

	///////////////////////////////////////////////////////////
	///
	/// \brief Define a single color component's size.
	///
	///////////////////////////////////////////////////////////
	enum bitDepth
	{
		depthU8 = 0,
		depthS8 = 1,
		depthU16 = 2,
		depthS16 = 3,
		depthU32 = 4,
		depthS32 = 5,
		endOfDepths = 6

	};

	// Constructor
	///////////////////////////////////////////////////////////
	Image();

	Image(const Image& right);

	Image& operator=(const Image& right);

#ifndef SWIG
	Image(puntoexe::ptr<puntoexe::imebra::image> pImage);
#endif

	DataHandler create(
		const int sizeX,
		const int sizeY,
		const bitDepth depth,
		std::wstring colorSpace,
		const int highBit);

	void setHighBit(int highBit);

	double getSizeMmY();
	double getSizeMmX();

	void setSizeMm(const double sizeX, const double sizeY);

	int getSizeX();
	int getSizeY();

	DataHandler getDataHandler(const bool bWrite);

	std::wstring getColorSpace();

	int getChannelsNumber();

	bitDepth getDepth();

	int getHighBit();

#ifndef SWIG
	puntoexe::ptr<puntoexe::imebra::image> m_pImage;
#endif

};



#endif // !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
