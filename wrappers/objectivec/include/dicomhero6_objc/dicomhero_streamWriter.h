/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(imebraObjcStreamWriter__INCLUDED_)
#define imebraObjcStreamWriter__INCLUDED_

#import <Foundation/Foundation.h>
#include "dicomhero_macros.h"


@class DicomheroBaseStreamOutput;

///
/// \brief A DicomheroStreamWriter is used to write data into a
///        DicomheroBaseStreamOutput object.
///
///////////////////////////////////////////////////////////////////////////////
@interface DicomheroStreamWriter: NSObject

{
    @public
    define_dicomhero_object_holder(StreamWriter);
}

    -(id)initWithDicomheroStreamWriter:define_dicomhero_parameter(StreamWriter);

    /// \brief Initializer.
    ///
    /// \param pOutput the DicomheroBaseStreamOutput object on which the
    ///                DicomheroStreamWriter will write
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithOutputStream:(DicomheroBaseStreamOutput*)pOutput;

    -(void)dealloc;

@end

#endif // !defined(imebraObjcStreamWriter__INCLUDED_)



