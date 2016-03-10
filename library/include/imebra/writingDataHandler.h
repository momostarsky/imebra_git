/*
$fileHeader$
*/

/// \file writingDataHandler.h
/// \brief Declaration of the class WritingDataHandler.
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraWritingDataHandler__INCLUDED_)
#define imebraWritingDataHandler__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "readWriteMemory.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
namespace handlers
{
class writingDataHandler;
}
}
}

#endif


namespace imebra
{

class IMEBRA_API WritingDataHandler
{
#ifndef SWIG
    friend class DataSet;
    friend class TagContent;
    friend class WritingDataHandlerNumeric;

private:
    WritingDataHandler(std::shared_ptr<imebra::implementation::handlers::writingDataHandler> pDataHandler);
#endif

public:
    // Costructor
    ///////////////////////////////////////////////////////////
    WritingDataHandler(const WritingDataHandler& right);

    virtual ~WritingDataHandler();

    WritingDataHandler& operator=(const WritingDataHandler& right);

    void close();

    void setSize(const size_t elementsNumber);

    size_t getSize() const;

    std::string getDataType() const;

    WritingDataHandler& setDate(const size_t index, const Date& date);

    WritingDataHandler& setAge(const size_t index, const Age& age);

    WritingDataHandler& setSignedLong(const size_t index, const std::int32_t value);

    WritingDataHandler& setUnsignedLong(const size_t index, const std::uint32_t value);

    WritingDataHandler& setDouble(const size_t index, const double value);

    WritingDataHandler& setString(const size_t index, const std::string& value);

    WritingDataHandler& setUnicodeString(const size_t index, const std::wstring& value);

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::handlers::writingDataHandler> m_pDataHandler;
#endif
};

}

#endif // !defined(imebraWritingDataHandler__INCLUDED_)
