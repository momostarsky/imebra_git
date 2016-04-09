/*
$fileHeader$
*/


#if !defined(imebraMemoryStreamInput__INCLUDED_)
#define imebraMemoryStreamInput__INCLUDED_

#include <string>
#include "baseStreamInput.h"
#include "definitions.h"

namespace imebra
{

class ReadMemory;
class ReadWriteMemory;

class IMEBRA_API MemoryStreamInput : public BaseStreamInput
{
    MemoryStreamInput(const MemoryStreamInput&) = delete;
    MemoryStreamInput& operator=(const MemoryStreamInput&) = delete;

public:
    MemoryStreamInput(const ReadMemory& memory);
    MemoryStreamInput(const ReadWriteMemory& memory);
};

}
#endif // !defined(imebraMemoryStreamInput__INCLUDED_)
