#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "../library/imebra/include/image.h"

#ifdef __APPLE__
   #include "TargetConditionals.h"
#endif

#ifdef TARGET_OS_IPHONE
UIImage* getImage(puntoexe::ptr<puntoexe::imebra::image> image);
#else
NSImage* getImage(puntoexe::ptr<puntoexe::imebra::image> image);
#endif

