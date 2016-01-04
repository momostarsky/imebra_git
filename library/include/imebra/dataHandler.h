/*
$fileHeader$
*/

/*! \file dataHandler_swig.h
    \brief Declaration of the class DataHandler for SWIG.

*/

#if !defined(imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
#define imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace puntoexe
{
namespace imebra
{
namespace handlers
{
class readingDataHandler;
class writingDataHandler;
}
}
}

#endif

#include "memory.h"

namespace imebra
{

struct IMEBRA_API Age
{
    Age(std::uint32_t age, ageUnit_t units);
    std::uint32_t age;
    ageUnit_t     units;
};

class IMEBRA_API ReadingDataHandler
{
public:
	// Costructor
	///////////////////////////////////////////////////////////
    ReadingDataHandler(const ReadingDataHandler& right);

    ReadingDataHandler& operator=(const ReadingDataHandler& right);

#ifndef SWIG
    ReadingDataHandler(std::shared_ptr<puntoexe::imebra::handlers::readingDataHandler> pDataHandler);
#endif

	void close();

    size_t getSize() const;

    size_t getUnitSize() const;

	std::string getDataType() const;

	int getSignedLong(const int index) const;

	int getUnsignedLong(const int index) const;

	double getDouble(const int index) const;

	std::wstring getString(const int index) const;

	void getDate(const int index,
		int* pYear,
		int* pMonth,
		int* pDay,
		int* pHour,
		int* pMinutes,
		int* pSeconds,
		int* pNanoseconds,
		int* pOffsetHours,
		int* pOffsetMinutes) const;

    Age getAge(const size_t index) const;

    ///
    /// \brief Copies the raw representation of the handled data into
    ///        an already allocated buffer.
    ///
    /// If the allocated buffer is not large enough then the method doesn't
    ///  copy any data and just returns the desidered size of the buffer.
    ///
    /// \param buffer     a pointer to the allocated buffer
    /// \param bufferSize the size of the allocated buffer
    /// \return the number of bytes to be copied into the pre-allocated buffer
    ///
    size_t data(char* buffer, const size_t bufferSize) const;

    ///
    /// \brief Returns a pointer to the raw representation of the handled data.
    /// \param dataSize
    /// \return
    ///
    const char* data(size_t* pDataSize) const;


#ifndef SWIG
protected:
    std::shared_ptr<puntoexe::imebra::handlers::readingDataHandler> m_pDataHandler;
#endif
};

class IMEBRA_API WritingDataHandler
{
public:
    // Costructor
    ///////////////////////////////////////////////////////////
    WritingDataHandler(const WritingDataHandler& right);

    WritingDataHandler& operator=(const WritingDataHandler& right);

#ifndef SWIG
    WritingDataHandler(std::shared_ptr<puntoexe::imebra::handlers::writingDataHandler> pDataHandler);
#endif

    void close();

    void setSize(const size_t elementsNumber);

    size_t getSize() const;

    size_t getUnitSize() const;

    std::string getDataType() const;

    void setDate(const int index,
        int year,
        int month,
        int day,
        int hour,
        int minutes,
        int seconds,
        int nanoseconds,
        int offsetHours,
        int offsetMinutes);

    void setAge(const size_t index, const Age& age);

    void setSignedLong(const int index, const int value);

    void setUnsignedLong(const int index, const int value);

    void setDouble(const int index, const double value);

    void setString(const int index, const std::wstring& value);

    void assign(const char* buffer, const size_t bufferSize);

    char* data(size_t* pDataSize) const;


#ifndef SWIG
protected:
    std::shared_ptr<puntoexe::imebra::handlers::writingDataHandler> m_pDataHandler;
#endif
};

}

#endif // !defined(imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
