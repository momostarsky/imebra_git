/*
$fileHeader$
*/

/*! \file tagContent.h
    \brief Declaration of the class TagContent.

*/

#if !defined(imebraTagContent__INCLUDED_)
#define imebraTagContent__INCLUDED_
#ifndef SWIG

#include <string>
#include <cstdint>
#include <memory>
#include <map>
#include "image.h"
#include "dataHandler.h"
#include "definitions.h"
#include "streamReader.h"
#include "streamWriter.h"

namespace imebra
{
namespace implementation
{
class data;
}
}

#endif

namespace imebra
{

///
///
/// This class represents a DICOM dataset.
///
///////////////////////////////////////////////////////////
class IMEBRA_API TagContent
{

#ifndef SWIG
    friend class DataSet;
private:
    TagContent(std::shared_ptr<imebra::implementation::data> pData);
#endif


public:
    ///
    /// \brief Construct an empty dicom dataset.
    ///
    ///////////////////////////////////////////////////////////
    TagContent();

    ///
    /// \brief Creates a dataset and shallow copies the data
    ///        from the dataset in the parameters
    /// \param right the dataset to copy from
    ///
    /// This dataset and the one in the parameter will refer
    ///  to the same data: changes made in one dataset will be
    ///  reflected in the other dataset.
    ///
    ///////////////////////////////////////////////////////////
    TagContent(const TagContent& right);

    virtual ~TagContent();

    TagContent& operator=(const TagContent& right);

    /// \brief Returns the number of buffers in the tag.
    ///
    /// @return the number of buffers in the tag
    ///
    ///////////////////////////////////////////////////////////
    size_t getBuffersCount() const;

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
    bool bufferExists(size_t bufferId) const;

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
    size_t getBufferSizeThrow(size_t bufferId) const;

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
    ReadingDataHandler getReadingDataHandlerThrow(size_t bufferId) const;

    WritingDataHandler getWritingDataHandler(size_t bufferId, const std::string& defaultType);

    ReadingDataHandlerNumeric getReadingDataHandlerNumericThrow(size_t bufferId) const;

    WritingDataHandlerNumeric getWritingDataHandlerNumeric(size_t bufferId, const std::string& defaultType);

    /// \brief Get a streamReader connected to a buffer's data.
    ///
    /// @param bufferId   the id of the buffer for which the
    ///                    streamReader is required. This
    ///                    parameter is usually 0
    /// @return           the streamReader connected to the
    ///                    buffer's data.
    ///
    ///////////////////////////////////////////////////////////
    StreamReader getStreamReaderThrow(size_t bufferId);

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
    StreamWriter getStreamWriter(size_t bufferId, const std::string& dataType = "");

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
    DataSet getSequenceItemThrow(size_t dataSetId) const;

    bool dataSetExists(size_t dataSetId) const;

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
    void setDataSet(size_t dataSetId, const DataSet& dataSet);

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
    void appendDataSet(const DataSet& dataSet);

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
    std::string getDataTypeThrow(size_t bufferId) const;

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::data> m_pData;
#endif
};

typedef std::map<std::uint16_t, TagContent> tags_t;

}

#endif // !defined(imebraTagContent__INCLUDED_)
