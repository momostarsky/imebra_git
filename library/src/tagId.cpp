/*
$fileHeader$
*/

#include "../include/imebra/dataSet.h"
#include "../implementation/dataSetImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/charsetConversionBaseImpl.h"
#include <typeinfo>
#include <memory>

namespace imebra
{

TagId::TagId()
{
}

TagId::TagId(std::uint16_t groupId, std::uint16_t tagId):
    m_groupId(groupId), m_groupOrder(0), m_tagId(tagId)
{
}

TagId::TagId(std::uint16_t groupId, std::uint32_t groupOrder, std::uint16_t tagId):
    m_groupId(groupId), m_groupOrder(groupOrder), m_tagId(tagId)
{
}

TagId::TagId(tagId_t id):
    m_groupId((std::uint16_t)((std::uint32_t)id / (std::uint32_t)65536)),
    m_groupOrder(0),
    m_tagId((std::uint16_t)((std::uint32_t)id & (std::uint32_t)0x0000ffff))
{
}

TagId::TagId(tagId_t id, std::uint32_t groupOrder):
    m_groupId((std::uint16_t)((std::uint32_t)id / (std::uint32_t)65536)),
    m_groupOrder(groupOrder),
    m_tagId((std::uint16_t)((std::uint32_t)id & (std::uint32_t)0x0000ffff))
{
}

TagId::~TagId()
{
}

std::uint16_t TagId::getGroupId() const
{
    return m_groupId;
}

std::uint32_t TagId::getGroupOrder() const
{
    return m_groupOrder;
}

std::uint16_t TagId::getTagId() const
{
    return m_tagId;
}

}
