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
#import "../include/imebra/objectivec/imebra_readMemory.h"

@implementation ImebraReadMemory

-(id)initWithImebraReadMemory:(imebra::ReadMemory*)pReadMemory
{
    self = [super init];
    if(self)
    {
        self->m_pMemory = pReadMemory;
    }
    return self;
}

-(id)init
{
    self = [super init];
    if(self)
    {
        self->m_pMemory = new imebra::ReadMemory();
    }
    return self;
}

-(id)initWithData:(const char*)source size:(unsigned int)size
{
    self = [super init];
    if(self)
    {
        self->m_pMemory = new imebra::ReadMemory(source, (size_t)size);
    }
    return self;
}

-(void)dealloc
{
    delete self->m_pMemory;
#if !__has_feature(objc_arc)
    [super dealloc];
#endif
}

-(unsigned int) size
{
    return (unsigned int)m_pMemory->size();
}

-(const char*) data
{
    size_t dummy;
    return m_pMemory->data(&dummy);
}

-(bool)empty
{
    return m_pMemory->empty();

}


@end


