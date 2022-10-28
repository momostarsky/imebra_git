/*
Copyright 2005 - 2022 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/// \file version.h
/// \brief Declaration of the function getVersion()
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraVersion__INCLUDED_)
#define imebraVersion__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "mutableMemory.h"
#include "writingDataHandler.h"


namespace dicomhero
{

std::string getVersion();

std::wstring getVersionW();

}

#endif // !defined(imebraVersion__INCLUDED_)
