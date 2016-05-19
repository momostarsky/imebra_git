/*
$fileHeader$
*/

/*! \file tag.h
    \brief Declaration of the class Tag.

*/

#if !defined(imebraLut__INCLUDED_)
#define imebraLut__INCLUDED_

#include <string>
#include <cstdint>
#include "readingDataHandlerNumeric.h"
#include "definitions.h"

#ifndef SWIG

namespace imebra
{
namespace implementation
{
class lut;
}
}

#endif

namespace imebra
{

///
/// \brief This class represents Lookup Table.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API LUT
{
    LUT(const LUT&) = delete;
    LUT& operator=(const LUT&) = delete;

#ifndef SWIG
    friend class DataSet;
    friend class VOILUT;
private:
    LUT(std::shared_ptr<imebra::implementation::lut> pLut);
#endif

public:
    /// \brief Initializes the lut with the values stored in the data handlers
    ///        retrieved from a dataset.
    ///
    /// @param pDescriptor   the handler referencing the lut descriptor (size,
    ///                       first mapped value and number of bits)
    /// @param pData         the handler referencing the lut data
    /// @param description   a string that describes the lut
    ///
    ///////////////////////////////////////////////////////////////////////////////
    LUT(ReadingDataHandlerNumeric& descriptor, ReadingDataHandlerNumeric& data, const std::wstring& description, bool pixelRepresentation);

    virtual ~LUT();

    /// \brief Returns the LUT's description.
    ///
    /// \return the LUT's description
    ///
    ///////////////////////////////////////////////////////////////////////////////
    std::wstring getDescription();

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::lut> m_pLut;
#endif
};

}

#endif // !defined(imebraLut__INCLUDED_)
