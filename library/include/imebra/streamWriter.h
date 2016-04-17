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

///
/// \brief A StreamWriter is used to write data into a BaseStreamOutput
///        object.
///
/// A StreamWriter can be mapped to only a portion of the BaseStreamOutput it
/// manages.
///
/// \warning: The StreamWriter object IS NOT THREAD-SAFE: however, several
///           StreamWriter objects from different threads can be connected to
///           the same BaseStreamOutput object.
///
///////////////////////////////////////////////////////////////////////////////
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
    /// \brief Constructor.
    ///
    /// \param stream the BaseStreamOutput object on which the StreamWriter will
    ///               write
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamWriter(const BaseStreamOutput& stream);

    /// \brief Constructor.
    ///
    /// This version of the constructor limits the portion of the stream that
    /// the StreamWriter will be able to use.
    ///
    /// \param stream        the BaseStreamOutput object on which the StreamWriter
    ///                      will write
    /// \param virtualStart  the first visible byte of the managed stream
    /// \param virtualLength the number of visible bytes in the managed stream
    ///
    ///////////////////////////////////////////////////////////////////////////////
    StreamWriter(const BaseStreamOutput& stream, size_t virtualStart, size_t virtualLength);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::streamWriter> m_pWriter;
#endif
};

}

#endif // !defined(imebraStreamWriter__INCLUDED_)
