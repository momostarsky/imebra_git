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
public:
    MemoryStreamOutput(const ReadWriteMemory& memory);
    MemoryStreamOutput(const MemoryStreamOutput& right);
    MemoryStreamOutput& operator=(const MemoryStreamOutput& right);
};

}
#endif // !defined(imebraMemoryStreamOutput__INCLUDED_)
