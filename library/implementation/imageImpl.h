/*
$fileHeader$
*/

/*! \file image.h
    \brief Declaration of the class image.

*/

#if !defined(imebraImage_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraImage_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#include <memory>
#include "dataHandlerNumericImpl.h"

///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

    namespace handlers
    {
        class dataHandlerNumericBase;
    }

class palette;
class buffer;

/// \addtogroup group_image Image data
/// \brief The class image contains the data of one DICOM image.
///
/// The image's data includes:
/// - the image's size, in pixels
/// - the image's size, in millimeters
/// - the bit depth (bytes per color channel) and high
///   bit
/// - the color palette (if available)
/// - the pixels' data
///
/// An image can be obtained from a dataSet object by
///  calling dataSet::getImage(), or it can be initialized
///  with image::create().
///
/// Images can also be allocated by the transforms
///  by calling
///  transforms::transform::allocateOutputImage().
///
/// @{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Represents a single image of a dicom data set.
///
/// Images are embedded into the dicom structures
///  (represented by the dataSet class), stored in
///  a compressed format.
///
/// The class image represents a decompressed raw image,
///  extracted from a dicom structure using
///  dataSet::getImage().
///
/// image objects can also be created by the
///  application and stored into a dicom structure using
///  the function dataSet::setImage().
///
/// The image and its buffer share a common lock object:
///  this means that a lock to the image object will also
///  locks the image's buffer and viceversa.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class image
{
public:

	///////////////////////////////////////////////////////////
	///
	/// \brief Define the number of allocated bytes per
	///        value.
	///
	///////////////////////////////////////////////////////////
	enum bitDepth
	{
			depthU8,    ///< unsigned integer, 1 byte
			depthS8,    ///< signed integer, 1 byte
			depthU16,   ///< unsigned integer, 2 bytes
			depthS16,   ///< signed integer, 2 bytes
			depthU32,   ///< unsigned integer, 4 bytes
			depthS32,   ///< signed integer, 4 bytes
            endOfDepths

	};

	// Constructor
	///////////////////////////////////////////////////////////
	image():
			m_rowLength(0),
			m_channelsNumber(0),
			m_imageDepth(depthU8),
			m_highBit(0),
			m_sizeX(0),
			m_sizeY(0),
			m_sizeMmX(0),
			m_sizeMmY(0){}


	/// \brief Create the image.
	///
	/// An image with the specified size (in pixels), bit depth
	///  and color space is allocated.
	/// The number of channels to allocate is automatically
	///  calculated using the colorSpace parameter.
	///
	/// @param sizeX    the image's width, in pixels.
	/// @param sizeY    the image's height, in pixels.
	/// @param depth    the size of a single color's component.
	/// @param colorSpace The color space as defined by the
	///                 DICOM standard.
	///                 Valid colorspace are:
	///                 - "RGB"
	///                 - "YBR_FULL"
	///                 - "YBR_PARTIAL"
	///                 - "YBR_RCT" (Not yet supported)
	///                 - "YBR_ICT" (Not yet supported)
	///                 - "PALETTE COLOR"
	///                 - "MONOCHROME2"
	///                 - "MONOCHROME1"
	/// @param highBit  the highest bit used for integer
	///                  values.
	/// @return         the data handler containing the image's
	///                  data
	///
	///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::writingDataHandlerNumericBase> create(
		const std::uint32_t sizeX,
		const std::uint32_t sizeY,
		const bitDepth depth,
		std::wstring colorSpace,
		const std::uint8_t  highBit);

	/// \brief Set the high bit.
	///
	/// @param highBit       the image's high bit
	///
	///////////////////////////////////////////////////////////
	void setHighBit(std::uint32_t highBit);

	/// \brief Set the palette for the image
	///
	/// @param imagePalette  the palette used in the image
	///
	///////////////////////////////////////////////////////////
	void setPalette(std::shared_ptr<palette> imagePalette);

	/// \brief Retrieve the image's size, in millimeters.
	///
	/// The image's size in millimeters is automatically read
	///  from the dicom structure or can be set using
	///  setSizeMm().
	///
	/// @param pSizeX a pointer to the variable to fill with
	///               the image's width (in millimeters).
	/// @param pSizeY a pointer to the variable to fill with
	///               the image's height (in millimeters).
	///////////////////////////////////////////////////////////
	void getSizeMm(double* pSizeX, double* pSizeY);

	/// \brief Set the image's size, in millimeters.
	///
	/// @param sizeX the new image's width, in millimeters.
	/// @param sizeY the new image's height, in millimeters.
	///
	///////////////////////////////////////////////////////////
	void setSizeMm(const double sizeX, const double sizeY);

	/// \brief Get the image's size, in pixels.
	///
	/// @param pSizeX a pointer to the variable to fill with
	///               the image's width (in pixels).
	/// @param pSizeY a pointer to the variable to fill with
	///               the image's height (in pixels).
	///
	///////////////////////////////////////////////////////////
	void getSize(std::uint32_t* pSizeX, std::uint32_t* pSizeY);

	/// \brief Retrieve a data handler for managing the
	///        image's buffer
	///
	/// The retrieved data handler gives access to the image's
	///  buffer.
	/// The image's buffer stores the data in the following
	///  format:
	/// - when multiple channels are present, then the channels
	///   are ALWAYS interleaved
	/// - the channels are NEVER subsampled or oversampled.
	///   The subsampling/oversampling is done by the codecs
	///   when the image is stored or loaded from the dicom
	///   structure.
	/// - the first stored value represent the first channel of
	///   the top/left pixel.
	/// - each row is stored countiguously, from the top to the
	///   bottom.
	///
	/// @param bWrite   true if the application wants to write
	///                 into the buffer, false otherwise.
	/// @param pRowSize the function will fill the variable
	///                 pointed by this parameter with
	///                 the size of a single row, in bytes.
	/// @param pChannelPixelSize the function will fill the
	///                 variable pointed by this parameter with
	///                 the size of a single pixel,
	///                 in bytes.
	/// @param pChannelsNumber  the function will fill the
	///                 variable pointed by this parameter with
	///                 the number of channels per pixel.
	/// @return a pointer to the data handler for the image's
	///         buffer.
	///
	///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::readingDataHandlerNumericBase> getReadingDataHandler() const;

    std::shared_ptr<handlers::writingDataHandlerNumericBase> getWritingDataHandler();

    /// \brief Get the image's color space (DICOM standard)
	///
	/// @return a string with the image's color space
	///
	///////////////////////////////////////////////////////////
	std::wstring getColorSpace();

	/// \brief Get the number of allocated channels.
	///
	/// @return the number of color channels in the image
	///
	///////////////////////////////////////////////////////////
	std::uint32_t getChannelsNumber();

	/// \brief Get the image's bit depth.
	///
	/// The bit depth indicates the number of bits used to
	///  store every single value.
	///
	/// @return the bit depth.
	///////////////////////////////////////////////////////////
	bitDepth getDepth();

	/// \brief Get the high bit.
	///
	/// @return the image's high bit
	///
	///////////////////////////////////////////////////////////
	std::uint32_t getHighBit();

        std::shared_ptr<palette> getPalette();


protected:
	// Image's buffer
	///////////////////////////////////////////////////////////
	std::shared_ptr<buffer> m_buffer;

	// Lenght of a buffer's row (in bytes)
	///////////////////////////////////////////////////////////
	std::uint32_t m_rowLength;

	// Number of channels
	///////////////////////////////////////////////////////////
	std::uint32_t  m_channelsNumber;

	// Color space
	///////////////////////////////////////////////////////////
	std::wstring m_colorSpace;

	// Depth (enum)
	///////////////////////////////////////////////////////////
	bitDepth  m_imageDepth;

	// High bit (not valid in float mode)
	///////////////////////////////////////////////////////////
	std::uint32_t m_highBit;

	// Image's size in pixels
	///////////////////////////////////////////////////////////
	std::uint32_t m_sizeX;
	std::uint32_t m_sizeY;

	// Image's size in millimeters
	///////////////////////////////////////////////////////////
	double m_sizeMmX;
	double m_sizeMmY;

	// Image's lut (only if the colorspace is PALETTECOLOR
	///////////////////////////////////////////////////////////
        std::shared_ptr<palette> m_palette;

};


/// @}

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraImage_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
