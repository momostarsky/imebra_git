/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcWritingDataHandlerNumeric__INCLUDED_)
#define imebraObjcWritingDataHandlerNumeric__INCLUDED_

#import "imebra_writingDataHandler.h"
#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class WritingDataHandlerNumeric;
}
#endif

@class ImebraReadingDataHandlerNumeric;
@class ImebraReadWriteMemory;

@interface ImebraWritingDataHandlerNumeric: ImebraWritingDataHandler

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
    -(id)initWithImebraWritingDataHandler:(imebra::WritingDataHandlerNumeric*)pWritingDataHandler;
#endif

    -(void)dealloc;

    -(ImebraReadWriteMemory*)getMemory:(NSError**)pError;

    -(void)assign:(const char*)data withSize:(unsigned int)size error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(void)copyFrom:(ImebraReadingDataHandlerNumeric*)source error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    @property (readonly) char* data;
    @property (readonly) unsigned int dataSizeBytes;

    @property (readonly) unsigned int unitSize;

    @property (readonly) bool isSigned;
    @property (readonly) bool isFloat;

@end

#endif // !defined(imebraObjcWritingDataHandlerNumeric__INCLUDED_)
