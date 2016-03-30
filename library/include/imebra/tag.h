/*
$fileHeader$
*/

/*! \file tag.h
    \brief Declaration of the class Tag.

*/

#if !defined(imebraTagContent__INCLUDED_)
#define imebraTagContent__INCLUDED_

#include <string>
#include <cstdint>
#include <memory>
#include <map>
#include "image.h"
#include "readingDataHandlerNumeric.h"
#include "writingDataHandlerNumeric.h"
#include "definitions.h"
#include "streamReader.h"
#include "streamWriter.h"
#include "dataSet.h"

#ifndef SWIG

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
/// \brief This class represents a DICOM tag.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API Tag
{

#ifndef SWIG
    friend class DataSet;
private:
    Tag(std::shared_ptr<imebra::implementation::data> pData);
#endif


public:
    /// \brief Construct an empty dicom tag.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    Tag(tagVR_t tagVR);

    /// \brief Copy constructor: build a Tag object referencing the same Tag
    ///        implementation object as the source one.
    ///
    /// \param right another Tag object to use as source
    ///
    ///////////////////////////////////////////////////////////////////////////////
    Tag(const Tag& right);

    virtual ~Tag();

    /// \brief Copy operator: references the same Tag object as the source one.
    ///
    /// \param right another Tag object to use as source
    /// \return a reference to this object
    ///
    ///////////////////////////////////////////////////////////////////////////////
    Tag& operator=(const Tag& right);

    /// \brief Returns the number of buffers in the tag.
    ///
    /// @return the number of buffers in the tag
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getBuffersCount() const;

    /// \brief Returns true if the specified buffer exists, otherwise it returns
    ///        false.
    ///
    /// @param bufferId the zero-based buffer's id the
    ///                 function has to check for
    /// @return true if the buffer exists, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    bool bufferExists(size_t bufferId) const;

    /// \brief Returns the size of a buffer, in bytes.
    ///
    /// If the buffer doesn't exist then throws MissingBufferError.
    ///
    /// @param bufferId the zero-based buffer's id the
    ///                 function has to check for
    /// @return the buffer's size in bytes
    ///
    ///////////////////////////////////////////////////////////////////////////////
    size_t getBufferSize(size_t bufferId) const;

    /// \brief Get a ReadingDataHandler for the specified buffer.
    ///
    /// \param bufferId the buffer to connect to the ReadingDataHandler object.
    ///                 The first buffer has an Id = 0
    /// \return a ReadingDataHandler object connected to the specified buffer
    ///         requested buffer.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    ReadingDataHandler getReadingDataHandler(size_t bufferId) const;

    WritingDataHandler getWritingDataHandler(size_t bufferId);

    ReadingDataHandlerNumeric getReadingDataHandlerNumeric(size_t bufferId) const;

    ReadingDataHandlerNumeric getReadingDataHandlerRaw(size_t bufferId) const;

    WritingDataHandlerNumeric getWritingDataHandlerNumeric(size_t bufferId);

    WritingDataHandlerNumeric getWritingDataHandlerRaw(size_t bufferId);

    /// \brief Get a streamReader connected to a buffer's data.
    ///
    /// @param bufferId   the id of the buffer for which the
    ///                    streamReader is required. This
    ///                    parameter is usually 0
    /// @return           the streamReader connected to the
    ///                    buffer's data.
    ///
    ///////////////////////////////////////////////////////////
    StreamReader getStreamReader(size_t bufferId);

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
    StreamWriter getStreamWriter(size_t bufferId);

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
    DataSet getSequenceItem(size_t dataSetId) const;

    bool sequenceItemExists(size_t dataSetId) const;

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
    void setSequenceItem(size_t dataSetId, const DataSet& dataSet);

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
    void appendSequenceItem(const DataSet& dataSet);

    /// \brief Get the tag's buffer type in Dicom format.
    ///
    /// A buffer's data type is composed by two uppercase
    ///  chars.
    ///
    /// @return the buffer's data type in Dicom format
    ///
    ///////////////////////////////////////////////////////////
    tagVR_t getDataType() const;

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::data> m_pData;
#endif
};

}

#endif // !defined(imebraTagContent__INCLUDED_)
