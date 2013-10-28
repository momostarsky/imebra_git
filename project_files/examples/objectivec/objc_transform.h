
#include "../../library/imebra/include/transform.h"
#import "objc_image.h"

/**
 * This class calls the C++ methods in imebra.
 *
 */
@interface ImebraTransform : NSObject
  puntoexe::ptr<puntoexe::imebra::transforms::transform> m_transform;

- initWithTransform: (puntoexe::ptr<puntoexe::imebra::transforms::transform>) transform;


/// \brief Returns true if the transform doesn't do
///         anything.
///
/// @return false if the transform does something, or true
///          if the transform doesn't do anything (e.g. an
///          empty transformsChain object).
///
///////////////////////////////////////////////////////////
- (bool) isEmpty;

- (ImebraImage*) allocateOutputImage: (ImebraImage*)inputImage width:(imbxUint32)width height:(imbxUint32)height;

- (void) runTransform:(ImebraImage*)input sourceTopLeftX:(imbxUint32)inputTopLeftX sourceTopLeftY:(imbxUint32)inputTopLeftY sourceWidth:(imbxUint32)width sourceHeight:(imbxUint32)height destinationImage:(ImebraImage*)outputImage destinationTopLeftX:(imbxUint32)outputTopLeftX destinationTopLeftY:(imbxUint32)outputTopLeftY;

@end

