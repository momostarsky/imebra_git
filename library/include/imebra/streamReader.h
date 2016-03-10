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
#include "baseStream.h"

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

class CodecFactory;

class IMEBRA_API StreamReader
{
#ifndef SWIG
    friend class CodecFactory;
    friend class TagContent;

private:
    StreamReader(std::shared_ptr<implementation::streamReader> pReader);
#endif

public:
    StreamReader(const BaseStreamInput& stream);

    StreamReader(const BaseStreamInput& stream, size_t virtualStart, size_t virtualLength);

    StreamReader(const StreamReader& right);

    virtual ~StreamReader();

    StreamReader& operator=(const StreamReader& right);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::streamReader> m_pReader;
#endif
};

}

#endif // !defined(imebraStreamReader__INCLUDED_)
