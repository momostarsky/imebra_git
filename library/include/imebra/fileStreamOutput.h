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

class IMEBRA_API FileStreamOutput : public BaseStreamOutput
{
public:
    FileStreamOutput();
    FileStreamOutput(const FileStreamOutput& right);
    FileStreamOutput& operator=(const FileStreamOutput& right);

    void openFile(const std::wstring& name);
    void openFile(const std::string& name);

	void close();
};

}
#endif // !defined(imebraFileStreamOutput__INCLUDED_)
