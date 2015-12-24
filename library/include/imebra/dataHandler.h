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

namespace puntoexe
{
namespace imebra
{
namespace handlers
{
class dataHandler;
}
}
}

#endif

#include "memory.h"

namespace imebra
{

/// \addtogroup group_swig_bindings Bindings
///
/// The binding classes interface the Imebra library
///  with software written in Java, PHP, Python and others.
///
///////////////////////////////////////////////////////////
/// @{

class DataHandler
{
public:
	// Costructor
	///////////////////////////////////////////////////////////
	DataHandler(const DataHandler& right);

	DataHandler& operator=(const DataHandler& right);

#ifndef SWIG
    DataHandler(std::shared_ptr<puntoexe::imebra::handlers::dataHandler> pDataHandler);
#endif

	void close();

    void setSize(const size_t elementsNumber);

    size_t getSize() const;

    size_t getUnitSize() const;

	std::string getDataType() const;

	char getPaddingByte() const;

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

	void setSignedLong(const int index, const int value);

	void setUnsignedLong(const int index, const int value);

	void setDouble(const int index, const double value);

	void setString(const int index, const std::wstring& value);

    Memory getMemory();

#ifndef SWIG
protected:
	std::shared_ptr<puntoexe::imebra::handlers::dataHandler> m_pDataHandler;
#endif
};

///@}

}

#endif // !defined(imebraDataHandler_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
