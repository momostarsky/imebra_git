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
#include "../include/imebra/exceptions.h"

#include <vector>


namespace puntoexe
{

namespace imebra
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
buffer::buffer(const std::string& defaultType /* ="" */):
    m_originalBufferPosition(0),
    m_originalBufferLength(0),
    m_originalWordLength(1),
    m_originalEndianType(streamController::lowByteEndian)
{
	PUNTOEXE_FUNCTION_START(L"buffer::buffer");

	// Set the buffer's type.
	// If the buffer's type is unspecified, then the buffer
	//  type is set to OB
	///////////////////////////////////////////////////////////
	if(defaultType.length()==2L)
		m_bufferType = defaultType;
	else
		m_bufferType = "OB";

	PUNTOEXE_FUNCTION_END();
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
        const std::shared_ptr<baseStreamReader>& originalStream,
		std::uint32_t bufferPosition,
		std::uint32_t bufferLength,
		std::uint32_t wordLength,
		streamController::tByteOrdering endianType):
		m_originalStream(originalStream),
		m_originalBufferPosition(bufferPosition),
		m_originalBufferLength(bufferLength),
		m_originalWordLength(wordLength),
        m_originalEndianType(endianType)
{
	PUNTOEXE_FUNCTION_START(L"buffer::buffer (on demand)");

	// Set the buffer's type.
	// If the buffer's type is unspecified, then the buffer
	//  type is set to OB
	///////////////////////////////////////////////////////////
	if(defaultType.length()==2L)
		m_bufferType = defaultType;
	else
		m_bufferType = "OB";

	PUNTOEXE_FUNCTION_END();
}


std::shared_ptr<memory> buffer::getLocalMemory() const
{
    std::shared_ptr<memory> localMemory(m_memory);

    // If the object must be loaded from the original stream,
    //  then load it...
    ///////////////////////////////////////////////////////////
    if(m_originalStream != 0 && (localMemory == 0 || localMemory->empty()) )
    {
        localMemory = std::shared_ptr<memory>(memoryPool::getMemoryPool()->getMemory(m_originalBufferLength));
        if(m_originalBufferLength != 0)
        {
            std::shared_ptr<streamReader> reader(new streamReader(m_originalStream, m_originalBufferPosition, m_originalBufferLength));
            std::vector<std::uint8_t> localBuffer;
            localBuffer.resize(m_originalBufferLength);
            reader->read(&localBuffer[0], m_originalBufferLength);
            if(m_originalWordLength != 0)
            {
                reader->adjustEndian(&localBuffer[0], m_originalWordLength, m_originalEndianType, m_originalBufferLength/m_originalWordLength);
            }
            localMemory->assign(&localBuffer[0], m_originalBufferLength);
        }
    }

    return localMemory;

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
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandler");

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
    if(m_bufferType=="FL")
    {
        return std::make_shared<handlers::readingDataHandlerNumeric<float> >(localMemory, m_bufferType);
    }

    // Retrieve a double float handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="FD")
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

    PUNTOEXE_THROW(::imebra::bufferExceptionUnknownType, "Unknown data type requested");

	PUNTOEXE_FUNCTION_END();
}

std::shared_ptr<handlers::writingDataHandler> buffer::getWritingDataHandler(std::uint32_t size)
{
    PUNTOEXE_FUNCTION_START(L"buffer::getDataHandler");

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
    if(m_bufferType=="FL")
    {
        return std::make_shared<handlers::writingDataHandlerNumeric<float> >(shared_from_this(), size, m_bufferType);
    }

    // Retrieve a double float handler
    ///////////////////////////////////////////////////////////
    if(m_bufferType=="FD")
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

    PUNTOEXE_THROW(::imebra::bufferExceptionUnknownType, "Unknown data type requested");

    PUNTOEXE_FUNCTION_END();
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
	PUNTOEXE_FUNCTION_START(L"buffer::getStreamReader");

	// If the object must be loaded from the original stream,
	//  then return the original stream
	///////////////////////////////////////////////////////////
	if(m_originalStream != 0 && (m_memory == 0 || m_memory->empty()) )
	{
        std::shared_ptr<streamReader> reader(new streamReader(m_originalStream, m_originalBufferPosition, m_originalBufferLength));
		return reader;
	}


	// Build a stream from the buffer's memory
	///////////////////////////////////////////////////////////
    std::shared_ptr<streamReader> reader;
    std::shared_ptr<memoryStreamReader> memoryStream = std::make_shared<memoryStreamReader>(getLocalMemory());
    reader = std::shared_ptr<streamReader>(new streamReader(memoryStream));

	return reader;

	PUNTOEXE_FUNCTION_END();
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
    PUNTOEXE_FUNCTION_START(L"buffer::getStreamWriter");

	// Build a stream from the buffer's memory
	///////////////////////////////////////////////////////////
    std::shared_ptr<streamWriter> writer;
    std::shared_ptr<handlers::writingDataHandlerRaw> tempHandlerRaw = getWritingDataHandlerRaw(0);
	if(tempHandlerRaw != 0)
	{
        writer = std::make_shared<streamWriter>(std::make_shared<bufferStreamWriter>(tempHandlerRaw), tempHandlerRaw->getSize());
	}

	return writer;

	PUNTOEXE_FUNCTION_END();
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
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandlerRaw");

    std::shared_ptr<memory> localMemory(getLocalMemory());

    // Allocate a raw data handler if bRaw==true
    ///////////////////////////////////////////////////////////
    return std::make_shared<handlers::readingDataHandlerRaw>(localMemory, m_bufferType);

	PUNTOEXE_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerRaw> buffer::getWritingDataHandlerRaw(std::uint32_t size)
{
    PUNTOEXE_FUNCTION_START(L"buffer::getDataHandlerRaw");

    return std::make_shared<handlers::writingDataHandlerRaw>(shared_from_this(), size, m_bufferType);

    PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
// Return the buffer's size in bytes
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t buffer::getBufferSizeBytes() const
{
	// The buffer has not been loaded yet
	///////////////////////////////////////////////////////////
	if(m_originalStream != 0 && (m_memory == 0 || m_memory->empty()) )
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
	PUNTOEXE_FUNCTION_START(L"buffer::commit");

    commit(newMemory, newBufferType);

	// Commit the charsets
	///////////////////////////////////////////////////////////
    m_charsetsList = newCharsetsList;

	PUNTOEXE_FUNCTION_END();
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
    PUNTOEXE_FUNCTION_START(L"buffer::commit");

    // Commit the memory buffer
    ///////////////////////////////////////////////////////////
    m_memory = newMemory;

    // Commit the buffer type
    ///////////////////////////////////////////////////////////
    m_bufferType = newBufferType;

    // The buffer has been updated and the original stream
    //  is still storing the old version. We don't need
    //  the original stream anymore, then release it.
    ///////////////////////////////////////////////////////////
    m_originalStream.reset();

    PUNTOEXE_FUNCTION_END();
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
    return m_bufferType;
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
	PUNTOEXE_FUNCTION_START(L"buffer::setCharsetsList");

    m_charsetsList = charsets;

	PUNTOEXE_FUNCTION_END();
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
	PUNTOEXE_FUNCTION_START(L"buffer::getCharsetsList");

    pCharsetsList->insert(pCharsetsList->end(), m_charsetsList.begin(), m_charsetsList.end());

	PUNTOEXE_FUNCTION_END();
}


} // namespace imebra

} // namespace puntoexe

