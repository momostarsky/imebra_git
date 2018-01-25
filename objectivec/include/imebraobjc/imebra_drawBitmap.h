/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDrawBitmap__INCLUDED_)
#define imebraObjcDrawBitmap__INCLUDED_

#import <Foundation/Foundation.h>
#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/NSImage.h>
#endif

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
    class DrawBitmap;
}
#endif

@class ImebraImage;
@class ImebraTransform;
@class ImebraReadWriteMemory;

typedef NS_ENUM(unsigned int, ImebraDrawBitmapType_t)
{
    ImebraDrawBitmapRGB  = 0, ///< Generates a BMP image where each pixel contains 3 bytes (R, G and B)
    ImebraDrawBitmapBGR  = 1, ///< Generates a BMP image where each pixel contains 3 bytes (B, G and R)
    ImebraDrawBitmapRGBA = 2, ///< Generates a BMP image where each pixel contains 4 bytes (R, G, B and A)
    ImebraDrawBitmapBGRA = 3  ///< Generates a BMP image where each pixel contains 4 bytes (B, G, R and A)
};


@interface ImebraDrawBitmap: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    imebra::DrawBitmap* m_pDrawBitmap;
}

#endif

    -(id)init;

    -(id)initWithTransform:(ImebraTransform*)pTransform;

    -(void)dealloc;

    /// \brief Apply the transforms defined in the constructor (if any) to the
    ///        input image, then calculate an array of bytes containing a bitmap
    ///        that can be rendered by the operating system.
    ///
    /// \param image          the image for which the bitmap must be calculated
    /// \param drawBitmapType the type of bitmap to generate
    /// \param rowAlignBytes  the number of bytes on which the bitmap rows are
    ///                       aligned
    /// \return a ReadWriteMemory object referencing the buffer containing the
    ///         generated bitmap
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraReadWriteMemory*) getBitmap:(ImebraImage*)pImage bitmapType:(ImebraDrawBitmapType_t) drawBitmapType rowAlignBytes:(unsigned int)rowAlignBytes error:(NSError**)pError;

#if defined(__APPLE__)

#if TARGET_OS_IPHONE
    -(UIImage*)getImebraImage:(ImebraImage*)pImage error:(NSError**)pError;
#else
    -(NSImage*)getImebraImage:(ImebraImage*)pImage error:(NSError**)pError;
#endif

#endif

@end

#endif // imebraObjcDrawBitmap__INCLUDED_


