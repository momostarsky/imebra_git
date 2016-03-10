/*
$fileHeader$
*/

/*! \file readMemory.h
    \brief Declaration of the class ReadMemory.

*/

#if !defined(imebraReadMemory__INCLUDED_)
#define imebraReadMemory__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
class memory;
}
}
#endif

namespace imebra
{

class IMEBRA_API ReadMemory
{

#ifndef SWIG
    friend class MemoryStreamInput;
    friend class ReadWriteMemory;
    friend class ReadingDataHandlerNumeric;
private:
    ReadMemory(std::shared_ptr<const implementation::memory> pMemory);
#endif


public:
    ReadMemory();

    ReadMemory(const char* buffer, size_t bufferSize);

    ReadMemory(const ReadMemory& right);

    virtual ~ReadMemory();

    ReadMemory& operator=(const ReadMemory& right);

    size_t size() const;

    const char* data() const;

    bool empty() const;

#ifndef SWIG
protected:
    std::shared_ptr<const implementation::memory> m_pMemory;
#endif
};

}

#endif // !defined(imebraReadMemory__INCLUDED_)
