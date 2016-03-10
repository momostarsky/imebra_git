/*
$fileHeader$
*/

/*! \file memory.h
    \brief Declaration of the class Memory.

*/

#if !defined(imebraMemory__INCLUDED_)
#define imebraMemory__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
class memory;
class memoryPool;
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


class IMEBRA_API MemoryPool
{
public:
    static void flush();
    static void setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize);
};

}

#endif // !defined(imebraMemory__INCLUDED_)
