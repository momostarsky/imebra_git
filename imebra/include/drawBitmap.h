/*
$fileHeader$
*/

/*! \file drawBitmap.h
    \brief Declaration of the a class that draw an image into a bitmap.

This file is not included automatically by imebra.h

*/

#if !defined(imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include "transform.h"
#include "../../base/include/memory.h"
#include <memory>

namespace puntoexe
{

namespace imebra
{

namespace transforms
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This transform takes an image as an input and
///         returns an 8 bit RGB bitmap of the requested
///         image's area; the image's area is expanded or
///         reduced to fit into the destination bitmap's
///         size.
///
/// The transform processes only the first declared image.
/// A requirement of this transform is that the dataSet has
///  to be declared before the input image; this means
///  that declareDataSet() has to be called before
///  declareInputImage().
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmap: public transform
{
public:
	drawBitmap();

	// Documented in transform
	virtual void declareInputImage(long imageNumber, ptr<image> pInputImage);
	
	// Documented in transform
	virtual void doTransform();

	/// \brief Declare the total size of a bitmap that contains
	///         the entire image and the rectangle of that
	///         bitmap that has to be generated.
	///         A subsequent call to getOutputBitmap() will
	///         return the requested bitmap.
	///
	/// This class is used by the class view.
	///
	/// @param totalWidthPixels   the width of the bitmap that
	///                            contains the whole image
	///                            declared with 
	///                            declareInputImage()
	/// @param totalHeightPixels  the width of the bitmap that
	///                            contains the whole image
	///                            declared with 
	///                            declareInputImage()
	/// @param visibleTopLeftX    the horizontal coordinate of
	///                            the top-left corner of the
	///                            destination bitmap's 
	///                            rectangle that has to be
	///                            updated
	/// @param visibleTopLeftY    the vertical coordinate of
	///                            the top-left corner of the
	///                            destination bitmap's 
	///                            rectangle that has to be
	///                            updated
	/// @param visibleBottomRightX the horizontal coordinate of
	///                            the bottom-right corner of
	///                            the destination bitmap's 
	///                            rectangle that has to be
	///                            updated
	/// @param visibleBottomRightY the vertical coordinate of
	///                            the bottom-right corner of
	///                            the destination bitmap's 
	///                            rectangle that has to be
	///                            updated
	/// @param alignByte          the number of bytes used to
	///                            align each row of the
	///                            returned bitmap
	/// @param bBGR               true if the returned bitmap
	///                            has to be in the BGR format,
	///                            false if it has to be in RGB
	///                            format
	///         
	///////////////////////////////////////////////////////////
	void declareBitmapType(imbxInt32 totalWidthPixels, imbxInt32 totalHeightPixels, 
		imbxInt32 visibleTopLeftX, imbxInt32 visibleTopLeftY, imbxInt32 visibleBottomRightX, imbxInt32 visibleBottomRightY,
		imbxInt32 alignByte,
		bool bBGR);

	/// \brief Returns a pointer to a bitmap that can be used
	///         to update the area defined by the parameters
	///         visibleTopLeftX, visibleTopLeftY, 
	///         visibleBottomRightX, visibleBottomRightY in
	///         the function declareBitmapType().
	///
	/// @param pWidthPixels      a pointer to a variable that
	///                           will by filled with the
	///                           returned bitmap's width, in
	///                           pixels
	/// @param pHeightPixels     a pointer to a variable that
	///                           will be filled with the
	///                           returned bitmap's height, in
	///                           pixels
	/// @param pRowLengthBytes   a pointer to a variable that
	///                           will be filled with the
	///                           image's rows' length, in
	///                           bytes
	///
	///////////////////////////////////////////////////////////
	imbxUint8* getOutputBitmap(imbxInt32* pWidthPixels, imbxInt32* pHeightPixels, imbxInt32* pRowLengthBytes);

protected:
	// Width of the bitmap that contains all the image, in 
	//  pixels.
	//
	///////////////////////////////////////////////////////////
	imbxInt32 m_totalWidthPixels;
	
	// Height of the bitmap that contains all the image, in 
	//  pixels.
	//
	///////////////////////////////////////////////////////////
	imbxInt32 m_totalHeightPixels;

	// Top left visible pixel.
	//
	///////////////////////////////////////////////////////////
	imbxInt32 m_visibleTopLeftX;
	imbxInt32 m_visibleTopLeftY;

	// Bottom right visible pixel.
	//
	///////////////////////////////////////////////////////////
	imbxInt32 m_visibleBottomRightX;
	imbxInt32 m_visibleBottomRightY;

	imbxInt32 m_alignByte;
	bool m_bBGR;


	// Width of the latest generated bitmap, in pixels
	imbxInt32 m_destBitmapWidth;
	imbxInt32 m_destBitmapHeight;
	imbxInt32 m_destBitmapRowSize;

	std::auto_ptr<imbxInt32> m_averagePixels;
	std::auto_ptr<imbxUint32> m_sourcePixelIndex;


	ptr<memory> m_finalBitmap;

private:
	ptr<image> m_pTemporaryImage;
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Base class used for the exceptions thrown by
///         drawBitmap.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapException: public transformException
{
public:
	drawBitmapException(const std::string& message): transformException(message){}
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by 
///         declareInputImage() if the dataSet hasn't been
///         declared yet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionDataSetNotDeclared: public drawBitmapException
{
public:
	drawBitmapExceptionDataSetNotDeclared(const std::string& message): drawBitmapException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by 
///         doTransform() if the image hasn't been declared
///         yet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionImageNotDeclared: public drawBitmapException
{
public:
	drawBitmapExceptionImageNotDeclared(const std::string& message): drawBitmapException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by 
///         declareBitmapType() if the image's area that
///         has to be generated is not valid.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionInvalidArea: public drawBitmapException
{
public:
	drawBitmapExceptionInvalidArea(const std::string& message): drawBitmapException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by 
///         declareBitmapType() if the align byte is
///         illegal (1, 2 and 4 are the typical values).
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class drawBitmapExceptionInvalidAlignByte: public drawBitmapException
{
public:
	drawBitmapExceptionInvalidAlignByte(const std::string& message): drawBitmapException(message){}
};




} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDrawBitmap_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)

