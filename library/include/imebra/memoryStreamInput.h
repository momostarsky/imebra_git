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

///
/// \brief An input stream that reads data from a memory region.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API MemoryStreamInput : public BaseStreamInput
{
    MemoryStreamInput(const MemoryStreamInput&) = delete;
    MemoryStreamInput& operator=(const MemoryStreamInput&) = delete;

public:
    /// \brief Constructor.
    ///
    /// \param memory the memory region from which the stream will read the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MemoryStreamInput(const ReadMemory& memory);

    /// \brief Constructor.
    ///
    /// \param memory the memory region from which the stream will read the data
    ///
    ///////////////////////////////////////////////////////////////////////////////
    MemoryStreamInput(const ReadWriteMemory& memory);
};

}
#endif // !defined(imebraMemoryStreamInput__INCLUDED_)
