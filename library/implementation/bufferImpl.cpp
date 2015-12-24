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
        const std::shared_ptr<baseStream>& originalStream,
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
std::shared_ptr<handlers::dataHandler> buffer::getDataHandler(bool bWrite, bool bRaw, std::uint32_t size)
{
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandler");

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

	// Reset the pointer to the data handler
	///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::dataHandler> handler;

	// Allocate a raw data handler if bRaw==true
	///////////////////////////////////////////////////////////
	if(bRaw)
	{
        handler = std::make_shared<handlers::dataHandlerRaw>(m_bufferType);
	}
	else
	{
		// Retrieve an Application entity handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="AE")
		{
            handler = std::make_shared<handlers::dataHandlerStringAE>();
		}

		// Retrieve an Age string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="AS")
		{
            handler = std::make_shared<handlers::dataHandlerStringAS>();
		}

		// Retrieve a Code string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="CS")
		{
            handler = std::make_shared<handlers::dataHandlerStringCS>();
		}

		// Retrieve a Decimal string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="DS")
		{
            handler = std::make_shared<handlers::dataHandlerStringDS>();
		}

		// Retrieve an Integer string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="IS")
		{
            handler = std::make_shared<handlers::dataHandlerStringIS>();
		}

		// Retrieve a Long string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="LO")
		{
            handler = std::make_shared<handlers::dataHandlerStringLO>(m_charsetsList);
		}

		// Retrieve a Long text data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="LT")
		{
            handler = std::make_shared<handlers::dataHandlerStringLT>(m_charsetsList);
		}

		// Retrieve a Person Name data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="PN")
		{
            handler = std::make_shared<handlers::dataHandlerStringPN>(m_charsetsList);
		}

		// Retrieve a Short string data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SH")
		{
            handler = std::make_shared<handlers::dataHandlerStringSH>(m_charsetsList);
		}

		// Retrieve a Short text data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="ST")
		{
            handler = std::make_shared<handlers::dataHandlerStringST>(m_charsetsList);
		}

		// Retrieve an Unique Identifier data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UI")
		{
            handler = std::make_shared<handlers::dataHandlerStringUI>();
		}

		// Retrieve an Unlimited text data handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UT")
		{
            handler = std::make_shared< handlers::dataHandlerStringUT>(m_charsetsList);
		}

		// Retrieve an object handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="OB")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::uint8_t> >(m_bufferType);
		}

		// Retrieve a signed-byte object handler.
		// Non standard: used by the images handler.
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SB")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::int8_t> >(m_bufferType);
		}

		// Retrieve an unknown object handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UN")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::uint8_t> >(m_bufferType);
		}

		// Retrieve a WORD handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="OW")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::uint16_t> >(m_bufferType);
		}

		// Retrieve a WORD handler (AT)
		///////////////////////////////////////////////////////////
		if(m_bufferType=="AT")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::uint16_t> >(m_bufferType);
		}

		// Retrieve a float handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="FL")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<float> >(m_bufferType);
		}

		// Retrieve a double float handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="FD")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<double> >(m_bufferType);
		}

		// Retrieve a signed long handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SL")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::int32_t> >(m_bufferType);
		}

		// Retrieve a signed short handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="SS")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::int16_t> >(m_bufferType);
		}

		// Retrieve an unsigned long handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="UL")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::uint32_t> >(m_bufferType);
		}

		// Retrieve an unsigned short handler
		///////////////////////////////////////////////////////////
		if(m_bufferType=="US")
		{
            handler = std::make_shared<handlers::dataHandlerNumeric<std::uint16_t> >(m_bufferType);
		}

		// Retrieve date
		///////////////////////////////////////////////////////////
		if(m_bufferType=="DA")
		{
            handler = std::make_shared<handlers::dataHandlerDate>();
		}

		// Retrieve date-time
		///////////////////////////////////////////////////////////
		if(m_bufferType=="DT")
		{
            handler = std::make_shared<handlers::dataHandlerDateTime>();
		}

		// Retrieve time
		///////////////////////////////////////////////////////////
		if(m_bufferType=="TM")
		{
            handler = std::make_shared<handlers::dataHandlerTime>();
		}

	} // check bRaw

	// If an error occurred during the data handler creation,
	//  then throw an exception
	///////////////////////////////////////////////////////////
	if(handler == 0)
	{
		PUNTOEXE_THROW(bufferExceptionUnknownType, "Unknown data type requested");
	}

	//  Connect the handler to this buffer
	///////////////////////////////////////////////////////////
	if(localMemory == 0)
	{
        localMemory = std::shared_ptr<memory>(new memory);
	}
    std::shared_ptr<memory> parseMemory(localMemory);

	// Set the handler's attributes
	///////////////////////////////////////////////////////////
	if(bWrite)
	{
        handler->m_buffer = shared_from_this();

		std::uint32_t currentMemorySize(localMemory->size());
                std::uint32_t newMemorySize(currentMemorySize);
		if(newMemorySize == 0)
		{
			newMemorySize = size * handler->getUnitSize();
		}
        parseMemory.reset(memoryPool::getMemoryPool()->getMemory(newMemorySize));
		if(currentMemorySize != 0)
		{
			parseMemory->copyFrom(localMemory);
		}
	}

	handler->parseBuffer(parseMemory);

	// Return the allocated handler
	///////////////////////////////////////////////////////////
	return handler;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a data handler and connect it to the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::dataHandler> buffer::getDataHandler(bool bWrite, std::uint32_t size)
{
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandler");

	return getDataHandler(bWrite, false, size);

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
    std::shared_ptr<handlers::dataHandlerRaw> tempHandlerRaw = getDataHandlerRaw(false);
    if(tempHandlerRaw != 0 && tempHandlerRaw->getSize() != 0)
	{
        std::shared_ptr<baseStream> localStream(new bufferStream(tempHandlerRaw));
        reader = std::shared_ptr<streamReader>(new streamReader(localStream));
	}

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
    std::shared_ptr<handlers::dataHandlerRaw> tempHandlerRaw = getDataHandlerRaw(true);
	if(tempHandlerRaw != 0)
	{
        writer = std::make_shared<streamWriter>(std::make_shared<bufferStream>(tempHandlerRaw), tempHandlerRaw->getSize());
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
std::shared_ptr<handlers::dataHandlerRaw> buffer::getDataHandlerRaw(bool bWrite, std::uint32_t size)
{
	PUNTOEXE_FUNCTION_START(L"buffer::getDataHandlerRaw");

    std::shared_ptr<handlers::dataHandler> returnValue = getDataHandler(bWrite, true, size);
    return std::static_pointer_cast<handlers::dataHandlerRaw>(returnValue);

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
    std::shared_ptr<baseStream> emptyBaseStream;
    m_originalStream = emptyBaseStream;

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
void buffer::setCharsetsList(charsetsList::tCharsetsList* pCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"buffer::setCharsetsList");

	m_charsetsList.clear();
	charsetsList::updateCharsets(pCharsetsList, &m_charsetsList);

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

