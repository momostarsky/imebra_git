/*
$fileHeader$
*/

/*! \file baseStreamOutput.h
    \brief Declaration of the the base stream class BaseStreamOutput.
*/

#if !defined(imebraBaseStreamOutput__INCLUDED_)
#define imebraBaseStreamOutput__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
    class baseStreamOutput;
}
}

#endif

namespace imebra
{

///
/// \brief This class represents a generic output stream.
///
/// Specialized classes derived from this one can write into files on the
/// computer's disks (FileStreamOutput) or to memory (MemoryStreamOutput).
///
/// The application can write into the stream by using a StreamWriter object.
///
/// While this class can be used across several threads, a StreamWriter can
/// be used only in one thread.
///
/// Several StreamWriter objects (also in different threads) can use the same
/// BaseStreamOutput object.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API BaseStreamOutput
{

#ifndef SWIG
    friend class StreamWriter;
    friend class FileStreamOutput;
    friend class MemoryStreamOutput;

private:
    /// \brief Construct a BaseStreamOutput object from an implementation object.
    ///
    /// \param pStream the implementation of BaseStreamOutput
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamOutput(std::shared_ptr<implementation::baseStreamOutput> pStream);
#endif

public:
    /// \brief Construct an empty BaseStreamOutput. The new object can be used only
    ///        after a valid stream object has been assigned to this one via
    ///        operator=().
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamOutput();

    /// \brief Copy constructor: build an output stream object referencing the
    ///        same stream implementation object as the source one.
    ///
    /// \param right another BaseStreamOutput object to use as source
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamOutput(const BaseStreamOutput& right);

    virtual ~BaseStreamOutput();

    /// \brief Copy operator: references the same output stream object as the
    ///        source one.
    ///
    /// \param right another BaseStreamOutput object to use as source
    /// \return a reference to this object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamOutput& operator=(const BaseStreamOutput& right);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::baseStreamOutput> m_pStream;
#endif
};

}

#endif // !defined(imebraBaseStreamOutput__INCLUDED_)
