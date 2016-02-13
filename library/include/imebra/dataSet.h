/*
$fileHeader$
*/

/*! \file dataSet_swig.h
    \brief Declaration of the class dataSet for SWIG.

*/

#if !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
#define imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#ifndef SWIG

#include <string>
#include <cstdint>
#include <memory>
#include "image.h"
#include "dataHandler.h"
#include "definitions.h"
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
	friend class DirectoryRecord;
	friend class DicomDir;
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

	DataSet& operator=(const DataSet& right);

#ifndef SWIG
    DataSet(std::shared_ptr<imebra::implementation::dataSet> pDataSet);
#endif

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

    DataSet getSequenceItemThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t itemId);

    ReadingDataHandler getReadingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const;

    WritingDataHandler getWritingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& defaultDataType = "");

    bool bufferExists(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId);

    std::int32_t getSignedLongThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    std::int32_t getSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::int32_t defaultValue) const;

    void setSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, std::int32_t newValue, const std::string& defaultType = "");

    std::uint32_t getUnsignedLongThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    std::uint32_t getUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, std::uint32_t defaultValue) const;

    void setUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, std::uint32_t newValue, const std::string& defaultType = "");

    double getDoubleThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    double getDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, double defaultValue) const;

    void setDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, double newValue, const std::string& defaultType = "");

    std::string getStringThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    std::string getString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::string& defaultValue) const;

    std::wstring getUnicodeStringThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    std::wstring getUnicodeString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::wstring& defaultValue) const;

    void setString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& newString, const std::string& defaultType = "");

    void setUnicodeString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::wstring& newString, const std::string& defaultType = "");

    void setAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const Age& age, const std::string& defaultType = "");

    Age getAgeThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    Age getAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const Age& defaultValue) const;

    void setDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const Date& date, const std::string& defaultType = "");

    Date getDateThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    Date getDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const Date& defaultValue) const;

    size_t getRawDataThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize) const;

    void setRawData(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize, const std::string& defaultType = "");

    std::string getDefaultDataType(std::uint16_t groupId, std::uint16_t tagId) const;

    std::string getDataTypeThrow(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId) const;

#ifndef SWIG
    std::shared_ptr<imebra::implementation::dataSet> m_pDataSet;
#endif
};

}

#endif // !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
