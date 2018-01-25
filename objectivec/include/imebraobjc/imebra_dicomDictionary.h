/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcDicomDictionary__INCLUDED_)
#define imebraObjcDicomDictionary__INCLUDED_

#import <Foundation/Foundation.h>

#import "imebra_dataset.h"

@class ImebraTagId;

@interface ImebraDicomDictionary: NSObject

    +(NSString*)getTagName:(ImebraTagId*)tagId error:(NSError**)pError;

    +(ImebraTagVR_t)getTagType:(ImebraTagId*)tagId error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    +(unsigned int)getWordSize:(ImebraTagVR_t)dataType;

    +(unsigned int)getMaxSize:(ImebraTagVR_t)dataType;

@end

#endif // imebraObjcDicomDictionary__INCLUDED_
