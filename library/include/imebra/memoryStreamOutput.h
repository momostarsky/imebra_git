/*
$fileHeader$
*/


#if !defined(imebraMemoryStreamOutput__INCLUDED_)
#define imebraMemoryStreamOutput__INCLUDED_

#include <string>
#include "baseStreamOutput.h"
#include "definitions.h"
#include "readWriteMemory.h"

namespace imebra
{

class IMEBRA_API MemoryStreamOutput : public BaseStreamOutput
{
public:
    MemoryStreamOutput(ReadWriteMemory& memory);
    MemoryStreamOutput(const MemoryStreamOutput& right);
    MemoryStreamOutput& operator=(const MemoryStreamOutput& right);
};

}
#endif // !defined(imebraMemoryStreamOutput__INCLUDED_)
