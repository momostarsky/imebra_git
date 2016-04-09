/*
$fileHeader$
*/

/*! \file fileStreamInput.h
    \brief Declaration of the file input stream class.

*/

#if !defined(imebraFileStreamInput__INCLUDED_)
#define imebraFileStreamInput__INCLUDED_

#include <string>
#include "baseStreamInput.h"
#include "definitions.h"

namespace imebra
{

class IMEBRA_API FileStreamInput : public BaseStreamInput
{
    FileStreamInput(const FileStreamInput&) = delete;
    FileStreamInput& operator=(const FileStreamInput&) = delete;
public:
    FileStreamInput();

    void openFile(const std::wstring& name);
    void openFile(const std::string& name);

    void close();

};

}
#endif // !defined(imebraFileStreamInput__INCLUDED_)
