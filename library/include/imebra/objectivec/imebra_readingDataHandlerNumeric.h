/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "imebra_readingDataHandler.h"
#import <Foundation/Foundation.h>

#if !defined(imebraObjcReadingDataHandlerNumeric__INCLUDED_)
#define imebraObjcReadingDataHandlerNumeric__INCLUDED_

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class ReadingDataHandlerNumeric;
}
#endif

@class ImebraWritingDataHandlerNumeric;
@class ImebraReadMemory;

@interface ImebraReadingDataHandlerNumeric: ImebraReadingDataHandler

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
    -(id)initWithImebraReadingDataHandler:(imebra::ReadingDataHandlerNumeric*)pReadingDataHandler;
#endif

    -(void)dealloc;

    -(ImebraReadMemory*)getMemory: (NSError**)pError;

    -(void)copyTo:(ImebraWritingDataHandlerNumeric*)destination error:(NSError**)pError;

    @property (readonly) const char* data;
    @property (readonly) unsigned int dataSizeBytes;

    @property (readonly) unsigned int unitSize;

    @property (readonly) bool isSigned;
    @property (readonly) bool isFloat;


@end

#endif // !defined(imebraObjcReadingDataHandlerNumeric__INCLUDED_)
