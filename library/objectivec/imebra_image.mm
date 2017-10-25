/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include <../include/imebra/imebra.h>
#import "../include/imebra/objectivec/imebra_nserror.h"
#import "../include/imebra/objectivec/imebra_image.h"
#import "../include/imebra/objectivec/imebra_readingDataHandlerNumeric.h"
#import "../include/imebra/objectivec/imebra_writingDataHandlerNumeric.h"
#import "../include/imebra/objectivec/imebra_strings.h"

#if defined(__APPLE__)

#include <memory>

#import <Foundation/Foundation.h>

namespace  imebra
{

void CGDataProviderCallbackFunc(void *info, const void *data, size_t size)
{
    // Release the shared pointer holding the memory
    ////////////////////////////////////////////////
    delete (imebra::ReadWriteMemory*)info;
}

#if TARGET_OS_IPHONE
UIImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap)
#else
NSImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap)
#endif
{
    // Get the amount of memory needed for the conversion
    /////////////////////////////////////////////////////
    std::uint32_t width(image.getWidth());
    std::uint32_t height(image.getHeight());

    // Get the result raw data
    //////////////////////////
    std::unique_ptr<imebra::ReadWriteMemory> pMemory(drawBitmap.getBitmap(image, imebra::drawBitmapType_t::drawBitmapRGBA, 4));
    size_t dataSize;
    char* pData = pMemory->data(&dataSize);

    // Create a CGImage, then convert it to NSImage or UIImage
    //////////////////////////////////////////////////////////
    CGDataProviderRef dataProviderRef = CGDataProviderCreateWithData(pMemory.release(),
                                                                pData,
                                                                dataSize,
                                                                CGDataProviderCallbackFunc);

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;

    CGImageRef imageRef = CGImageCreate(
                width, height,
                8, 32,
                width * 4,
                colorSpaceRef, bitmapInfo, dataProviderRef, NULL, YES, renderingIntent);


#if TARGET_OS_IPHONE
    UIImage* returnImage = [[UIImage alloc] initWithCGImage:imageRef];
#else
    NSImage* returnImage = [[NSImage alloc] initWithCGImage:imageRef size:NSZeroSize];
#endif
    CGDataProviderRelease(dataProviderRef);
    CGImageRelease(imageRef);
    CGColorSpaceRelease(colorSpaceRef);
    return returnImage;
}

} // namespace imebra

#endif

@implementation ImebraImage

-(id)initWithImebraImage:(imebra::Image*)pImage
{
    self =  [super init];
    if(self)
    {
        self->m_pImage = pImage;
    }
    return self;
}

-(id)initWithSize:(unsigned int)width height:(unsigned int)height depth:(ImebraBitDepth_t)depth colorSpace:(NSString*)colorSpace highBit:(unsigned int)highBit
{
    self =  [super init];
    if(self)
    {
        self->m_pImage = new imebra::Image(
                                 width,
                                 height,
                                 (imebra::bitDepth_t)depth,
                                 imebra::NSStringToString(colorSpace),
                                 highBit);
    }
    return self;
}

///
/// \ Destructor
///
///////////////////////////////////////////////////////////////////////////////
-(void)dealloc
{
    delete m_pImage;
}

-(ImebraReadingDataHandlerNumeric*) getReadingDataHandler:(NSError**)pError
{
    try
    {
        return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:m_pImage->getReadingDataHandler()];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraWritingDataHandlerNumeric*) getWritingDataHandler:(NSError**)pError
{
    try
    {
        return [[ImebraWritingDataHandlerNumeric alloc] initWithImebraWritingDataHandler:m_pImage->getWritingDataHandler()];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(double) widthMm
{
    return m_pImage->getWidthMm();
}

-(double) heightMm
{
    return m_pImage->getHeightMm();
}

-(unsigned int) width
{
    return m_pImage->getWidth();
}

-(unsigned int) height
{
    return m_pImage->getHeight();
}

-(NSString*) colorSpace
{
    return imebra::stringToNSString(m_pImage->getColorSpace());
}

-(unsigned int) getChannelsNumber
{
    return m_pImage->getChannelsNumber();
}

-(ImebraBitDepth_t) getDepth
{
    return (ImebraBitDepth_t)m_pImage->getDepth();
}

-(unsigned int) getHighBit
{
    return m_pImage->getHighBit();
}

@end

