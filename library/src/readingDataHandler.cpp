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

#include "../include/imebra/readingDataHandler.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../include/imebra/age.h"
#include "../include/imebra/patientName.h"
#include <cstring>

namespace imebra
{

ReadingDataHandler::ReadingDataHandler(const std::shared_ptr<implementation::handlers::readingDataHandler>& pDataHandler): m_pDataHandler(pDataHandler)
{
}

ReadingDataHandler::ReadingDataHandler(const ReadingDataHandler& source): m_pDataHandler(getReadingDataHandlerImplementation(source))
{
}

ReadingDataHandler& ReadingDataHandler::operator=(const ReadingDataHandler& source)
{
    m_pDataHandler = getReadingDataHandlerImplementation(source);
    return *this;
}

ReadingDataHandler::~ReadingDataHandler()
{
}

const std::shared_ptr<implementation::handlers::readingDataHandler>& getReadingDataHandlerImplementation(const ReadingDataHandler& readingDataHandler)
{
    return readingDataHandler.m_pDataHandler;
}

size_t ReadingDataHandler::getSize() const
{
    return m_pDataHandler->getSize();
}

tagVR_t ReadingDataHandler::getDataType() const
{
    return m_pDataHandler->getDataType();
}

std::int32_t ReadingDataHandler::getSignedLong(size_t index) const
{
    return m_pDataHandler->getSignedLong(index);
}

std::uint32_t ReadingDataHandler::getUnsignedLong(size_t index) const
{
    return m_pDataHandler->getUnsignedLong(index);
}

double ReadingDataHandler::getDouble(size_t index) const
{
    return m_pDataHandler->getDouble(index);
}

std::string ReadingDataHandler::getString(size_t index) const
{
    return m_pDataHandler->getString(index);
}

std::wstring ReadingDataHandler::getUnicodeString(size_t index) const
{
    return m_pDataHandler->getUnicodeString(index);
}

const Date ReadingDataHandler::getDate(size_t index) const
{
    return Date(m_pDataHandler->getDate(index));
}

const Age ReadingDataHandler::getAge(size_t index) const
{
    return Age(m_pDataHandler->getAge(index));
}

const PatientName ReadingDataHandler::getPatientName(size_t index) const
{
    return PatientName(m_pDataHandler->getPatientName(index));
}

const UnicodePatientName ReadingDataHandler::getUnicodePatientName(size_t index) const
{
    return UnicodePatientName(m_pDataHandler->getUnicodePatientName(index));
}



}
