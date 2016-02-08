/*
$fileHeader$
*/

/*! \file streamReader_swig.h
	\brief Declaration of the the class used to read the streams for SWIG.

*/

#if !defined(imebraStreamReader_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
#define imebraStreamReader_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_

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
    friend class CodecFactory;
public:
#ifndef SWIG
    StreamReader(std::shared_ptr<implementation::streamReader> pReader);
#endif
    StreamReader(const BaseStreamInput& stream);

    StreamReader(const BaseStreamInput& stream, size_t virtualStart, size_t virtualLength);

    StreamReader(const StreamReader& right);

    StreamReader& operator=(const StreamReader& right);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::streamReader> m_pReader;
#endif
};

}

#endif // !defined(imebraStreamReader_SWIG_F6221390_BC44_4B83_B5BB_3485222FF1DD__INCLUDED_)
