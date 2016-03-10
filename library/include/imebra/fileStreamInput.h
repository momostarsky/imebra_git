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
public:
    FileStreamInput();
    FileStreamInput(const FileStreamInput& right);
    FileStreamInput& operator=(const FileStreamInput& right);

    void openFile(const std::wstring& name);
    void openFile(const std::string& name);

    void close();

};

}
#endif // !defined(imebraFileStreamInput__INCLUDED_)
