/**
 * This is a simple objective-c class that calls some method on the imebra library.
 *
 * The most problematic part is the conversion from NSString to wstring and viceversa.
 *
 * Other data types can be used natively (e.g. int, imbxInt16, double, etc).
 *
 */

#include "../library/imebra/include/imebra.h"

#import "objc_dataset.h"
#import "objc_image.h"
#import "objc_helpers.h"

#ifdef TARGET_OS_IPHONE
UIImage* getImage(puntoexe::ptr<puntoexe::imebra::image> image)
#else
NSImage* getImage(puntoexe::ptr<puntoexe::imebra::image> image)
#endif
{
    imbxUint32 width, height;
    image->getSize(&width, &height);
    imbxUint32 rowSize, channelPixelSize, channelsNumber;

    puntoexe::imebra::drawBitmap drawBitmap(image, 0);
    size_t memorySize = drawBitmap.getBitmap<puntoexe::imebra::drawBitmapRGBA, 4>(width, height, 0, 0, width, height, 0, 0);

    puntoexe::ptr<puntoexe::memory> memory(puntoexe::memoryPool::getMemoryPool()->getMemory(memorySize));
    drawBitmap.getBitmap<puntoexe::imebra::drawBitmapRGBA, 4>(width, height, 0, 0, width, height, memory->data(), memorySize);

    CGDataProviderRef dataProviderRef = CGDataProviderCreateWithData(0,
                                                                dataHandler->getMemoryBuffer(),
                                                                width * height * 4,
                                                                0);

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;

    CGImageRef imageRef = CGImageCreate(
                width, height,
                8, 32,
                width * 4,
                colorSpaceRef, bitmapInfo, dataProviderRef, NULL, YES, renderingIntent);


    imageRef = CGImageCreate(width,
                                    height,
                                    8,
                                    32,
                                    rowSize, colorSpaceRef,
                                    bitmapInfo,
                                    provider, NULL, NO, renderingIntent);
#ifdef TARGET_OS_IPHONE

    return [[[UIImage alloc] imageWithCGImage:imageRef] autorelease];
    }
#else
    return [[[NSImage alloc] initWithCGImage:imageRef] autorelease];
#endif
}


@end
