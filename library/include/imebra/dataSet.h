/*
$fileHeader$
*/

/*! \file dataSet.h
    \brief Declaration of the DataSet class.

*/

#if !defined(imebraDataSet__INCLUDED_)
#define imebraDataSet__INCLUDED_

#include "definitions.h"
#include "tagId.h"

#ifndef SWIG

#include <string>
#include <cstdint>
#include <memory>
#include "image.h"
#include "readingDataHandlerNumeric.h"
#include "writingDataHandlerNumeric.h"
#include "tagContent.h"

namespace imebra
{
namespace implementation
{
class dataSet;
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
class IMEBRA_API DataSet
{
#ifndef SWIG
    friend class DicomDirEntry;
	friend class DicomDir;
    friend class ModalityVOILUT;
    friend class VOILUT;
    friend class CodecFactory;
    friend class TagContent;

private:
    DataSet(std::shared_ptr<imebra::implementation::dataSet> pDataSet);
#endif
public:
    ///
    /// \brief Construct an empty dicom dataset.
    ///
    ///////////////////////////////////////////////////////////
	DataSet();

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
    DataSet(const DataSet& right);

    virtual ~DataSet();

	DataSet& operator=(const DataSet& right);

    groups_t getGroups() const;

    size_t getGroupsNumber(std::uint16_t groupId) const;

    tags_t getGroupTags(std::uint16_t groupId, size_t groupOrder) const;

    ///
    /// \brief Retrieve an image from the dataset.
    ///
    /// Images should be retrieved in order (first frame 0,
    ///  then frame 1, then frame 2 and so on).
    /// Images can be retrieved also in random order but this
    ///  introduces performance penalties.
    ///
    /// Throws dataSetImageDoesntExist if the requested frame
    ///  does not exist.
    ///
    /// \note Images retrieved from the dataset should be
    ///       processed by the ModalityVOILUT transform,
    ///       which converts the modality-specific pixel
    ///       values to values that the application can
    ///       understand. Consider using
    ///       getImageApplyModalityTransform() to retrieve
    ///       the image already processed by ModalityVOILUT.
    ///
    /// \param frameNumber the frame to retrieve (the first
    ///                    frame is 0)
    /// \return an image object containing the decompressed
    ///         image
    ///
    ///////////////////////////////////////////////////////////
    Image getImage(size_t frameNumber);

    ///
    /// \brief Retrieve an image from the dataset and if
    ///        necessary process it with ModalityVOILUT before
    ///        returning it.
    ///
    /// Images should be retrieved in order (first frame 0,
    ///  then frame 1, then frame 2 and so on).
    /// Images can be retrieved also in random order but this
    ///  introduces performance penalties.
    ///
    /// Throws dataSetImageDoesntExist if the requested frame
    ///  does not exist.
    ///
    /// \param frameNumber the frame to retrieve (the first
    ///                    frame is 0)
    /// \return an image object containing the decompressed
    ///         image, processed with ModalityVOILUT
    ///
    ///////////////////////////////////////////////////////////
    Image getImageApplyModalityTransform(size_t frameNumber);

    ///
    /// \brief Insert an image into the dataset.
    ///
    /// In multi-frame datasets the images must be inserted
    ///  in order: first insert the frame 0, then the frame 1,
    ///  then the frame 2 and so on.
    ///
    /// All the inserted images must have the same transfer
    ///  syntax and the same properties (size, color space,
    ///  high bit, bits allocated).
    ///
    /// If the images are inserted in the wrong order then the
    ///  dataSetExceptionWrongFrame exception is thrown.
    ///
    /// If the image being inserted has different properties
    ///  than the ones of the images already in the dataset
    ///  then the exception dataSetExceptionDifferentFormat
    ///  is thrown.
    ///
    /// \param frameNumber    the frame number (the first
    ///                        frame is 0)
    /// \param image          the object containing the image
    /// \param transferSyntax the transfer syntax. This
    ///                        influence also the format used
    ///                        to store the entire dataset
    /// \param quality        the quality to use for lossy
    ///                       compression. Ignored if lossless
    ///                       compression is used
    ///
    ///////////////////////////////////////////////////////////
    void setImage(size_t frameNumber, Image image, const std::string& transferSyntax, imageQuality_t quality);

    DataSet getSequenceItemThrow(const TagId& tagId, size_t itemId);

    ReadingDataHandler getReadingDataHandlerThrow(const TagId& tagId, size_t bufferId) const;

    WritingDataHandler getWritingDataHandler(const TagId& tagId, size_t bufferId, const std::string& defaultDataType = "");

    ReadingDataHandlerNumeric getReadingDataHandlerNumericThrow(const TagId& tagId, size_t bufferId) const;

    WritingDataHandlerNumeric getWritingDataHandlerNumeric(const TagId& tagId, size_t bufferId, const std::string& defaultDataType = "");

    bool bufferExists(const TagId& tagId, size_t bufferId);

    std::int32_t getSignedLongThrow(const TagId& tagId, size_t bufferId, size_t elementNumber) const;

    std::int32_t getSignedLong(const TagId& tagId, size_t bufferId, size_t elementNumber, std::int32_t defaultValue) const;

    void setSignedLong(const TagId& tagId, size_t bufferId, std::int32_t newValue, const std::string& defaultType = "");

    std::uint32_t getUnsignedLongThrow(const TagId& tagId, size_t bufferId, size_t elementNumber) const;

    std::uint32_t getUnsignedLong(const TagId& tagId, size_t bufferId, size_t elementNumber, std::uint32_t defaultValue) const;

    void setUnsignedLong(const TagId& tagId, size_t bufferId, std::uint32_t newValue, const std::string& defaultType = "");

    double getDoubleThrow(const TagId& tagId, size_t bufferId, size_t elementNumber) const;

    double getDouble(const TagId& tagId, size_t bufferId, size_t elementNumber, double defaultValue) const;

    void setDouble(const TagId& tagId, size_t bufferId, double newValue, const std::string& defaultType = "");

    std::string getStringThrow(const TagId& tagId, size_t bufferId, size_t elementNumber) const;

    std::string getString(const TagId& tagId, size_t bufferId, size_t elementNumber, const std::string& defaultValue) const;

    std::wstring getUnicodeStringThrow(const TagId& tagId, size_t bufferId, size_t elementNumber) const;

    std::wstring getUnicodeString(const TagId& tagId, size_t bufferId, size_t elementNumber, const std::wstring& defaultValue) const;

    void setString(const TagId& tagId, size_t bufferId, const std::string& newString, const std::string& defaultType = "");

    void setUnicodeString(const TagId& tagId, size_t bufferId, const std::wstring& newString, const std::string& defaultType = "");

    void setAge(const TagId& tagId, size_t bufferId, const Age& age, const std::string& defaultType = "");

    Age getAgeThrow(const TagId& tagId, size_t bufferId, size_t elementNumber) const;

    Age getAge(const TagId& tagId, size_t bufferId, size_t elementNumber, const Age& defaultValue) const;

    void setDate(const TagId& tagId, size_t bufferId, const Date& date, const std::string& defaultType = "");

    Date getDateThrow(const TagId& tagId, size_t bufferId, size_t elementNumber) const;

    Date getDate(const TagId& tagId, size_t bufferId, size_t elementNumber, const Date& defaultValue) const;

    size_t getRawDataThrow(const TagId& tagId, size_t bufferId, char* buffer, size_t bufferSize) const;

    void setRawData(const TagId& tagId, size_t bufferId, char* buffer, size_t bufferSize, const std::string& defaultType = "");

    std::string getDataTypeThrow(const TagId& tagId) const;

#ifndef SWIG
protected:
    std::shared_ptr<imebra::implementation::dataSet> m_pDataSet;
#endif
};

}

#endif // !defined(imebraDataSet__INCLUDED_)
