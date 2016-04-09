/*
$fileHeader$
*/


#if !defined(imebraMemoryStreamOutput__INCLUDED_)
#define imebraMemoryStreamOutput__INCLUDED_

#include <string>
#include "baseStreamOutput.h"
#include "definitions.h"

namespace imebra
{

class ReadWriteMemory;

class IMEBRA_API MemoryStreamOutput : public BaseStreamOutput
{
    MemoryStreamOutput(const MemoryStreamOutput&) = delete;
    MemoryStreamOutput& operator=(const MemoryStreamOutput&) = delete;

public:
    MemoryStreamOutput(const ReadWriteMemory& memory);
};

}
#endif // !defined(imebraMemoryStreamOutput__INCLUDED_)
