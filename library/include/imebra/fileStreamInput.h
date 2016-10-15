/*
$fileHeader$
*/

/*! \file fileStreamInput.h
    \brief Declaration of the FileStreamInput class.

*/

#if !defined(imebraFileStreamInput__INCLUDED_)
#define imebraFileStreamInput__INCLUDED_

#include <string>
#include "baseStreamInput.h"
#include "definitions.h"

namespace imebra
{

///
/// \brief Represents an input file stream.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API FileStreamInput : public BaseStreamInput
{
    FileStreamInput(const FileStreamInput&) = delete;
    FileStreamInput& operator=(const FileStreamInput&) = delete;

public:
    /// \brief Constructor.
    ///
    /// \param name the path to the file to open in read mode
    ///
    ///////////////////////////////////////////////////////////////////////////////
#ifndef SWIG // Use only UTF-8 strings with SWIG
    FileStreamInput(const std::wstring& name);
#endif

    /// \brief Constructor.
    ///
    /// \param name the path to the file to open in read mode, in encoded in UTF8
    ///
    ///////////////////////////////////////////////////////////////////////////////
    FileStreamInput(const std::string& name);


    /// \brief Destructor. Closes the file.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ~FileStreamInput();
};

}
#endif // !defined(imebraFileStreamInput__INCLUDED_)
