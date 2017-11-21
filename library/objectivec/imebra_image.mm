/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include <../include/imebra/imebra.h>
#import "imebra_nserror.h"
#import "../include/imebra/objectivec/imebra_image.h"
#import "../include/imebra/objectivec/imebra_readingDataHandlerNumeric.h"
#import "../include/imebra/objectivec/imebra_writingDataHandlerNumeric.h"
#import "imebra_strings.h"


@implementation ImebraImage

-(id)initWithImebraImage:(imebra::Image*)pImage
{
    self =  [super init];
    if(self)
    {
        self->m_pImage = pImage;
    }
    return self;
}

-(id)initWithSize:(unsigned int)width height:(unsigned int)height depth:(ImebraBitDepth_t)depth colorSpace:(NSString*)colorSpace highBit:(unsigned int)highBit
{
    self =  [super init];
    if(self)
    {
        self->m_pImage = new imebra::Image(
                                 width,
                                 height,
                                 (imebra::bitDepth_t)depth,
                                 imebra::NSStringToString(colorSpace),
                                 highBit);
    }
    return self;
}

///
/// \ Destructor
///
///////////////////////////////////////////////////////////////////////////////
-(void)dealloc
{
    delete m_pImage;
#if !__has_feature(objc_arc)
    [super dealloc];
#endif
}

-(ImebraReadingDataHandlerNumeric*) getReadingDataHandler:(NSError**)pError
{
    try
    {
        return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:m_pImage->getReadingDataHandler()];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(ImebraWritingDataHandlerNumeric*) getWritingDataHandler:(NSError**)pError
{
    try
    {
        return [[ImebraWritingDataHandlerNumeric alloc] initWithImebraWritingDataHandler:m_pImage->getWritingDataHandler()];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(double) widthMm
{
    return m_pImage->getWidthMm();
}

-(double) heightMm
{
    return m_pImage->getHeightMm();
}

-(unsigned int) width
{
    return m_pImage->getWidth();
}

-(unsigned int) height
{
    return m_pImage->getHeight();
}

-(NSString*) colorSpace
{
    return imebra::stringToNSString(m_pImage->getColorSpace());
}

-(unsigned int) getChannelsNumber
{
    return m_pImage->getChannelsNumber();
}

-(ImebraBitDepth_t) getDepth
{
    return (ImebraBitDepth_t)m_pImage->getDepth();
}

-(unsigned int) getHighBit
{
    return m_pImage->getHighBit();
}

@end

