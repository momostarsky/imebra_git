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
#import "../include/imebra/objectivec/imebra_readWriteMemory.h"

@implementation ImebraReadWriteMemory

-(id)initWithImebraReadWriteMemory:(imebra::ReadWriteMemory*)pReadWriteMemory
{
    return [super initWithImebraReadMemory:pReadWriteMemory];
}

-(id)init
{
    return [super initWithImebraReadMemory:new imebra::ReadWriteMemory()];
}

-(id)initWithSize:(unsigned int)size
{
    return [super initWithImebraReadMemory:new imebra::ReadWriteMemory((size_t)size)];
}

-(id)initWithMemory:(ImebraReadMemory*)source
{
    return [super initWithImebraReadMemory:(new imebra::ReadWriteMemory(*(source->m_pMemory)))];
}

-(id)initWithData:(const char*)source size:(unsigned int)size
{
    return [super initWithData:source size:size];
}

-(void)dealloc
{
#if !__has_feature(objc_arc)
    [super dealloc];
#endif
}

-(void)copyFrom:(ImebraReadMemory*)source error:(NSError**)pError
{
    try
    {
        ((imebra::ReadWriteMemory*)m_pMemory)->copyFrom(*(source->m_pMemory));
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)clear:(NSError**)pError
{
    try
    {
        ((imebra::ReadWriteMemory*)m_pMemory)->clear();
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)resize:(unsigned int)newSize error:(NSError**)pError
{
    try
    {
        ((imebra::ReadWriteMemory*)m_pMemory)->resize((size_t)newSize);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)reserve:(unsigned int)reserveSize error:(NSError**)pError
{
    try
    {
        ((imebra::ReadWriteMemory*)m_pMemory)->reserve((size_t)reserveSize);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)assign:(const char*)data withSize:(unsigned int)size error:(NSError**)pError
{
    try
    {
        ((imebra::ReadWriteMemory*)m_pMemory)->assign(data, (size_t)size);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

-(void)assignRegion:(const char*)data  withSize:(unsigned int)size offset:(unsigned int)destinationOffset error:(NSError**)pError
{
    try
    {
        ((imebra::ReadWriteMemory*)m_pMemory)->assignRegion(data, (size_t)size, (size_t)destinationOffset);
    }
    catch(const std::runtime_error& e)
    {
        imebra::setNSError(e, pError);
    }
}

@end
