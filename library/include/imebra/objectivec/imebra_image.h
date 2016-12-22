#if !defined(imebraObjcImage__INCLUDED_)
#define imebraObjcImage__INCLUDED_

#if defined(APPLE)

#import <Foundation/Foundation.h>
#include "../definitions.h"

#ifdef TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/NSImage.h>
#endif
#include <imebra/imebra.h>

#ifdef __APPLE__
   #include "TargetConditionals.h"
#endif

#ifdef TARGET_OS_IPHONE
IMEBRA_API UIImage* getImebraImage(const imebra::Image& image, const imebra::Transform& transform);
#else
IMEBRA_API NSImage* getImebraImage(const imebra::Image& image, const imebra::Transform& transform);
#endif

#endif //APPLE

#endif // imebraObjcImage__INCLUDED_

