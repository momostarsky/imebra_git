/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "imebra_bridgeStructures.h"

@implementation ImebraWritingDataHandlerNumeric

-(ImebraReadWriteMemory*)getMemory:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadWriteMemory alloc] initWithImebraReadWriteMemory:((imebra::WritingDataHandlerNumeric*)m_pDataHandler)->getMemory()];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)assign:(NSData*)pSource error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::WritingDataHandlerNumeric*)m_pDataHandler)->assign((char*)pSource.bytes, (size_t)pSource.length);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)copyFrom:(ImebraReadingDataHandlerNumeric*)pSource error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::WritingDataHandlerNumeric*)m_pDataHandler)->copyFrom(*((imebra::ReadingDataHandlerNumeric*)pSource->m_pDataHandler));

    OBJC_IMEBRA_FUNCTION_END();
}

-(unsigned int) unitSize
{
    return (unsigned int)((imebra::WritingDataHandlerNumeric*)m_pDataHandler)->getUnitSize();
}

-(bool) isSigned
{
    return ((imebra::WritingDataHandlerNumeric*)m_pDataHandler)->isSigned();
}

-(bool) isFloat
{
    return ((imebra::WritingDataHandlerNumeric*)m_pDataHandler)->isFloat();
}

@end
