/*
Copyright 2005 - 2022 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file version.cpp
    \brief Implementation of the function getVersion().

*/

#include <vcs_version.h>
#include <dicomhero6/version.h>

namespace dicomhero
{

std::string getVersion()
{
    return PRODUCT_VERSION_FULL;
}

std::wstring getVersionW()
{
    return PRODUCT_VERSION_FULL_W;
}

} // namespace dicomhero


