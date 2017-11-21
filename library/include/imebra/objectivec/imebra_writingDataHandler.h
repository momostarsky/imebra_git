/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcWritingDataHandler__INCLUDED_)
#define imebraObjcWritingDataHandler__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class WritingDataHandler;
}
#endif

@class ImebraDate;
@class ImebraAge;

@interface ImebraWritingDataHandler: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::WritingDataHandler* m_pDataHandler;
}
#endif

    -(id)initWithImebraWritingDataHandler:(imebra::WritingDataHandler*)pWritingDataHandler;

    -(void)dealloc;

    @property unsigned int size;

    -(void) setSignedLong:(unsigned int)index withValue:(int)value error:(NSError**)pError;

    -(void) setUnsignedLong:(unsigned int)index withValue:(unsigned int)value error:(NSError**)pError;

    -(void) setDouble:(unsigned int)index withValue:(double)value error:(NSError**)pError;

    -(void) setString:(unsigned int)index withValue:(NSString*)value error:(NSError**)pError;

    -(void) setDate:(unsigned int)index withValue:(ImebraDate*)value error:(NSError**)pError;

    -(void) setAge:(unsigned int)index withValue:(ImebraAge*)value error:(NSError**)pError;

@end

#endif // !defined(imebraObjcWritingDataHandler__INCLUDED_)
