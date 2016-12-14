#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include <imebra/imebra.h>

#ifdef __APPLE__
   #include "TargetConditionals.h"
#endif

#ifdef TARGET_OS_IPHONE

UIImage* getImage(const imebra::Image& image, const imebra::Transform& transform);
#else
NSImage* getImage(const imebra::Image& image, const imebra::Transform& transform);
#endif

///@}

