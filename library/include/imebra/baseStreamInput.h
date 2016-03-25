/*
$fileHeader$
*/

/*! \file baseStreamInput.h
    \brief Declaration of the the base stream class BaseStreamInput.
*/

#if !defined(imebraBaseStreamInput__INCLUDED_)
#define imebraBaseStreamInput__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
    class baseStreamInput;
}
}

#endif

namespace imebra
{

///
/// \brief This class represents a generic input stream.
///
/// Specialized classes derived from this one can read data from files stored
/// on the computer's disks (FileStreamInput) or from memory
/// (MemoryStreamInput).
///
/// The client application cannot read the data directly from a
/// BaseStreamInput but must use a StreamReader. Several StreamReader objects
/// can read data from the same BaseStreamInput object.
///
/// The StreamReader class is not thread-safe, but different StreamReader
/// objects in different threads can access the same BaseStreamInput object.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API BaseStreamInput
{

#ifndef SWIG
	friend class StreamReader;
    friend class FileStreamInput;
    friend class MemoryStreamInput;

private:
    /// \brief Construct a BaseStreamInput object from an implementation object.
    ///
    /// \param pStream the implementation of BaseStreamInput
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamInput(std::shared_ptr<implementation::baseStreamInput> pStream);
#endif

public:
    /// \brief Copy constructor: build an input stream object referencing the
    ///        same stream object as the source one.
    ///
    /// \param right another BaseStreamInput object to use as source
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamInput(const BaseStreamInput& right);

    /// \brief Destructor.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~BaseStreamInput();

    /// \brief Copy operator: references the same input stream object as the
    ///        source one.
    ///
    /// \param right another BaseStreamInput object to use as source
    /// \return a reference to this object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamInput& operator=(const BaseStreamInput& right);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::baseStreamInput> m_pStream;
#endif
};

}

#endif // !defined(imebraBaseStreamInput__INCLUDED_)
