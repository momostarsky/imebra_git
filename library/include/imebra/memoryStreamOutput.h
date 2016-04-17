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

///
/// \brief An output stream that writes data into a memory region.
///
/// When new data is written into the memory then it is resized as necessary.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MemoryStreamOutput : public BaseStreamOutput
{
    MemoryStreamOutput(const MemoryStreamOutput&) = delete;
    MemoryStreamOutput& operator=(const MemoryStreamOutput&) = delete;

public:
    /// \brief Constructor.
    ///
    /// \param memory the memory region into which the stream will write the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MemoryStreamOutput(const ReadWriteMemory& memory);
};

}
#endif // !defined(imebraMemoryStreamOutput__INCLUDED_)
