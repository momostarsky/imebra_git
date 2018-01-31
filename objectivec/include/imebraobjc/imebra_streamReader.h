/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcStreamReader__INCLUDED_)
#define imebraObjcStreamReader__INCLUDED_

#import "imebra_baseStreamInput.h"
#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class StreamReader;
}
#endif

@interface ImebraStreamReader: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::StreamReader* m_pReader;
}

    -(id)initWithImebraStreamReader:(imebra::StreamReader*)pStreamReader;
#endif

    -(id)initWithInputStream:(ImebraBaseStreamInput*)pInput;

    -(id)initWithInputStream:(ImebraBaseStreamInput*)pInput virtualStart:(unsigned int)virtualStart virtualEnd:(unsigned int)virtualEnd;

    -(void)dealloc;

    -(ImebraStreamReader*)getVirtualStream:(unsigned int)virtualSize error:(NSError**)pError;

    -(void)terminate;

@end

#endif // !defined(imebraObjcStreamReader__INCLUDED_)
