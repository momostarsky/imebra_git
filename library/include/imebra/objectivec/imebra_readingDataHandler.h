/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcReadingDataHandler__INCLUDED_)
#define imebraObjcReadingDataHandler__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class ReadingDataHandler;
}
#endif


@class ImebraDate;
@class ImebraAge;

@interface ImebraReadingDataHandler: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::ReadingDataHandler* m_pDataHandler;
}

    -(id)initWithImebraReadingDataHandler:(imebra::ReadingDataHandler*)pReadingDataHandler;
#endif

    -(void)dealloc;

    @property (readonly) unsigned int size;

    -(int) getSignedLong:(unsigned int)index error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(unsigned int) getUnsignedLong:(unsigned int)index error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(double) getDouble:(unsigned int)index error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    -(NSString*) getString:(unsigned int)index error:(NSError**)pError;

    -(ImebraDate*) getDate:(unsigned int)index error:(NSError**)pError;

    -(ImebraAge*) getAge:(unsigned int)index error:(NSError**)pError;


@end

#endif // !defined(imebraObjcReadingDataHandler__INCLUDED_)
