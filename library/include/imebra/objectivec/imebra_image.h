/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcImage__INCLUDED_)
#define imebraObjcImage__INCLUDED_

#import <Foundation/Foundation.h>

namespace imebra
{
    class Image;
    class DrawBitmap;
}

#if defined(__APPLE__)
#include "TargetConditionals.h"

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/NSImage.h>
#endif

namespace imebra
{

#if TARGET_OS_IPHONE
/**
 * Generates a NSImage on OS-X or an UIImage on iOS from a 24bpp RGB data returned by
 * imebra::DrawBitmap::getBitmap().
 *
 * @param image      the image to pass as parameter to imebra::DrawBitmap::getBitmap()
 * @param drawBitmap the imebra::DrawBitmap object to use to generate the 24bpp RGB
 *                   representation of the DICOM image
 * @return           a UIImage initialized with the 24bpp RGB data returned by imebra::DrawBitmap
 */
IMEBRA_API UIImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);

#else

/**
 * Generates a NSImage on OS-X or an UIImage on iOS from a 24bpp RGB data returned by
 * imebra::DrawBitmap::getBitmap().
 *
 * @param image      the image to pass as parameter to imebra::DrawBitmap::getBitmap()
 * @param drawBitmap the imebra::DrawBitmap object to use to generate the 24bpp RGB
 *                   representation of the DICOM image
 * @return           a NSImage initialized with the 24bpp RGB data returned by imebra::DrawBitmap
 */
IMEBRA_API NSImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);
#endif

} // namespace imebra

#endif //__APPLE__

typedef NS_ENUM(unsigned int, ImebraBitDepth_t)
{
    depthU8 = 0,
    depthS8 = 1,
    depthU16 = 2,
    depthS16 = 3,
    depthU32 = 4,
    depthS32 = 5
};

@class ImebraReadingDataHandlerNumeric;
@class ImebraWritingDataHandlerNumeric;

@interface ImebraImage: NSObject
{
    @public
    imebra::Image* m_pImage;
}

    -(id)initWithImebraImage:(imebra::Image*)pImage;

    /// \brief Constructor.
    ///
    /// The memory for the image is not allocated by the constructor but only when
    /// a WritingDataHandler is requested with getWritingDataHandler().
    ///
    /// \param width      the image width, in pixels
    /// \param height     the image height, in pixels
    /// \param depth      the channel values data types
    /// \param colorSpace the Image's color space
    /// \param highBit    the highest bit occupied by the channels' values
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithSize:(unsigned int)width height:(unsigned int)height depth:(ImebraBitDepth_t)depth colorSpace:(NSString*)colorSpace highBit:(unsigned int)highBit;

    ///
    /// \ Destructor
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)dealloc;

    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandler:(NSError**)pError;

    -(ImebraWritingDataHandlerNumeric*) getWritingDataHandler:(NSError**)pError;

    @property double widthMm;

    @property double heightMm;

    @property (readonly) unsigned int width;

    @property (readonly) unsigned int height;

    @property (readonly) NSString* colorSpace;

    @property (readonly) unsigned int getChannelsNumber;

    @property (readonly) ImebraBitDepth_t getDepth;

    @property (readonly) unsigned int getHighBit;

@end

#endif // imebraObjcImage__INCLUDED_


