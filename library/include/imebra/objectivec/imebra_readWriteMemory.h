/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcReadWriteMemory__INCLUDED_)
#define imebraObjcReadWriteMemory__INCLUDED_

#import "imebra_readMemory.h"
#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class ReadWriteMemory;
}
#endif


@interface ImebraReadWriteMemory: ImebraReadMemory

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
    -(id)initWithImebraReadWriteMemory:(imebra::ReadWriteMemory*)pReadWriteMemory;
#endif

    -(id)init;

    -(id)initWithSize:(unsigned int)size;

    -(id)initWithMemory:(ImebraReadMemory*)source;

    -(id)initWithData:(const char*)source size:(unsigned int)size;

    -(void)dealloc;

    -(void)copyFrom:(ImebraReadMemory*)source error:(NSError**)pError;

    -(void)clear:(NSError**)pError;

    -(void)resize:(unsigned int)newSize error:(NSError**)pError;

    -(void)reserve:(unsigned int)reserveSize error:(NSError**)pError;

    -(void)assign:(const char*)data withSize:(unsigned int)size error:(NSError**)pError;

    -(void)assignRegion:(const char*)data  withSize:(unsigned int)size offset:(unsigned int)destinationOffset error:(NSError**)pError;
@end

#endif // !defined(imebraObjcReadWriteMemory__INCLUDED_)
