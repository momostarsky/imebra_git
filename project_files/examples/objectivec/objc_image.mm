/**
 * This is a simple objective-c class that calls some method on the imebra library.
 *
 * The most problematic part is the conversion from NSString to wstring and viceversa.
 *
 * Other data types can be used natively (e.g. int, imbxInt16, double, etc).
 *
 */

#include "../../library/imebra/include/imebra.h"
#import "objc_dataset.h"
#import "objc_image.h"
#import "objc_helpers.h"



@implementation ImebraImage

- initWithImebraImage: (puntoexe::ptr<puntoexe::imebra::image>) image
{
    if(self = [super init])
    {
        m_image = image;
    }
}

- (long) getWidth
{
    imbxUint32 width, height;
    m_image->getSize(&width, &height);
    return width;
}

- (long) getHeight
{
    imbxUint32 width, height;
    m_image->getSize(&width, &height);
    return height;
}

#ifdef TARGET_OS_IPHONE
- (UIImage*) getUIImage
{
    imbxUint32 width, height;
    m_image->getSize(&width, &height);
    imbxUint32 rowSize, channelPixelSize, channelsNumber;
    puntoexe::ptr<puntoexe::imebra::handlers::dataHandlerNumericBase> dataHandler = m_image->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                                dataHandler->getMemoryBuffer(),
                                                                width * height * 4,
                                                                NULL);

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    CGImageRef imageRef = CGImageCreate(width,
                                    height,
                                    8,
                                    32,
                                    rowSize,colorSpaceRef,
                                    bitmapInfo,
                                    provider, NULL, NO, renderingIntent);

    return [[[UIImage alloc] imageWithCGImage:imageRef] autorelease];
}

#else

- (NSImage*) GetNSImage
{
    imbxUint32 width, height;
    m_image->getSize(&width, &height);
    imbxUint32 rowSize, channelPixelSize, channelsNumber;
    puntoexe::ptr<puntoexe::imebra::handlers::dataHandlerNumericBase> dataHandler = m_image->getDataHandler(false, &rowSize, &channelPixelSize, &channelsNumber);
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                                dataHandler->getMemoryBuffer(),
                                                                width * height * 4,
                                                                NULL);

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    CGImageRef imageRef = CGImageCreate(width,
                                    height,
                                    8,
                                    32,
                                    rowSize,colorSpaceRef,
                                    bitmapInfo,
                                    provider, NULL, NO, renderingIntent);

    return [[[NSImage alloc] initWithCGImage:imageRef] autorelease];

}
#endif

@end
