/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcTcpListener__INCLUDED_)
#define imebraObjcTcpListener__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class TCPListener;
}
#endif

@class ImebraTCPPassiveAddress;
@class ImebraTCPStream;

@interface ImebraTCPListener: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::TCPListener* m_pTcpListener;

}

#endif

    -(id)initWithAddress:(ImebraTCPPassiveAddress*)pAddress error:(NSError**)pError;

    -(void)dealloc;

    -(ImebraTCPStream*)waitForConnection:(NSError**)pError;

    -(void)terminate;

@end


#endif // imebraObjcTcpListener__INCLUDED_
