/*
$fileHeader$
*/

/*! \file buffer.cpp
    \brief Implementation of the buffer class.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "bufferImpl.h"
#include "bufferStreamImpl.h"
#include "dataHandlerImpl.h"
#include "dataHandlerNumericImpl.h"
#include "dataHandlerStringAEImpl.h"
#include "dataHandlerStringASImpl.h"
#include "dataHandlerStringCSImpl.h"
#include "dataHandlerStringDSImpl.h"
#include "dataHandlerStringISImpl.h"
#include "dataHandlerStringLOImpl.h"
#include "dataHandlerStringLTImpl.h"
#include "dataHandlerStringPNImpl.h"
#include "dataHandlerStringSHImpl.h"
#include "dataHandlerStringSTImpl.h"
#include "dataHandlerStringUIImpl.h"
#include "dataHandlerStringUTImpl.h"
#include "dataHandlerDateImpl.h"
#include "dataHandlerDateTimeImpl.h"
#include "dataHandlerTimeImpl.h"
#include "dicomDictImpl.h"
#include "../include/imebra/exceptions.h"

#include <vector>


namespace imebra
{

namespace implementation
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// imebraBuffer
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Buffer's constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
buffer::buffer(const std::string& defaultType):
    m_bufferType(defaultType),
    m_originalBufferPosition(0),
    m_originalBufferLength(0),
    m_originalWordLength(1),
    m_originalEndianType(streamController::lowByteEndian)
{
    IMEBRA_FUNCTION_START();

    if(!dicomDictionary::getDicomDictionary()->isDataTypeValid(defaultType))
    {
        IMEBRA_THROW(BufferUnknownTypeError, "Unknown data type " << defaultType);
    }

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Buffer's constructor (on demand content)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
buffer::buffer(
		const std::string& defaultType,
        const std::shared_ptr<baseStreamInput>& originalStream,
        size_t bufferPosition,
        size_t bufferLength,
        size_t wordLength,
		streamController::tByteOrdering endianType):
        m_bufferType(defaultType),
		m_originalStream(originalStream),
		m_originalBufferPosition(bufferPosition),
		m_originalBufferLength(bufferLength),
		m_originalWordLength(wordLength),
        m_originalEndianType(endianType)
{
    IMEBRA_FUNCTION_START();

    if(!dicomDictionary::getDicomDictionary()->isDataTypeValid(defaultType))
    {
        IMEBRA_THROW(BufferUnknownTypeError, "Unknown data type " << defaultType);
    }

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<memory> buffer::getLocalMemory() const
{
    IMEBRA_FUNCTION_START();

    // If the object must be loaded from the original stream,
    //  then load it...
    ///////////////////////////////////////////////////////////
    if(m_originalStream != 0)
    {
        std::shared_ptr<memory> localMemory(std::make_shared<memory>(m_originalBufferLength));
        if(m_originalBufferLength != 0)
        {
            std::shared_ptr<streamReader> reader(std::make_shared<streamReader>(m_originalStream, m_originalBufferPosition, m_originalBufferLength));
            std::vector<std::uint8_t> localBuffer;
            localBuffer.resize(m_originalBufferLength);
            reader->read(&localBuffer[0], m_originalBufferLength);
            if(m_originalWordLength != 0)
            {
                reader->adjustEndian(&localBuffer[0], m_originalWordLength, m_originalEndianType, m_originalBufferLength/m_originalWordLength);
            }
            localMemory->assign(&localBuffer[0], m_originalBufferLength);
        }
        return localMemory;
    }

    if(m_memory == 0)
    {
        return std::make_shared<memory>();
    }

    return m_memory;

    IMEBRA_FUNCTION_END();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a data handler and connect it to the buffer
// (raw or normal)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandler> buffer::getReadingDataHandler() const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    std::shared_ptr<const memory> localMemory(getLocalMemory());

    // Retrieve an Application entity handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="AE")
    {
        return std::make_shared<handlers::readingDataHandlerStringAE>(*localMemory);
    }

    // Retrieve an Age string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="AS")
    {
        return std::make_shared<handlers::readingDataHandlerStringAS>(*localMemory);
    }

    // Retrieve a Code string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="CS")
    {
        return std::make_shared<handlers::readingDataHandlerStringCS>(*localMemory);
    }

    // Retrieve a Decimal string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="DS")
    {
        return std::make_shared<handlers::readingDataHandlerStringDS>(*localMemory);
    }

    // Retrieve an Integer string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="IS")
    {
        return std::make_shared<handlers::readingDataHandlerStringIS>(*localMemory);
    }

    // Retrieve a Long string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="LO")
    {
        return std::make_shared<handlers::readingDataHandlerStringLO>(*localMemory, m_charsetsList);
    }

    // Retrieve a Long text data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="LT")
    {
        return std::make_shared<handlers::readingDataHandlerStringLT>(*localMemory, m_charsetsList);
    }

    // Retrieve a Person Name data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="PN")
    {
        return std::make_shared<handlers::readingDataHandlerStringPN>(*localMemory, m_charsetsList);
    }

    // Retrieve a Short string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SH")
    {
        return std::make_shared<handlers::readingDataHandlerStringSH>(*localMemory, m_charsetsList);
    }

    // Retrieve a Short text data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="ST")
    {
        return std::make_shared<handlers::readingDataHandlerStringST>(*localMemory, m_charsetsList);
    }

    // Retrieve an Unique Identifier data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UI")
    {
        return std::make_shared<handlers::readingDataHandlerStringUI>(*localMemory);
    }

    // Retrieve an Unlimited text data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UT")
    {
        return std::make_shared< handlers::readingDataHandlerStringUT>(*localMemory, m_charsetsList);
    }

    // Retrieve an object handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="OB")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::uint8_t> >(localMemory, m_bufferType);
    }

    // Retrieve a signed-byte object handler.
    // Non standard: used by the images handler.
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SB")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::int8_t> >(localMemory, m_bufferType);
    }

    // Retrieve an unknown object handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UN")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::uint8_t> >(localMemory, m_bufferType);
    }

    // Retrieve a WORD handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="OW")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::uint16_t> >(localMemory, m_bufferType);
    }

    // Retrieve a WORD handler (AT)
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="AT")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::uint16_t> >(localMemory, m_bufferType);
    }

    // Retrieve a float handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="FL" || m_bufferType == "OF")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<float> >(localMemory, m_bufferType);
    }

    // Retrieve a double float handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType == "FD" || m_bufferType == "OD")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<double> >(localMemory, m_bufferType);
    }

    // Retrieve a signed long handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SL")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::int32_t> >(localMemory, m_bufferType);
    }

    // Retrieve a signed short handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SS")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::int16_t> >(localMemory, m_bufferType);
    }

    // Retrieve an unsigned long handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UL")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::uint32_t> >(localMemory, m_bufferType);
    }

    // Retrieve an unsigned short handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="US")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<std::uint16_t> >(localMemory, m_bufferType);
    }

    // Retrieve date
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="DA")
    {
        return std::make_shared<handlers::readingDataHandlerDate>(*localMemory);
    }

    // Retrieve date-time
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="DT")
    {
        return std::make_shared<handlers::readingDataHandlerDateTime>(*localMemory);
    }

    // Retrieve time
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="TM")
    {
        return std::make_shared<handlers::readingDataHandlerTime>(*localMemory);
    }

    IMEBRA_THROW(BufferUnknownTypeError, "Unknown data type requested (" << m_bufferType << ")");

	IMEBRA_FUNCTION_END();
}

std::shared_ptr<handlers::writingDataHandler> buffer::getWritingDataHandler(std::uint32_t size)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Reset the pointer to the data handler
    ///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::writingDataHandler> handler;

    // Retrieve an Application entity handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="AE")
    {
        return std::make_shared<handlers::writingDataHandlerStringAE>(shared_from_this());
    }

    // Retrieve an Age string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="AS")
    {
        return std::make_shared<handlers::writingDataHandlerStringAS>(shared_from_this());
    }

    // Retrieve a Code string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="CS")
    {
        return std::make_shared<handlers::writingDataHandlerStringCS>(shared_from_this());
    }

    // Retrieve a Decimal string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="DS")
    {
        return std::make_shared<handlers::writingDataHandlerStringDS>(shared_from_this());
    }

    // Retrieve an Integer string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="IS")
    {
        return std::make_shared<handlers::writingDataHandlerStringIS>(shared_from_this());
    }

    // Retrieve a Long string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="LO")
    {
        return std::make_shared<handlers::writingDataHandlerStringLO>(shared_from_this(), m_charsetsList);
    }

    // Retrieve a Long text data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="LT")
    {
        return std::make_shared<handlers::writingDataHandlerStringLT>(shared_from_this(), m_charsetsList);
    }

    // Retrieve a Person Name data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="PN")
    {
        return std::make_shared<handlers::writingDataHandlerStringPN>(shared_from_this(), m_charsetsList);
    }

    // Retrieve a Short string data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SH")
    {
        return std::make_shared<handlers::writingDataHandlerStringSH>(shared_from_this(), m_charsetsList);
    }

    // Retrieve a Short text data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="ST")
    {
        return std::make_shared<handlers::writingDataHandlerStringST>(shared_from_this(), m_charsetsList);
    }

    // Retrieve an Unique Identifier data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UI")
    {
        return std::make_shared<handlers::writingDataHandlerStringUI>(shared_from_this());
    }

    // Retrieve an Unlimited text data handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UT")
    {
        return std::make_shared< handlers::writingDataHandlerStringUT>(shared_from_this(), m_charsetsList);
    }

    // Retrieve an object handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="OB")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::uint8_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a signed-byte object handler.
    // Non standard: used by the images handler.
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SB")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::int8_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve an unknown object handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UN")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::uint8_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a WORD handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="OW")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::uint16_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a WORD handler (AT)
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="AT")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::uint16_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a float handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="FL" || m_bufferType == "OF")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<float> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a double float handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType == "FD" || m_bufferType == "OD")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<double> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a signed long handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SL")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::int32_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a signed short handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="SS")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::int16_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve an unsigned long handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="UL")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::uint32_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve an unsigned short handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="US")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<std::uint16_t> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve date
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="DA")
    {
        return std::make_shared<handlers::writingDataHandlerDate>(shared_from_this());
    }

    // Retrieve date-time
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="DT")
    {
        return std::make_shared<handlers::writingDataHandlerDateTime>(shared_from_this());
    }

    // Retrieve time
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="TM")
    {
        return std::make_shared<handlers::writingDataHandlerTime>(shared_from_this());
    }

    IMEBRA_THROW(BufferUnknownTypeError, "Unknown data type requested");

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a reading stream for the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamReader> buffer::getStreamReader()
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

	// If the object must be loaded from the original stream,
	//  then return the original stream
	///////////////////////////////////////////////////////////
    if(m_originalStream != 0 && (m_originalWordLength <= 1 && m_originalEndianType != streamReader::getPlatformEndian()))
	{
        std::shared_ptr<streamReader> reader(std::make_shared<streamReader>(m_originalStream, m_originalBufferPosition, m_originalBufferLength));
		return reader;
	}

	// Build a stream from the buffer's memory
	///////////////////////////////////////////////////////////
    std::shared_ptr<streamReader> reader;
    std::shared_ptr<memoryStreamInput> memoryStream = std::make_shared<memoryStreamInput>(getLocalMemory());
    reader = std::shared_ptr<streamReader>(std::make_shared<streamReader>(memoryStream));

	return reader;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a writing stream for the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamWriter> buffer::getStreamWriter()
{
    IMEBRA_FUNCTION_START();

    std::shared_ptr<handlers::writingDataHandlerRaw> tempHandlerRaw = getWritingDataHandlerRaw(0);
    return std::make_shared<streamWriter>(std::make_shared<bufferStreamOutput>(tempHandlerRaw), tempHandlerRaw->getSize());

	IMEBRA_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a raw data handler and connect it to the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandlerRaw> buffer::getReadingDataHandlerRaw() const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    return std::make_shared<handlers::readingDataHandlerRaw>(getLocalMemory(), m_bufferType);

	IMEBRA_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerRaw> buffer::getWritingDataHandlerRaw(std::uint32_t size)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    return std::make_shared<handlers::writingDataHandlerRaw>(shared_from_this(), size, m_bufferType);

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Return the buffer's size in bytes
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
size_t buffer::getBufferSizeBytes() const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // The buffer has not been loaded yet
	///////////////////////////////////////////////////////////
    if(m_originalStream != 0)
	{
		return m_originalBufferLength;
	}

	// The buffer has no memory
	///////////////////////////////////////////////////////////
	if(m_memory == 0)
	{
		return 0;
	}

	// Return the memory's size
	///////////////////////////////////////////////////////////
	return m_memory->size();

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Commit the changes made by copyBack
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void buffer::commit(std::shared_ptr<memory> newMemory, const std::string& newBufferType, const charsetsList::tCharsetsList& newCharsetsList)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    m_memory = newMemory;
    m_bufferType = newBufferType;
    m_originalStream.reset();
    m_charsetsList = newCharsetsList;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Commit the changes made by copyBack
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void buffer::commit(std::shared_ptr<memory> newMemory, const std::string& newBufferType)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    m_memory = newMemory;
    m_bufferType = newBufferType;
    m_originalStream.reset();

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the data type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string buffer::getDataType() const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);
    return m_bufferType;

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the charsets used by the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void buffer::setCharsetsList(const charsetsList::tCharsetsList& charsets)
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);
    m_charsetsList = charsets;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the charsets used by the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void buffer::getCharsetsList(charsetsList::tCharsetsList* pCharsetsList) const
{
    IMEBRA_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);
    pCharsetsList->insert(pCharsetsList->end(), m_charsetsList.begin(), m_charsetsList.end());

	IMEBRA_FUNCTION_END();
}


} // namespace implementation

} // namespace imebra

