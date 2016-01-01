/*
$fileHeader$
*/

/*! \file dataHandlerStringDS.h
    \brief Declaration of the class dataHandlerStringDS.

*/

#if !defined(imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringImpl.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Handles the Dicom type "DS" (decimal string)
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringDS : public readingDataHandlerString
{
public:
    readingDataHandlerStringDS(const memory& memory);

	// Overwritten to use getDouble()
	///////////////////////////////////////////////////////////
	virtual std::int32_t getSignedLong(const size_t index) const;

	// Overwritten to use getDouble()
	///////////////////////////////////////////////////////////
	virtual std::uint32_t getUnsignedLong(const size_t index) const;

};

class writingDataHandlerStringDS: public writingDataHandlerString
{
public:
    writingDataHandlerStringDS(const std::shared_ptr<buffer> pBuffer);

    // Overwritten to use setDouble()
    ///////////////////////////////////////////////////////////
    virtual void setSignedLong(const size_t index, const std::int32_t value);

    // Overwritten to use setDouble()
    ///////////////////////////////////////////////////////////
    virtual void setUnsignedLong(const size_t index, const std::uint32_t value);
};

} // namespace handlers

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraDataHandlerStringDS_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
