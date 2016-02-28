/*
$fileHeader$
*/

/*! \file dataHandlerStringPN.cpp
    \brief Implementation of the class dataHandlerStringPN.

*/

#include "dataHandlerStringPNImpl.h"

namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerStringPN
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringPN::readingDataHandlerStringPN(const memory& parseMemory, const charsetsList::tCharsetsList& charsets):
    readingDataHandlerStringUnicode(parseMemory, charsets, "PN", L'=', 0x20)
{
}

writingDataHandlerStringPN::writingDataHandlerStringPN(const std::shared_ptr<buffer>& pBuffer, const charsetsList::tCharsetsList& charsets):
    writingDataHandlerStringUnicode(pBuffer, charsets, "PN", L'=', 0, 0, 0x20)
{
}

void writingDataHandlerStringPN::validate() const
{
    IMEBRA_FUNCTION_START();

    if(m_strings.size() > 3)
    {
        IMEBRA_THROW(DataHandlerInvalidDataError, "A patient name can contain maximum 3 groups");
    }
    for(size_t scanGroups(0); scanGroups != m_strings.size(); ++scanGroups)
    {
        if(m_strings[scanGroups].size() > 64)
        {
            IMEBRA_THROW(DataHandlerInvalidDataError, "A patient name group can contain maximum 64 chars");
        }
    }

    writingDataHandlerStringUnicode::validate();

    IMEBRA_FUNCTION_END();
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
