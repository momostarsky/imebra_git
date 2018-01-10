/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcStreamWriter__INCLUDED_)
#define imebraObjcStreamWriter__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class StreamWriter;
}
#endif

@class ImebraBaseStreamOutput;
@class ImebraBaseStreamInputOutput;

@interface ImebraStreamWriter: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::StreamWriter* m_pWriter;
}

    -(id)initWithImebraStreamWriter:(imebra::StreamWriter*)pStreamWriter;
#endif

    -(id)initWithOutputStream:(ImebraBaseStreamOutput*)pOutput;

    -(id)initWithInputOutputStream:(ImebraBaseStreamInputOutput*)pInputOutput;

    -(void)dealloc;

@end

#endif // !defined(imebraObjcStreamWriter__INCLUDED_)



