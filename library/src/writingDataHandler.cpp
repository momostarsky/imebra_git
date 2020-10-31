/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/dicomhero/writingDataHandler.h"
#include "../include/dicomhero/date.h"
#include "../include/dicomhero/age.h"
#include "../include/dicomhero/patientName.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace dicomhero
{

WritingDataHandler::~WritingDataHandler()
{
}

WritingDataHandler::WritingDataHandler(const std::shared_ptr<implementation::handlers::writingDataHandler>& pDataHandler): m_pDataHandler(pDataHandler)
{}

WritingDataHandler::WritingDataHandler(const WritingDataHandler& source): m_pDataHandler(getWritingDataHandlerImplementation(source))
{
}

const std::shared_ptr<implementation::handlers::writingDataHandler>& getWritingDataHandlerImplementation(const WritingDataHandler& writingHandler)
{
    return writingHandler.m_pDataHandler;
}

void WritingDataHandler::setSize(size_t elementsNumber)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setSize(elementsNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

size_t WritingDataHandler::getSize() const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getSize();

    DICOMHERO_FUNCTION_END_LOG();
}

tagVR_t WritingDataHandler::getDataType() const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getDataType();

    DICOMHERO_FUNCTION_END_LOG();
}


void WritingDataHandler::setDate(size_t index, const Date& date)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setDate((std::uint32_t)index, getDateImplementation(date));

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setAge(size_t index, const Age& age)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setAge(index, getAgeImplementation(age));

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setInt32(size_t index, std::int32_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setInt32(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setSignedLong(size_t index, std::int32_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setInt32(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setUint32(size_t index, std::uint32_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setUint32(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setUnsignedLong(size_t index, std::uint32_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setUint32(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setInt16(size_t index, std::int16_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setInt16(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setUint16(size_t index, std::uint16_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setUint16(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setInt8(size_t index, std::int8_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setInt8(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setUint8(size_t index, std::uint8_t value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setUint8(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setDouble(size_t index, double value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setDouble(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setFloat(size_t index, float value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setFloat(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setString(size_t index, const std::string& value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setString(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setUnicodeString(size_t index, const std::wstring& value)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setUnicodeString(index, value);

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setPatientName(size_t index, const PatientName& patientName)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setPatientName(index, getPatientNameImplementation(patientName));

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandler::setUnicodePatientName(size_t index, const UnicodePatientName& patientName)
{
    DICOMHERO_FUNCTION_START();

    m_pDataHandler->setUnicodePatientName(index, getUnicodePatientNameImplementation(patientName));

    DICOMHERO_FUNCTION_END_LOG();
}

}
