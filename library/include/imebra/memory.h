/*
$fileHeader$
*/

/*! \file memory_swig.h
    \brief Declaration of the Memory class for SWIG.

*/

#if !defined(imebraMemory_SWIG_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraMemory_SWIG_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#ifndef SWIG

#include "../../implementation/baseObjectImpl.h"

namespace puntoexe
{
class memory;
}
#endif

namespace imebra
{

class Memory
{
public:
	Memory();
    Memory(size_t requestedSize);

#ifndef SWIG
    Memory(puntoexe::ptr<puntoexe::memory> pMemory);
#endif

	void transfer(Memory& transferFrom);

	void copyFrom(Memory& copyFrom);

	void clear();

    void resize(size_t newSize);

    void reserve(size_t reserveSize);

    size_t size() const;

    std::uint8_t* data() const;

    size_t data(char* buffer, size_t bufferSize) const;

    void assign(char* buffer, size_t bufferSize);

    bool empty() const;

#ifndef SWIG
    puntoexe::ptr<puntoexe::memory> m_pMemory;
#endif
};

class MemoryPool
{
public:
    static void flush();
};

}

#endif // !defined(imebraMemory_SWIG_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
