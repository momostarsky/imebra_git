/*
$fileHeader$
*/

/*! \file memoryPool.h
    \brief Declaration of the class MemoryPool.

*/

#if !defined(imebraMemoryPool__INCLUDED_)
#define imebraMemoryPool__INCLUDED_

#ifndef SWIG

#include <memory>
#include <string>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
class memoryPool;
}
}
#endif

namespace imebra
{

class IMEBRA_API MemoryPool
{
public:
    static void flush();
    static void setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize);
};

}

#endif // !defined(imebraMemoryPool__INCLUDED_)
