/*
$fileHeader$
*/

/*! \file fileStreamOutput.h
    \brief Declaration of the file output stream class.

*/

#if !defined(imebraFileStreamOutput__INCLUDED_)
#define imebraFileStreamOutput__INCLUDED_

#include <string>
#include "baseStreamOutput.h"
#include "definitions.h"

namespace imebra
{

///
/// \brief Represents an output file stream.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API FileStreamOutput : public BaseStreamOutput
{
    FileStreamOutput(const FileStreamOutput&) = delete;
    FileStreamOutput& operator=(const FileStreamOutput&) = delete;

public:
    /// \brief Constructor.
    ///
    /// \param name the path to the file to open in write mode
    ///
    ///////////////////////////////////////////////////////////////////////////////
    FileStreamOutput(const std::wstring& name);

#ifndef SWIG // Use Unicode strings only with SWIG

    /// \brief Constructor.
    ///
    /// \param name the path to the file to open in write mode
    ///
    ///////////////////////////////////////////////////////////////////////////////
    FileStreamOutput(const std::string& name);

#endif

    /// \brief Destructor. Closes the file
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ~FileStreamOutput();

};

}
#endif // !defined(imebraFileStreamOutput__INCLUDED_)
