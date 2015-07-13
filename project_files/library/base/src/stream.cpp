/*
$fileHeader$
*/

/*! \file stream.cpp
    \brief Implementation of the stream class.

*/

#include "../include/exception.h"
#include "../include/stream.h"
#include "../include/charsetConversion.h"
#include <sstream>

namespace puntoexe
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// Stream
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
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
stream::~stream()
{
	if(m_openFile != 0)
	{
		::fclose(m_openFile);
	}
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Open a file (ansi)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void stream::openFile(const std::string& fileName, const int mode)
{
	PUNTOEXE_FUNCTION_START(L"stream::openFile (ansi)");

	std::wstring wFileName;
	size_t fileNameSize(fileName.size());
	wFileName.resize(fileNameSize);
	for(size_t copyChars = 0; copyChars != fileNameSize; ++copyChars)
	{
		wFileName[copyChars] = (wchar_t)fileName[copyChars];
	}
	openFile(wFileName, mode);

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Open a file (unicode)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void stream::openFile(const std::wstring& fileName, const int mode)
{
	PUNTOEXE_FUNCTION_START(L"stream::openFile (unicode)");
	if(m_openFile)
	{
		if(::fclose(m_openFile)!=0)
		{
			PUNTOEXE_THROW(streamExceptionClose, "Error while closing the file");
		}
		m_openFile = 0;
	}

	std::wstring strMode;

	int tempMode = mode & (~std::ios::binary);

	if(tempMode == (int)(std::ios::in | std::ios::out))
	{
		strMode = L"r+";
	}

	if(tempMode == (int)(std::ios::in | std::ios::out | std::ios::app))
	{
		strMode = L"a+";
	}
	
	if(tempMode == (int)(std::ios::in | std::ios::out | std::ios::trunc))
	{
		strMode = L"w+";
	}
	
	if(tempMode == (int)(std::ios::out) || tempMode == (int)(std::ios::out | std::ios::trunc))
	{
		strMode = L"w";
	}
	
	if(tempMode == (int)(std::ios::out | std::ios::app))
	{
		strMode = L"a";
	}
	
	if(tempMode == (int)(std::ios::in))
	{
		strMode = L"r";
	}

	strMode += L"b";

#if defined(PUNTOEXE_WINDOWS)
	m_openFile = ::_wfopen(fileName.c_str(), strMode.c_str());
#else
	// Convert the filename to UTF8
    std::auto_ptr<charsetConversion> toUtf8(allocateCharsetConversion());
    toUtf8->initialize("ISO-IR 192");
    std::string utf8FileName(toUtf8->fromUnicode(fileName));

	// Convert the filemode to UTF8
    std::string utf8Mode(toUtf8->fromUnicode(strMode));
	
	m_openFile = ::fopen(utf8FileName.c_str(), utf8Mode.c_str());
#endif
	if(m_openFile == 0)
	{
		PUNTOEXE_THROW(streamExceptionOpen, "stream::openFile failure");
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write raw data into the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void stream::write(std::uint32_t startPosition, const std::uint8_t* pBuffer, std::uint32_t bufferLength)
{
	PUNTOEXE_FUNCTION_START(L"stream::write");

	lockObject lockThis(this);

	::fseek(m_openFile, startPosition, SEEK_SET);
	if(ferror(m_openFile) != 0)
	{
		PUNTOEXE_THROW(streamExceptionWrite, "stream::seek failure");
	}

	if(::fwrite(pBuffer, 1, bufferLength, m_openFile) != bufferLength)
	{
		PUNTOEXE_THROW(streamExceptionWrite, "stream::write failure");
	}

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read raw data from the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t stream::read(std::uint32_t startPosition, std::uint8_t* pBuffer, std::uint32_t bufferLength)
{
	PUNTOEXE_FUNCTION_START(L"stream::read");

	lockObject lockThis(this);

	::fseek(m_openFile, startPosition, SEEK_SET);
	if(ferror(m_openFile) != 0)
	{
		return 0;
	}

	std::uint32_t readBytes = (std::uint32_t)::fread(pBuffer, 1, bufferLength, m_openFile);
	if(ferror(m_openFile) != 0)
	{
		PUNTOEXE_THROW(streamExceptionRead, "stream::read failure");
	}
	return readBytes;

	PUNTOEXE_FUNCTION_END();
}


} // namespace puntoexe
