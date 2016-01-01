/*
$fileHeader$
*/

/*! \file data.h
    \brief Declaration of class used to store a single tag.

*/

#if !defined(imebraData_20A41D11_C650_410b_B3AA_CD5B3FF63222__INCLUDED_)
#define imebraData_20A41D11_C650_410b_B3AA_CD5B3FF63222__INCLUDED_

#include <memory>

#include "charsetsListImpl.h"
#include "dataHandlerNumericImpl.h"

#include <map>
#include <vector>


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{
	class streamReader;
	class streamWriter;

namespace imebra
{

class buffer;
class dataSet;


/// \addtogroup group_dataset
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Represents a single Dicom Tag.
///
/// Dicom tags are stored into a dataSet object.
/// Each tag can be referred by its group ID and tag ID.
///
/// The class data uses the buffer objects to store its
///  %data.
///
/// Each tag can have several buffers (tags defined as
///  sequence in the dicom stream).
///
/// Your application can access to the tag's buffers
///  using a data handler (call getDataHandler()).
/// 
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class data
{
public:
	///////////////////////////////////////////////////////////
	/// \name Data handlers
	///
	/// Retrieve dataHandler, dataHandlerRaw or a baseStream
	///  that allow to read or modify the buffer's data
	///
	///////////////////////////////////////////////////////////
	//@{

	/// \brief Returns the number of buffers in the tag.
	///
	/// @return the number of buffers in the tag
	///
	///////////////////////////////////////////////////////////
	std::uint32_t getBuffersCount();

	/// \brief Returns true if the specified buffer exists,
	///         otherwise it returns false.
	///
	/// The buffer can be created by requesting a writing
	///  handler (see handlers::dataHandler).
	///
	/// @param bufferId the zero-based buffer's id the 
	///                 function has to check for
	/// @return true if the buffer exists, false otherwise
	///
	///////////////////////////////////////////////////////////
	bool bufferExists(std::uint32_t bufferId);

	/// \brief Returns the size of a buffer, in bytes.
	///
	/// If the buffer doesn't exist then returns 0.
	/// See buffer::getBufferSizeBytes() for more info.
	///
	/// @param bufferId the zero-based buffer's id the 
	///                 function has to check for
	/// @return the buffer's size in bytes, or 0 if the buffer
	///          doesn't exist.
	///
	///////////////////////////////////////////////////////////
	std::uint32_t getBufferSize(std::uint32_t bufferId);

	/// \brief Get a data handler for the specified buffer.
	///
	/// handlers::dataHandler can be used to read, write 
	///  and resize the buffer.
	///
	/// handlers::dataHandler manages data types depending 
	///  on the buffer's data type: if your application
	///  has to work directly on the buffer's bytes,
	///  then it should obtain a handlers::dataHandlerRaw by
	///  calling getDataHandlerRaw().
	///
	/// Usually a tag has only one buffer (bufferId = 0), 
	///  but when a tag is a sequence or has an undefined
	///  length, then it could store more than one buffer;
	/// in this case your application has to specify the
	///  id of the buffer for which the handlers::dataHandler
	///  is requested.
	///
	/// The application can also specify a data type to use
	///  when a buffer doesn't exist yet: in this case a buffer
	///  with the specified data type will be allocated.
	///
	/// The returned handlers::dataHandler works on a local 
	///  copy of the buffer's data, then it doesn't have to 
	///  worry about multithreading accesses to the buffer's
	///  data.
	///
	/// @param bufferId the zero-based buffer's id the data
	///                 handler must use.
	/// @param bWrite   true if the application wants to write
	///                 something into the buffer
	/// @param defaultType a string that specifies the data
	///                  type to use for the new buffers.
	/// @return a pointer to the data handler for the
	///         requested buffer.
	///
	///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::readingDataHandler> getReadingDataHandler(std::uint32_t bufferId) const;

    std::shared_ptr<handlers::writingDataHandler> getWritingDataHandler(std::uint32_t bufferId, const std::string& defaultType, const charsetsList::tCharsetsList& defaultCharsets);
	
	/// \brief Get a raw data handler 
	///         (handlers::dataHandlerRaw) for the specified 
	///         buffer.
	///
	/// The raw data handler can be used to read, write and
	///  resize the buffer.
	///
	/// A raw data handler (handlers::dataHandlerRaw) always 
	///  works on a collection of bytes, no matter what the 
	///  buffer's data type is, while the normal 
	///  handlers::dataHandler works on data types depending 
	///  on the buffer's data type.
	///  
	/// A handlers::dataHandler can be obtained by calling
	///  getDataHandler().
	///
	/// Usually a tag has only one buffer (bufferId = 0), 
	///  but when a tag is a sequence or has an undefined
	///  length, then it could store more than one buffer;
	/// in this case your application has to specify the
	///  id of the buffer for which the data handler is
	///  requested.
	///
	/// The application can also specify a data type to use
	///  when a buffer doesn't exist yet: in this case a buffer
	///  with the specified data type will be allocated.
	///
	/// The returned handlers::dataHandlerRaw works on a local 
	///  copy of the buffer's data, then it doesn't have to 
	///  worry about multithreading accesses to the buffer's
	///  data.
	///
	/// @param bufferId the zero-based buffer's id the data
	///                 handler must use.
	/// @param bWrite   true if the application wants to write
	///                 something into the buffer
	/// @param defaultType a string that specifies the data
	///                  type to use for the new buffers.
	/// @return a pointer to the data handler for the
	///         requested buffer.
	///
	///////////////////////////////////////////////////////////
    std::shared_ptr<handlers::readingDataHandlerRaw> getReadingDataHandlerRaw(std::uint32_t bufferId) const;

    std::shared_ptr<handlers::writingDataHandlerRaw> getWritingDataHandlerRaw(std::uint32_t bufferId, const std::string& defaultType, const charsetsList::tCharsetsList& defaultCharsets);

	/// \brief Get a streamReader connected to a buffer's data.
	///
	/// @param bufferId   the id of the buffer for which the
	///                    streamReader is required. This 
	///                    parameter is usually 0
	/// @return           the streamReader connected to the 
	///                    buffer's data.
	///
	///////////////////////////////////////////////////////////
	std::shared_ptr<streamReader> getStreamReader(std::uint32_t bufferId);

	/// \brief Get a streamWriter connected to a buffer's data.
	///
	/// @param bufferId   the id of the buffer for which the
	///                    streamWriter is required. This 
	///                    parameter is usually 0
	/// @param dataType   the datatype used to create the 
	///                    buffer if it doesn't exist already
	/// @return           the streamWriter connected to the 
	///                    emptied buffer's data.
	///
	///////////////////////////////////////////////////////////
    std::shared_ptr<streamWriter> getStreamWriter(std::uint32_t bufferId, const std::string& dataType = "");

	//@}


	///////////////////////////////////////////////////////////
	/// \name Embedded data sets.
	///
	/// Get or set an embedded dataSet
	///
	///////////////////////////////////////////////////////////
	//@{

	/// \brief Retrieve an embedded data set.
	///
	/// Sequence tags (dicom type=SQ) store embedded dicom 
	///  structures inside.
	///
	/// Sequences allow to nest several dicom structures.
	/// Sequences are used by dicom directories and by some
	///  tags in the normal dataSet.
	///
	/// @param dataSetId  the ID of the dataSet to retrieve.
	///                   Several data sets can be embedded
	///                   in the tag.
	///                   The first dataSet's ID is zero.
	/// @return           a pointer to the retrieved dataSet
	///
	///////////////////////////////////////////////////////////
	std::shared_ptr<dataSet> getDataSet(std::uint32_t dataSetId);

	/// \brief Set an embedded dataSet to the sequence.
	///
	/// Several data sets can be nested one inside each other.
	/// When a data set is embedded into a tag, then the
	///  tag will have a sequence type (dicom type=SQ).
	///
	/// Sequences are used to build dicom directories and
	///  other tags in normal data sets.
	///
	/// @param dataSetId  The Id of the dataSet inside the tag.
	///                   Tags can store several data sets.
	///                   The first dataSet has an ID of zero
	/// @param pDataSet   A pointer to the dataSet to store
	///                   into the tag
	///
	///////////////////////////////////////////////////////////
	void setDataSet(std::uint32_t dataSetId, std::shared_ptr<dataSet> pDataSet);

	/// \brief Append an embedded dataSet to the sequence.
	///
	/// Several data sets can be nested one inside each other.
	/// When a data set is embedded into a tag, then the
	///  tag will have a sequence type (dicom type=SQ).
	///
	/// Sequences are used to build dicom directories and
	///  other tags in normal data sets.
	///
	/// @param pDataSet   A pointer to the dataSet to store
	///                   into the tag
	///
	///////////////////////////////////////////////////////////
	void appendDataSet(std::shared_ptr<dataSet> pDataSet);
	
	//@}


	///////////////////////////////////////////////////////////
	/// \name Buffer deletion
	///
	///////////////////////////////////////////////////////////
	//@{

	/// \brief Remove a buffer from the tag.
	///
	/// @param bufferId  the id of the buffer to be removed
	///                   from the tag
	///
	///////////////////////////////////////////////////////////
	void deleteBuffer(std::uint32_t bufferId);

	//@}


	///////////////////////////////////////////////////////////
	/// \name Buffer's data type
	///
	///////////////////////////////////////////////////////////
	//@{

	/// \brief Get the tag's buffer type in Dicom format.
	///
	/// A buffer's data type is composed by two uppercase
	///  chars.
	///
	/// @return the buffer's data type in Dicom format
	///
	///////////////////////////////////////////////////////////
	std::string getDataType();

	//@}

    virtual void setCharsetsList(const charsetsList::tCharsetsList& charsetsList);
    virtual void getCharsetsList(charsetsList::tCharsetsList* pCharsetsList) const;

	// Set a buffer
	///////////////////////////////////////////////////////////
	void setBuffer(std::uint32_t bufferId, const std::shared_ptr<buffer>& newBuffer);

protected:
	// Pointers to the internal buffers
	///////////////////////////////////////////////////////////
	typedef std::map<std::uint32_t, std::shared_ptr<buffer> > tBuffersMap;
	tBuffersMap m_buffers;

	// Pointers to the embedded datasets
	///////////////////////////////////////////////////////////
	typedef std::shared_ptr<dataSet> ptrDataSet;
	typedef std::vector<ptrDataSet> tEmbeddedDatasetsMap;
	tEmbeddedDatasetsMap m_embeddedDataSets;
};

/// @}

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraData_20A41D11_C650_410b_B3AA_CD5B3FF63222__INCLUDED_)
