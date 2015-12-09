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

class Memory
{
public:
	Memory();
	Memory(int requestedSize);

#ifndef SWIG
    Memory(puntoexe::ptr<puntoexe::memory> pMemory);
#endif

	void transfer(Memory& transferFrom);

	void copyFrom(Memory& copyFrom);

	void clear();

	void resize(int newSize);

	void reserve(int reserveSize);

	int size();

	size_t data(char* buffer, int bufferSize);

	void assign(char* buffer, int bufferSize);

	bool empty();

#ifndef SWIG
    puntoexe::ptr<puntoexe::memory> m_pMemory;
#endif
};

class MemoryPool
{
public:
    static void flush();
};


#endif // !defined(imebraMemory_SWIG_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
