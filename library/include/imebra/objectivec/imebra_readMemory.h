/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcReadMemory__INCLUDED_)
#define imebraObjcReadMemory__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class ReadMemory;
}
#endif

@interface ImebraReadMemory: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    imebra::ReadMemory* m_pMemory;
}

    -(id)initWithImebraReadMemory:(imebra::ReadMemory*)pReadMemory;
#endif

    -(id)init;

    -(id)initWithData:(const char*)source size:(unsigned int)size;

    -(void)dealloc;

    @property (readonly) const char* data;
    @property (readonly) unsigned int size;
    @property (readonly) bool empty;

@end

#endif // !defined(imebraObjcReadMemory__INCLUDED_)
