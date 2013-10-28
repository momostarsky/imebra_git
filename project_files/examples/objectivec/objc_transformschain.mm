
#import "objc_transformschain.h"

/**
 * This class calls the C++ methods in imebra.
 *
 */
@implementation ImebraTransformsChain

- initWithTransform: (puntoexe::ptr<puntoexe::imebra::transforms::transformsChain>) transformsChain
{
    m_transform = transformsChain;
}

- (void) addTransform: (ImebraTransform*) transform
{
    (puntoexe::imebra::transforms::transformsChain*)(m_transform->get())->addTransform(transform->m_transform);
}


@end

