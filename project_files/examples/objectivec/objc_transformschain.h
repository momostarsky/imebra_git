
#import "objc_transform.h"
#include "../../library/imebra/include/transformsChain.h"

/**
 * This class calls the C++ methods in imebra.
 *
 */
@interface ImebraTransformsChain : ImebraTransform

- initWithTransform: (puntoexe::ptr<puntoexe::imebra::transforms::transform>) transform;

- (void) addTransform: (ImebraTransform*) transform;


@end

