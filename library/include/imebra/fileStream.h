/*
$fileHeader$
*/

/*! \file fileStream.h
    \brief Declaration of the file tream classes.

*/

#if !defined(imebraFileStream__INCLUDED_)
#define imebraFileStream__INCLUDED_

#include <string>
#include "baseStream.h"
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
#endif // !defined(imebraFileStream__INCLUDED_)
