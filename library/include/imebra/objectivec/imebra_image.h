#if !defined(imebraObjcImage__INCLUDED_)
#define imebraObjcImage__INCLUDED_

#if defined(__APPLE__)
#include "TargetConditionals.h"

#import <Foundation/Foundation.h>
#include "../definitions.h"

#if TARGET_OS_IPHONE
#import <UIKit/UIImage.h>
#else
#import <AppKit/NSImage.h>
#endif
#include <imebra/imebra.h>

#if TARGET_OS_IPHONE
IMEBRA_API UIImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);
#else
IMEBRA_API NSImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);
#endif

#endif //__APPLE__

#endif // imebraObjcImage__INCLUDED_


