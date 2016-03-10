/*
$fileHeader$
*/


#if !defined(imebraMemoryStream__INCLUDED_)
#define imebraMemoryStream__INCLUDED_

#include <string>
#include "baseStream.h"
#include "definitions.h"
#include "memory.h"

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

class IMEBRA_API MemoryStreamOutput : public BaseStreamOutput
{
public:
    MemoryStreamOutput(ReadWriteMemory& memory);
    MemoryStreamOutput(const MemoryStreamOutput& right);
    MemoryStreamOutput& operator=(const MemoryStreamOutput& right);
};

}
#endif // !defined(imebraMemoryStream__INCLUDED_)
