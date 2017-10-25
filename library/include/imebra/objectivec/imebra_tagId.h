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

#include "../definitions.h"
#import <Foundation/Foundation.h>

namespace imebra
{
class TagId;
}

///
/// \brief Specifies an age, in days, weeks, months or years.
///
///////////////////////////////////////////////////////////////////////////////
IMEBRA_API
@interface ImebraTagId: NSObject
{
    @public
    imebra::TagId* m_pTagId;
}

    -(id)init;

    -(id)init:(unsigned short)groupId tag:(unsigned short)tagId;

    -(id)init:(unsigned short)groupId groupOrder:(unsigned int)groupOrder tag:(unsigned short)tagId;

    -(void)dealloc;

    @property (readonly) unsigned short groupId;

    @property (readonly) unsigned int groupOrder;

    @property (readonly) unsigned int tagId;

@end


#endif // imebraObjcTagId__INCLUDED_
