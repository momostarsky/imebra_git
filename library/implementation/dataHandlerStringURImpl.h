/*
$fileHeader$
*/

/*! \file dataHandlerStringUR.h
    \brief Declaration of the class dataHandlerStringUR.

*/

#if !defined(imebraDataHandlerStringUR_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringUR_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"
#include <map>
#include <string>


namespace imebra
{

namespace implementation
{

namespace handlers
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Handles the Dicom data type "UR" (universal
///         resource identifier)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringUR : public readingDataHandlerString
{
public:
    readingDataHandlerStringUR(const memory& parseMemory);
};

class writingDataHandlerStringUR: public writingDataHandlerString
{
public:
    writingDataHandlerStringUR(const std::shared_ptr<buffer>& pBuffer);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringUR_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
