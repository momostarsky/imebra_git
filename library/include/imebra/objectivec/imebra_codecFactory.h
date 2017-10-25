/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcCodecFactory__INCLUDED_)
#define imebraObjcCodecFactory__INCLUDED_

#include "../definitions.h"
#import <Foundation/Foundation.h>

namespace imebra
{
    class DataSet;
}

@class ImebraDataSet;

///
/// \brief The ImebraCodecFactory class can load or save a DataSet or an Image
///        object using one of the codecs supplied by the Imebra library.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraCodecFactory: NSObject

    /// \brief Parses the content of the input file and returns a ImebraDataSet
    ///        representing it.
    ///
    /// If none of the codecs supplied by Imebra is able to decode the file's
    /// content then set the NSError and returns nil
    ///
    /// \param fileName          the name of the input file
    /// \param pError            pointer to a NSError pointer that will be set
    ///                          in case of error
    /// \return a ImebraDataSet object representing the input file's content
    ///
    ///////////////////////////////////////////////////////////////////////////////
    +(ImebraDataSet*)load:(NSString*) fileName error:(NSError**)pError;

@end

#endif // imebraObjcCodecFactory__INCLUDED_


