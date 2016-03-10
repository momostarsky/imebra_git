/*
$fileHeader$
*/

/*! \file baseStream.h
    \brief Declaration of the the base stream classes BaseStreamInput and BaseStreamOutput.
*/

#if !defined(imebraBaseStream__INCLUDED_)
#define imebraBaseStream__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace imebra
{
namespace implementation
{
    class baseStreamInput;
    class baseStreamOutput;
}
}

#endif

namespace imebra
{

///
/// \brief This class represents a generic input stream,
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
    /// \brief Construct an empty BaseStreamInput. The new object can be used only
    ///        after a valid stream object has been assigned to this one via
    ///        operator=().
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamInput();

    /// \brief Copy constructor: build an input stream object referencing the
    ///        same stream object as the source one.
    ///
    /// \param right another BaseStreamInput object to use as source
    ///
    ///////////////////////////////////////////////////////////////////////////////
    BaseStreamInput(const BaseStreamInput& right);

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

#endif // !defined(imebraBaseStream__INCLUDED_)
