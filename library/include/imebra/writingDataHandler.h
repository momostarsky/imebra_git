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
    friend class Tag;
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

    void setSize(size_t elementsNumber);

    size_t getSize() const;

    tagVR_t getDataType() const;

    WritingDataHandler& setDate(size_t index, const Date& date);

    WritingDataHandler& setAge(size_t index, const Age& age);

    WritingDataHandler& setSignedLong(size_t index, std::int32_t value);

    WritingDataHandler& setUnsignedLong(size_t index, std::uint32_t value);

    WritingDataHandler& setDouble(size_t index, double value);

    WritingDataHandler& setString(size_t index, const std::string& value);

    WritingDataHandler& setUnicodeString(size_t index, const std::wstring& value);

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::handlers::writingDataHandler> m_pDataHandler;
#endif
};

}

#endif // !defined(imebraWritingDataHandler__INCLUDED_)
