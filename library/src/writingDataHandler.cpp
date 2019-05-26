/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/imebra/writingDataHandler.h"
#include "../include/imebra/date.h"
#include "../include/imebra/age.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace imebra
{

WritingDataHandler::~WritingDataHandler()
{
}

WritingDataHandler::WritingDataHandler(const std::shared_ptr<implementation::handlers::writingDataHandler>& pDataHandler): m_pDataHandler(pDataHandler)
{}

WritingDataHandler::WritingDataHandler(const WritingDataHandler& source): m_pDataHandler(getWritingDataHandlerImplementation(source))
{
}

WritingDataHandler& WritingDataHandler::operator=(const WritingDataHandler& source)
{
    m_pDataHandler = getWritingDataHandlerImplementation(source);
    return *this;
}

const std::shared_ptr<implementation::handlers::writingDataHandler>& getWritingDataHandlerImplementation(const WritingDataHandler& writingHandler)
{
    return writingHandler.m_pDataHandler;
}

void WritingDataHandler::setSize(size_t elementsNumber)
{
    m_pDataHandler->setSize(elementsNumber);
}

size_t WritingDataHandler::getSize() const
{
    return m_pDataHandler->getSize();
}

tagVR_t WritingDataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}


void WritingDataHandler::setDate(size_t index, const Date& date)
{
    m_pDataHandler->setDate((std::uint32_t)index, getDateImplementation(date));
}

void WritingDataHandler::setAge(size_t index, const Age& age)
{
    m_pDataHandler->setAge(index, getAgeImplementation(age));
}

void WritingDataHandler::setSignedLong(size_t index, std::int32_t value)
{
    m_pDataHandler->setSignedLong(index, value);
}

void WritingDataHandler::setUnsignedLong(size_t index, std::uint32_t value)
{
    m_pDataHandler->setUnsignedLong(index, value);
}

void WritingDataHandler::setDouble(size_t index, double value)
{
    m_pDataHandler->setDouble(index, value);
}

void WritingDataHandler::setString(size_t index, const std::string& value)
{
    m_pDataHandler->setString(index, value);
}

void WritingDataHandler::setUnicodeString(size_t index, const std::wstring& value)
{
    m_pDataHandler->setUnicodeString(index, value);
}

}
