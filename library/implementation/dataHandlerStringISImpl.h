/*
$fileHeader$
*/

/*! \file dataHandlerStringIS.h
    \brief Declaration of the class dataHandlerStringIS.

*/

#if !defined(imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

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
/// \brief Handles the Dicom type "IS" (integer string)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringIS : public readingDataHandlerString
{
public:
    readingDataHandlerStringIS(const memory& parseMemory);

	// Overwritten to use getSignedLong()
	///////////////////////////////////////////////////////////
	virtual double getDouble(const size_t index) const;

};

class writingDataHandlerStringIS: public writingDataHandlerString
{
public:
    writingDataHandlerStringIS(const std::shared_ptr<buffer> pBuffer);

    // Overwritten to use setSignedLong()
    ///////////////////////////////////////////////////////////
    virtual void setDouble(const size_t index, const double value);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringIS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
