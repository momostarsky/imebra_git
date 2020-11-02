/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_memoryPool.h"

#include <dicomhero6/memoryPool.h>

@implementation DicomheroMemoryPool

+(void) flush
{
    dicomhero::MemoryPool::flush();
}

+(unsigned int) getUnusedMemorySize
{
    return (unsigned int)dicomhero::MemoryPool::getUnusedMemorySize();
}

+(void) setMemoryPoolSize:(unsigned int)minMemoryBlockSize maxSize:(unsigned int)maxMemoryPoolSize
{
    dicomhero::MemoryPool::setMemoryPoolSize((size_t)minMemoryBlockSize, (size_t)maxMemoryPoolSize);
}

@end




