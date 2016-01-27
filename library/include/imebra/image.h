/*
$fileHeader$
*/

/*! \file image_swig.h
    \brief Declaration of the class image for SWIG.

*/

#if !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"
#include "dataHandler.h"

namespace imebra
{
namespace implementation
{
class image;
}
}
#endif

namespace imebra
{

class IMEBRA_API Image
{
public:

	///////////////////////////////////////////////////////////
	///
	/// \brief Define a single color component's size.
	///
	///////////////////////////////////////////////////////////
    enum class bitDepth
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
    Image(std::shared_ptr<imebra::implementation::image> pImage);
#endif

    WritingDataHandler create(
        const size_t sizeX,
        const size_t sizeY,
		const bitDepth depth,
        const std::string& colorSpace,
        const unsigned int highBit);

    void setHighBit(unsigned int highBit);

    double getSizeMmY() const;
    double getSizeMmX() const;

	void setSizeMm(const double sizeX, const double sizeY);

    size_t getSizeX() const;
    size_t getSizeY() const;

    ReadingDataHandler getReadingDataHandler() const;
    WritingDataHandler getWritingDataHandler();

    std::string getColorSpace() const;

    int getChannelsNumber() const;

    bitDepth getDepth() const;

    int getHighBit() const;

#ifndef SWIG
    std::shared_ptr<imebra::implementation::image> m_pImage;
#endif

};

}

#endif // !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
