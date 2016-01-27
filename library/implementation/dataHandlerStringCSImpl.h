/*
$fileHeader$
*/

/*! \file dataHandlerStringCS.h
    \brief Declaration of the class dataHandlerStringCS.

*/

#if !defined(imebraDataHandlerStringCS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringCS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

namespace handlers
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Handles the Dicom data type "CS" (code string)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringCS : public readingDataHandlerString
{
public:
    readingDataHandlerStringCS(const memory& parseMemory);

};

class writingDataHandlerStringCS: public writingDataHandlerString
{
public:
    writingDataHandlerStringCS(const std::shared_ptr<buffer> pBuffer);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringCS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
