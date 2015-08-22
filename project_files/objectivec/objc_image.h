#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "../library/imebra/include/image.h"

#ifdef __APPLE__
   #include "TargetConditionals.h"
#endif

#ifdef TARGET_OS_IPHONE
UIImage* getImage(puntoexe::ptr<puntoexe::imebra::image> image, puntoexe::ptr<puntoexe::imebra::transforms::transform> transforms);
#else
NSImage* getImage(puntoexe::ptr<puntoexe::imebra::image> image, puntoexe::ptr<puntoexe::imebra::transforms::transform> transforms);
#endif

