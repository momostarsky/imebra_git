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

namespace imebra
{

#if TARGET_OS_IPHONE
/**
 * Generates a UIImage from a 24bpp RGB image returned by imebra::DrawBitmap::getImage().
 *
 * @param image      the image to pass as parameter to imebra::DrawBitmap::getImage()
 * @param drawBitmap the imebra::DrawBitmap object to use to generate the 24bpp RGB
 *                   representation of the DICOM image
 * @return           a UIImage initialized with the 24bpp RGB image returned by imebra::DrawBitmap
 */
IMEBRA_API UIImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);

#else

/**
 * Generates a NSImage from a 24bpp RGB image returned by imebra::DrawBitmap::getImage().
 *
 * @param image      the image to pass as parameter to imebra::DrawBitmap::getImage()
 * @param drawBitmap the imebra::DrawBitmap object to use to generate the 24bpp RGB
 *                   representation of the DICOM image
 * @return           a NSImage initialized with the 24bpp RGB image returned by imebra::DrawBitmap
 */
IMEBRA_API NSImage* getImebraImage(const imebra::Image& image, imebra::DrawBitmap& drawBitmap);
#endif

} // namespace imebra

#endif //__APPLE__

#endif // imebraObjcImage__INCLUDED_


