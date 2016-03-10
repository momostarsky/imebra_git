/*
$fileHeader$
*/


#if !defined(imebraMemoryStreamInput__INCLUDED_)
#define imebraMemoryStreamInput__INCLUDED_

#include <string>
#include "baseStreamInput.h"
#include "definitions.h"
#include "readMemory.h"
#include "readWriteMemory.h"

namespace imebra
{

class IMEBRA_API MemoryStreamInput : public BaseStreamInput
{
public:
    MemoryStreamInput(const ReadMemory& memory);
    MemoryStreamInput(const ReadWriteMemory& memory);
    MemoryStreamInput(const MemoryStreamInput& right);
    MemoryStreamInput& operator=(const MemoryStreamInput& right);
};

}
#endif // !defined(imebraMemoryStreamInput__INCLUDED_)
