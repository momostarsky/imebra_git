/*
$fileHeader$
*/

/*! \file baseStream_swig.h
    \brief Declaration of the the base class for the streams (memory, file, ...)
			for SWIG.
*/

#if !defined(imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

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
/// \brief This class represents an input stream, a source
///        of data from which the DICOM or the Jpeg
///        decoders read the DICOM or the Jpeg file.
///
/// Specialized classes derived from this class can
///  read from files stored on the computer's disks,
///  on the network or in memory.
///
/// The application can read from the stream by using the
///  StreamReader class.
///
/// While this class can be used across several threads,
///  the StreamReader can be used only in one thread.
/// Several StreamReader objects can use a BaseStreamInput
///  object at the same time.
///
/// The library supplies the specialized derived
///  class FileStreamInput, used to read from physical
///  files.
///
///////////////////////////////////////////////////////////
class IMEBRA_API BaseStreamInput
{

#ifndef SWIG
	friend class StreamReader;
protected:
    BaseStreamInput(std::shared_ptr<implementation::baseStreamInput> pStream);
#endif

public:
    BaseStreamInput();
    BaseStreamInput(const BaseStreamInput& right);
    BaseStreamInput& operator=(const BaseStreamInput& right);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::baseStreamInput> m_pStream;
#endif
};


///
/// \brief This class represents an output stream, a
///        data sink into which the DICOM or the Jpeg
///        encoders write the DICOM or the Jpeg file.
///
/// Specialized classes derived from this class can
///  write into files on the computer's disks, on the
///   network or in memory.
///
/// The application can write into the stream by using the
///  StreamWriter class.
///
/// While this class can be used across several threads,
///  the StreamWriter can be used only in one thread.
/// Several StreamWriter objects can use a BaseStreamOutput
///  object at the same time.
///
/// The library supplies the specialized derived
///  class FileStreamOutput, used to write into physical
///  files.
///
///////////////////////////////////////////////////////////
class IMEBRA_API BaseStreamOutput
{

#ifndef SWIG
    friend class StreamWriter;
protected:
    BaseStreamOutput(std::shared_ptr<implementation::baseStreamOutput> pStream);
#endif

public:
    BaseStreamOutput();
    BaseStreamOutput(const BaseStreamOutput& right);
    BaseStreamOutput& operator=(const BaseStreamOutput& right);

#ifndef SWIG
protected:
    std::shared_ptr<implementation::baseStreamOutput> m_pStream;
#endif
};

}

#endif // !defined(imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
