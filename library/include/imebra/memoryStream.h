/*
$fileHeader$
*/


#if !defined(imebraMemoryStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraMemoryStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#include <string>
#include "baseStream.h"
#include "definitions.h"
#include "memory.h"

namespace imebra
{

class IMEBRA_API MemoryStreamInput : public BaseStreamInput
{
public:
    MemoryStreamInput(const Memory& memory);
    MemoryStreamInput(const MemoryStreamInput& right);
    MemoryStreamInput& operator=(const MemoryStreamInput& right);
};

class IMEBRA_API MemoryStreamOutput : public BaseStreamOutput
{
public:
    MemoryStreamOutput(Memory& memory);
    MemoryStreamOutput(const MemoryStreamOutput& right);
    MemoryStreamOutput& operator=(const MemoryStreamOutput& right);
};

}
#endif // !defined(imebraMemoryStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
