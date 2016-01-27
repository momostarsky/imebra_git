/*
$fileHeader$
*/

/*! \file waveform.h
    \brief Declaration of the class waveform.

*/

#if !defined(imebraWaveform_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraWaveform_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#include <memory>
#include "dataHandlerImpl.h"

///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

class dataSet;
namespace handlers
{
	class dataHandler;
}

/// \addtogroup group_waveform Waveforms
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Represents a single waveform of a dicom dataset. 
///
/// Waveforms are embedded into the dicom structures
///  (represented by the dataSet class), stored in sequence
///  items (one waveform per item).
///
/// Use dataSet::getWaveform() to retrieve a waveform from
///  a dataSet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class waveform
{
public:
	/// \brief Constructor. Initializes the class and connects
	///         it to the sequence item containing the waveform
	///         data.
	///
	/// @param pDataSet   the sequence item containing the
	///                    waveform. 
	///                   Use dataSet::getSequenceItem() to
	///                    retrieve the sequence item 
	///                    containing the waveform or
	///                    construct the class with
	///                    dataSet::getWaveform()
	///
	///////////////////////////////////////////////////////////
	waveform(std::shared_ptr<dataSet> pDataSet);

	/// \brief Retrieve the number of channels (tag 003A,0005).
	///
	/// @return the number of channels
	///
	///////////////////////////////////////////////////////////
    std::uint32_t getChannels() const;

	/// \brief Retrieve the number of samples per channel
	///         (tag 003A,0010).
	///
	/// @return the number of samples per channel
	///
	///////////////////////////////////////////////////////////
    std::uint32_t getSamples() const;

	/// \brief Retrieve the number of bit stored 
	///         (tag 003A,021A).
	///
	/// @return the number of bits stored
	///
	///////////////////////////////////////////////////////////
    std::uint32_t getBitsStored() const;

	/// \brief Retrieve the number of bit allocated
	///         (tag 5400,1004).
	///
	/// @return the number of bits allocated
	///
	///////////////////////////////////////////////////////////
    std::uint32_t getBitsAllocated() const;

	/// \brief Return the data interpretation string 
	///         (tag 5400,1006).
	///
	/// @return the interpretation string. Possible values are:
	/// - "SB": signed 8 bit linear
	/// - "UB": unsigned 8 bit linear
	/// - "MB": 8 bit u-law 
	/// - "AB": 8 bit a-law
	/// - "SS": signed 16 bit
	/// - "US": unsigned 16 bit
	///
	///////////////////////////////////////////////////////////
    std::string getInterpretation() const;

	/// \brief Retrieve the decompressed waveform data.
	///
	/// Retrieve the requested channel's data and decompress
	///  it into signed long values. 8 bits uLaw and aLaw data 
	///  are decompressed into normalized 16 bits values.
	///
	/// This function takes into account the value in the 
	///  interpretation tag and returns an handler to ready to
	///  use data.
	///
	/// @param channel      the channel for which the data is
	///                      required
	/// @param paddingValue the value that the function must
	///                      write in the returned data in
	///                      place of the original padding
	///                      value. Specify a number
	///                      outside the range -32768..65535
	/// @return a data handler attached to ready to use data.
	///        Use handlers::dataHandler->GetSignedLong() or 
	///        handlers::dataHandler->GetSignedLongIncPointer()
	///        to retrieve the data
	///
	///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::readingDataHandler> getIntegerData(std::uint32_t channel, std::int32_t paddingValue = 0x7fffffff);

	/// \brief Return the sequence item used by the waveform.
	///
	/// @return the sequence item used by the waveform
	///
	///////////////////////////////////////////////////////////
	std::shared_ptr<dataSet> GetWaveformItem();
	
private:
	std::shared_ptr<dataSet> m_pDataSet;
};

/// @}

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraWaveform_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
