/*
$fileHeader$
*/

/*! \file streamWriter.h
    \brief Declaration of the the class used to write the streams.

*/

#if !defined(imebraStreamWriter__INCLUDED_)
#define imebraStreamWriter__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
class streamWriter;
}
}
#endif

namespace imebra
{

class BaseStreamOutput;

class CodecFactory;

class IMEBRA_API StreamWriter
{
    StreamWriter(const StreamWriter&) = delete;
    StreamWriter& operator=(const StreamWriter&) = delete;

#ifndef SWIG
    friend class CodecFactory;
    friend class Tag;

private:
    StreamWriter(std::shared_ptr<implementation::streamWriter> pWriter);
#endif

public:
    StreamWriter(const BaseStreamOutput& stream, size_t virtualStart = 0, size_t virtualLength = 0);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::streamWriter> m_pWriter;
#endif
};

}

#endif // !defined(imebraStreamWriter__INCLUDED_)
