/*
$fileHeader$
*/

/*! \file streamReader.h
    \brief Declaration of the the class used to read the streams.

*/

#if !defined(imebraStreamReader__INCLUDED_)
#define imebraStreamReader__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
class streamReader;
}

}

#endif


namespace imebra
{

class BaseStreamInput;

class CodecFactory;

class IMEBRA_API StreamReader
{
    StreamReader(const StreamReader&) = delete;
    StreamReader& operator=(const StreamReader&) = delete;

#ifndef SWIG
    friend class CodecFactory;
    friend class Tag;

private:
    StreamReader(std::shared_ptr<implementation::streamReader> pReader);
#endif

public:
    StreamReader(const BaseStreamInput& stream);

    StreamReader(const BaseStreamInput& stream, size_t virtualStart, size_t virtualLength);

    virtual ~StreamReader();

#ifndef SWIG
protected:
    std::shared_ptr<implementation::streamReader> m_pReader;
#endif
};

}

#endif // !defined(imebraStreamReader__INCLUDED_)
