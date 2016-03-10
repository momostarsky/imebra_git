/*
$fileHeader$
*/

/*! \file tagId.h
    \brief Declaration of the class TagId.

*/

#if !defined(imebraTagId__INCLUDED_)
#define imebraTagId__INCLUDED_

#ifndef SWIG

#include <cstdint>
#include "tagsEnumeration.h"

#endif

#include "definitions.h"

namespace imebra
{

///
/// \brief Represents a Dicom tag's identification.
///
class IMEBRA_API TagId
{
public:
    TagId(std::uint16_t groupId, std::uint16_t tagId);
    TagId(std::uint16_t groupId, std::uint32_t groupOrder, std::uint16_t tagId);

    /// \brief Constructor.
    ///
    /// \param id an enumeration representing a tag group and
    ///           id
    ///
    ///////////////////////////////////////////////////////////
    TagId(tagId_t id);

    TagId(tagId_t id, std::uint32_t groupOrder);

    virtual ~TagId();

    std::uint16_t getGroupId() const;
    std::uint32_t getGroupOrder() const;
    std::uint16_t getTagId() const;

private:
    std::uint16_t m_groupId;
    std::uint32_t m_groupOrder;
    std::uint16_t m_tagId;
};

}

#endif // !defined(imebraTagId__INCLUDED_)
