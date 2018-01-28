/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcTcpAddress__INCLUDED_)
#define imebraObjcTcpAddress__INCLUDED_

#import <Foundation/Foundation.h>

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class TCPAddress;
}
#endif


@interface ImebraTCPAddress: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::TCPAddress* m_pTcpAddress;

}

    -(id)initWithImebraTCPAddress:(imebra::TCPAddress*)pTcpAddress;

#endif

    -(void)dealloc;

    @property (readonly) NSString* node;
    @property (readonly) NSString* service;

@end


@interface ImebraTCPActiveAddress: ImebraTCPAddress

    -(id)init:(NSString*)node service:(NSString*)service error:(NSError**)pError;

@end


@interface ImebraTCPPassiveAddress: ImebraTCPAddress

    -(id)init:(NSString*)node service:(NSString*)service error:(NSError**)pError;

@end

#endif // imebraObjcTcpAddress__INCLUDED_
