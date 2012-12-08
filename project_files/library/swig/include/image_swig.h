/*
$fileHeader$
*/

/*! \file image_swig.h
    \brief Declaration of the class image for SWIG.

*/


#if !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#ifndef SWIG
#include "../../imebra/include/image.h"
#endif



class image
{
public:

	///////////////////////////////////////////////////////////
	///
	/// \brief Define a single color component's size.
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
	image();

	image(const image& right);

	image& operator=(const image& right);

	dataHandlerNumericBase create(
		const long sizeX,
		const long sizeY,
		const bitDepth depth,
		std::wstring colorSpace,
		const long  highBit);

	/// \brief Set the high bit.
	///
	/// @param highBit       the image's high bit
	///
	///////////////////////////////////////////////////////////
	void setHighBit(long highBit);

	/*
	/// \brief Set the palette for the image
	///
	/// @param imagePalette  the palette used in the image
	///
	///////////////////////////////////////////////////////////
	void setPalette(ptr<palette> imagePalette);
	*/

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
	void getSize(imbxUint32* pSizeX, imbxUint32* pSizeY);

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
	dataHandlerNumericBase getDataHandler(
		const bool bWrite,
		imbxUint32* pRowSize,
		imbxUint32* pChannelPixelSize,
		imbxUint32* pChannelsNumber);

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
	long getChannelsNumber();

	/// \brief Get the image's bit depth.
	///
	/// The bit depth indicates how every single value is
	///  stored into the image's buffer.
	///
	/// @return the bit depth.
	///////////////////////////////////////////////////////////
	bitDepth getDepth();

	/// \brief Get the high bit.
	///
	/// @return the image's high bit
	///
	///////////////////////////////////////////////////////////
	long getHighBit();

	/*
        ptr<palette> getPalette();
*/

#ifndef SWIG
protected:
	puntoexe::ptr<puntoexe::imebra::image> m_pImage;
#endif

};


///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the image class.
///
///////////////////////////////////////////////////////////
class imageException: public std::runtime_error
{
public:
	/// \brief Build a codec exception
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	imageException(const std::string& message): std::runtime_error(message){}
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown depth
///         is specified as a parameter.
///
///////////////////////////////////////////////////////////
class imageExceptionUnknownDepth: public imageException
{
public:
	imageExceptionUnknownDepth(const std::string& message): imageException(message){}
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown color
///         space is specified in the function create().
///
///////////////////////////////////////////////////////////
class imageExceptionUnknownColorSpace: public imageException
{
public:
	imageExceptionUnknownColorSpace(const std::string& message): imageException(message){}
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an invalid size
///         in pixels is specified in the function
///         create().
///
///////////////////////////////////////////////////////////
class imageExceptionInvalidSize: public imageException
{
public:
	imageExceptionInvalidSize(const std::string& message): imageException(message){}
};

/// @}


#endif // !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
