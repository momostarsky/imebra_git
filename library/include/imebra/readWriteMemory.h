/*
$fileHeader$
*/

/*! \file readWriteMemory.h
    \brief Declaration of the class ReadWriteMemory.

*/

#if !defined(imebraReadWriteMemory__INCLUDED_)
#define imebraReadWriteMemory__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"
#include "readMemory.h"

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

class IMEBRA_API ReadWriteMemory: public ReadMemory
{

#ifndef SWIG
    friend class MemoryStreamOutput;
    friend class DrawBitmap;
    friend class WritingDataHandlerNumeric;
private:
    ReadWriteMemory(std::shared_ptr<implementation::memory> pMemory);
#endif

public:

    ReadWriteMemory();

    ReadWriteMemory(size_t initialSize);

    ReadWriteMemory(const char* buffer, size_t bufferSize);

    ReadWriteMemory(const ReadWriteMemory& right);

    ReadWriteMemory& operator=(const ReadWriteMemory& right);

    void copyFrom(const ReadMemory& sourceMemory);

    void copyFrom(const ReadWriteMemory& sourceMemory);

    void clear();

    void resize(size_t newSize);

    void reserve(size_t reserveSize);

    char* data();

    void assign(const char* pSource, const size_t sourceLength);
};

}

#endif // !defined(imebraReadWriteMemory__INCLUDED_)
