/*
$fileHeader$
*/

/// \file writingDataHandlerNumeric.h
/// \brief Declaration of the class WritingDataHandlerNumeric.
///
///////////////////////////////////////////////////////////////////////////////

#if !defined(imebraWritingDataHandlerNumeric__INCLUDED_)
#define imebraWritingDataHandlerNumeric__INCLUDED_

#include <string>
#include <memory>
#include "definitions.h"
#include "readWriteMemory.h"
#include "writingDataHandler.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
namespace handlers
{
class writingDataHandlerNumericBase;
}
}
}

#endif


namespace imebra
{

class IMEBRA_API WritingDataHandlerNumeric: public WritingDataHandler
{
#ifndef SWIG
    friend class Image;
    friend class DataSet;
    friend class TagContent;
private:
    WritingDataHandlerNumeric(std::shared_ptr<imebra::implementation::handlers::writingDataHandlerNumericBase> pDataHandler);
#endif

public:
    // Costructor
    ///////////////////////////////////////////////////////////
    WritingDataHandlerNumeric(const WritingDataHandlerNumeric& right);

    WritingDataHandlerNumeric& operator=(const WritingDataHandlerNumeric& right);

    ReadWriteMemory getMemory() const;

    void assign(const char* buffer, const size_t bufferSize);

    char* data(size_t* pDataSize) const;

    size_t getUnitSize() const;

    bool isSigned() const;
};

}

#endif // !defined(imebraWritingDataHandlerNumeric__INCLUDED_)
