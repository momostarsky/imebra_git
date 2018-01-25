/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcFileStreamInput__INCLUDED_)
#define imebraObjcFileStreamInput__INCLUDED_

#import <Foundation/Foundation.h>
#import "imebra_baseStreamInput.h"

@interface ImebraFileStreamInput: ImebraBaseStreamInput

    -(id)initWithName:(NSString*)fileName error:(NSError**)pError;

@end

#endif // imebraObjcFileStreamInput__INCLUDED_


