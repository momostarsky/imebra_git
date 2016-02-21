/*
$fileHeader$
*/

/*! \file memory.h
    \brief Declaration of the class Memory.

*/

#if !defined(imebraMemory_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraMemory_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"
#include "dataHandler.h"

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

class IMEBRA_API Memory
{
    friend class MemoryStreamInput;
    friend class MemoryStreamOutput;

public:

    Memory();

    Memory(size_t initialSize);

    Memory(const char* buffer, size_t bufferSize);

#ifndef SWIG
    Memory(std::shared_ptr<implementation::memory> pMemory);
#endif

    void transfer(Memory& transferFrom);

    void copyFrom(const Memory& sourceMemory);

    void clear();

    void resize(size_t newSize);

    void reserve(size_t reserveSize);

    size_t size() const;

    char* data();

    const char* data() const;

    bool empty() const;

    void assign(const char* pSource, const size_t sourceLength);

protected:
#ifndef SWIG
    std::shared_ptr<implementation::memory> m_pMemory;
#endif
};

class IMEBRA_API MemoryPool
{
public:
    static void flush();
    static void setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize);
};

}

#endif // !defined(imebraImage_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
