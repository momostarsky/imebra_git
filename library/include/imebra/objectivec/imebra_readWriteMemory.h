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

    -(id)initWithData:(NSData*)pSource;

    -(void)dealloc;

    -(void)copyFrom:(ImebraReadMemory*)source error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)clear:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)resize:(unsigned int)newSize error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)reserve:(unsigned int)reserveSize error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)assign:(NSData*)pSource error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)assignRegion:(NSData*)pSource offset:(unsigned int)destinationOffset error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

@end

#endif // !defined(imebraObjcReadWriteMemory__INCLUDED_)
