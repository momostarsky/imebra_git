/*
$fileHeader$
*/

/*! \file charsetsList.h
    \brief Declaration of the the base class for the classes that need to be
            aware of the Dicom charsets.

*/

#if !defined(imebraCharsetsList_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraCharsetsList_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include <stdexcept>
#include <string>
#include <list>

namespace puntoexe
{

namespace imebra
{

/// \addtogroup group_dataset
///
/// @{


/// \name charsetsList
/// \brief The classes used to convert between different
///         charsets are declared in this namespace.
///////////////////////////////////////////////////////////
namespace charsetsList
{

/// \typedef std::list<std::wstring> tCharsetsList
/// \brief Defines a list of widechar strings.
///
/// It is used to set or retrieve a list of charsets
///
///////////////////////////////////////////////////////////
typedef std::list<std::string> tCharsetsList;

void updateCharsets(const tCharsetsList* pCharsetsList, tCharsetsList* pDestinationCharsetsList);

} // namespace charsetsList

/// @}

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraCharsetsList_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)

