/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcLut__INCLUDED_)
#define imebraObjcLut__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class LUT;
}
#endif

@class ImebraReadingDataHandlerNumeric;

@interface ImebraLUT : NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::LUT* m_pLUT;
}

    -(id)initWithImebraLut:(imebra::LUT*)pLUT;
#endif

    -(void)dealloc;

    -(ImebraReadingDataHandlerNumeric*) getReadingDataHandler;

    -(unsigned int)getMappedValue:(int)index;

    @property (readonly) NSString* description;
    @property (readonly) unsigned int bits;
    @property (readonly) unsigned int size;
    @property (readonly) int firstMappedValue;

@end

#endif // imebraObjcLut__INCLUDED_


