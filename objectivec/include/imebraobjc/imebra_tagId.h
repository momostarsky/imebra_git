/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcTagId__INCLUDED_)
#define imebraObjcTagId__INCLUDED_

#import <Foundation/Foundation.h>
#import "tagsEnumeration.h"

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
namespace imebra
{
class TagId;
}
#endif

///
/// \brief Represents a Dicom tag's identification.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraTagId: NSObject

#ifndef __IMEBRA_OBJECTIVEC_BRIDGING__
{
    @public
    imebra::TagId* m_pTagId;
}
#endif

    -(id)init;

    -(id)initWithGroup:(unsigned short)groupId tag:(unsigned short)tagId;

    -(id)initWithId:(ImebraTagId_t)tagId;

    -(id)initWithGroup:(unsigned short)groupId groupOrder:(unsigned int)groupOrder tag:(unsigned short)tagId;

    -(void)dealloc;

    @property (readonly) unsigned short groupId;

    @property (readonly) unsigned int groupOrder;

    @property (readonly) unsigned short tagId;

@end


#endif // imebraObjcTagId__INCLUDED_
