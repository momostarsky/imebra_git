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
#ifndef SWIG // Use only UTF-8 strings with SWIG
    FileStreamOutput(const std::wstring& name);
#endif

    /// \brief Constructor.
    ///
    /// \param name the path to the file to open in write mode
    ///
    ///////////////////////////////////////////////////////////////////////////////
    FileStreamOutput(const std::string& name);


    /// \brief Destructor. Closes the file
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ~FileStreamOutput();

};

}
#endif // !defined(imebraFileStreamOutput__INCLUDED_)
