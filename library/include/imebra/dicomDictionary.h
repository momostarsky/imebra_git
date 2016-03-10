/*
$fileHeader$
*/

/*! \file dicomDictionary.h
    \brief Declaration of the DicomDictionary class.

*/

#if !defined(imebraDicomDictionary__INCLUDED_)
#define imebraDicomDictionary__INCLUDED_

#include <string>
#include "dataSet.h"
#include "streamReader.h"
#include "streamWriter.h"
#include "definitions.h"

namespace imebra
{

class IMEBRA_API DicomDictionary
{
public:
    /// \brief Retrieve a tag's description.
    ///
    /// @param groupId   The group which the tag belongs to
    /// @param tagId     The tag's id
    /// @return          The tag's description
    ///
    ///////////////////////////////////////////////////////////
    static std::wstring getUnicodeTagName(std::uint16_t groupId, std::uint16_t tagId);

    static std::string getTagName(std::uint16_t groupId, std::uint16_t tagId);

    /// \brief Retrieve a tag's default data type.
    ///
    /// @param groupId   The group which the tag belongs to
    /// @param tagId     The tag's id
    /// @return          The tag's data type
    ///
    ///////////////////////////////////////////////////////////
    static std::string getTagType(std::uint16_t groupId, std::uint16_t tagId);

    /// \brief Return the size of the data type's elements
    ///
    /// @param dataType the data type for which the information
    ///                  is required
    /// @return the size of a single element
    ///
    ///////////////////////////////////////////////////////////
    static std::uint32_t getWordSize(const std::string& dataType);

    /// \brief Return the maximum size of the tags with
    ///         the specified data type.
    ///
    /// @param dataType the data type for which the information
    ///                  is required
    /// @return         the maximum tag's size in bytes
    ///
    ///////////////////////////////////////////////////////////
    static std::uint32_t getMaxSize(const std::string& dataType);
};

}
#endif // !defined(imebraDicomDictionary__INCLUDED_)
