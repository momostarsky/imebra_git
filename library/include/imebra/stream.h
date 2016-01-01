/*
$fileHeader$
*/

/*! \file stream_swig.h
	\brief Declaration of the stream class for SWIG.

*/

#if !defined(imebraStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_


#include "baseStream.h"
#include "definitions.h"

namespace imebra
{

/// \addtogroup group_swig_bindings
/// @{
class IMEBRA_API FileStreamWriter : public BaseStreamWriter
{
public:
    FileStreamWriter();
    FileStreamWriter(const FileStreamWriter& right);
    FileStreamWriter& operator=(const FileStreamWriter& right);

    void openFile(const std::wstring& name);
    void openFile(const std::string& name);

	void close();
};

class IMEBRA_API FileStreamReader : public BaseStreamReader
{
public:
    FileStreamReader();
    FileStreamReader(const FileStreamReader& right);
    FileStreamReader& operator=(const FileStreamReader& right);

    void openFile(const std::wstring& name);
    void openFile(const std::string& name);

    void close();

};


///@}

}
#endif // !defined(imebraStream_SWIG_146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
