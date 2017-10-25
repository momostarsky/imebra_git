/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebra/imebra.h"
#import "../include/imebra/objectivec/imebra_nserror.h"
#import "../include/imebra/objectivec/imebra_readingDataHandlerNumeric.h"
#import "../include/imebra/objectivec/imebra_writingDataHandlerNumeric.h"
#import "../include/imebra/objectivec/imebra_readMemory.h"

@implementation ImebraReadingDataHandlerNumeric

-(id)initWithImebraReadingDataHandler:(imebra::ReadingDataHandlerNumeric*)pReadingDataHandler
{
    self = [super initWithImebraReadingDataHandler:pReadingDataHandler];
    return self;
}

-(void)dealloc
{
}

-(ImebraReadMemory*)getMemory:(NSError**)pError
{
    try
    {
        return [[ImebraReadMemory alloc] initWithImebraReadMemory:((imebra::ReadingDataHandlerNumeric*)m_pDataHandler)->getMemory()];
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
        return nil;
    }
}

-(void)copyTo:(ImebraWritingDataHandlerNumeric*)destination error:(NSError**)pError
{
    try
    {
        ((imebra::ReadingDataHandlerNumeric*)m_pDataHandler)->copyTo(*((imebra::WritingDataHandlerNumeric*)destination->m_pDataHandler));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(const char*) data
{
    size_t dummy;
    return ((imebra::ReadingDataHandlerNumeric*)m_pDataHandler)->data(&dummy);
}

-(unsigned int) dataSizeBytes
{
    size_t size;
    ((imebra::ReadingDataHandlerNumeric*)m_pDataHandler)->data(&size);
    return (unsigned int)size;
}

-(unsigned int) unitSize
{
    return (unsigned int)((imebra::ReadingDataHandlerNumeric*)m_pDataHandler)->getUnitSize();
}

-(bool) isSigned
{
    return ((imebra::ReadingDataHandlerNumeric*)m_pDataHandler)->isSigned();
}

-(bool) isFloat
{
    return ((imebra::ReadingDataHandlerNumeric*)m_pDataHandler)->isFloat();
}

@end
