#include "../../library/imebra/include/imebra.h"
#import "objc_transform.h"


@implementation ImebraTransform

- initWithTransform: (puntoexe::ptr<puntoexe::imebra::transforms::transform>) transform
{
    if(self = [super init])
    {
        m_transform = transform;
    }
}

- (bool) isEmpty
{
    return m_transform->isEmpty();
}

- (ImebraImage*) allocateOutputImage: (ImebraImage*)inputImage width:(imbxUint32)width height:(imbxUint32)height
{
    puntoexe::ptr<puntoexe::imebra::image> image = m_transform->allocateOutputImage(inputImage->m_image, width, height);
    return [[[ImebraImage alloc] initWithImebraImage:image] autorelease];
}

- (void) runTransform:(ImebraImage*)input sourceTopLeftX:(imbxUint32)inputTopLeftX sourceTopLeftY:(imbxUint32)inputTopLeftY sourceWidth:(imbxUint32)width sourceHeight:(imbxUint32)height destinationImage:(ImebraImage*)outputImage destinationTopLeftX:(imbxUint32)outputTopLeftX destinationTopLeftY:(imbxUint32)outputTopLeftY
{
    m_transform->runTransform(input->m_image, sourceTopLeftX, sourceTopLeftY, sourceWidth, sourceHeight, destinationImage->m_image, destinationTopLeftX, destinationTopLeftY);
}

@end


