#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "../../library/imebra/include/image.h"

#ifdef __APPLE__
   #include "TargetConditionals.h"
#endif

/**
 * This class calls the C++ methods in imebra.
 *
 */
@interface ImebraImage : NSObject
  puntoexe::ptr<puntoexe::imebra::image> m_image;

- initWithImebraImage: (puntoexe::ptr<puntoexe::imebra::image>) image;

/**
 * Retrieve the image's size.
 */
- (long) getWidth;
- (long) getHeight;

#ifdef TARGET_OS_IPHONE
- (UIImage*) getUIImage;
#else
- (NSImage*) GetNSImage;
#endif

@end

