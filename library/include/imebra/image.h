/*
$fileHeader$
*/

/*! \file image.h
    \brief Declaration of the class Image.

*/

#if !defined(imebraImage__INCLUDED_)
#define imebraImage__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"
#include "readingDataHandlerNumeric.h"
#include "writingDataHandlerNumeric.h"

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

class CodecFactory;
class Transform;
class VOILUT;
class DataSet;
class DrawBitmap;

class IMEBRA_API Image
{
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

#ifndef SWIG
    friend class CodecFactory;
    friend class Transform;
    friend class VOILUT;
    friend class DataSet;
    friend class DrawBitmap;

private:
    Image(std::shared_ptr<imebra::implementation::image> pImage);
#endif

public:

    Image(
        std::uint32_t width,
        std::uint32_t height,
        bitDepth_t depth,
        const std::string& colorSpace,
        std::uint32_t highBit);

    virtual ~Image();

    double getWidthMm() const;
    double getHeightMm() const;

    void setSizeMm(const double width, const double height);

    std::uint32_t getWidth() const;
    std::uint32_t getHeight() const;

    ReadingDataHandlerNumeric* getReadingDataHandler() const;
    WritingDataHandlerNumeric* getWritingDataHandler();

    std::string getColorSpace() const;

    std::uint32_t getChannelsNumber() const;

    bitDepth_t getDepth() const;

    std::uint32_t getHighBit() const;

#ifndef SWIG
protected:
    std::shared_ptr<implementation::image> m_pImage;
#endif

};

}

#endif // !defined(imebraImage__INCLUDED_)
