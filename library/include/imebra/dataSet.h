/*
$fileHeader$
*/

/*! \file dataSet_swig.h
    \brief Declaration of the class dataSet for SWIG.

*/

#if !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
#define imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#ifndef SWIG

#include <memory>
#include "image.h"
#include "dataHandler.h"
#include "definitions.h"

namespace puntoexe
{
namespace imebra
{
class dataSet;
}
}
#endif

namespace imebra
{

///
/// \brief The DataSet class
///
class IMEBRA_API DataSet
{
#ifndef SWIG
	friend class DirectoryRecord;
	friend class DicomDir;
#endif
public:
    /// Costructor
	///////////////////////////////////////////////////////////
	DataSet();

	DataSet(const DataSet& right);

	DataSet& operator=(const DataSet& right);

#ifndef SWIG
	DataSet(std::shared_ptr<puntoexe::imebra::dataSet> pDataSet);
#endif

	enum imageQuality
	{
		veryHigh = 0,      ///< the image is saved with very high quality. No subsampling is performed and no quantization
		high = 100,        ///< the image is saved with high quality. No subsampling is performed. Quantization ratios are low
		aboveMedium = 200, ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are low
		medium = 300,      ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are medium
		belowMedium = 400, ///< the image is saved in medium quality. Horizontal and vertical subsampling are applied. Quantization ratios are medium
		low = 500,         ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are higher than the ratios used in the belowMedium quality
		veryLow = 600	   ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are high
	};

    Image getImage(size_t frameNumber);

    void setImage(size_t frameNumber, Image image, const std::string& transferSyntax, imageQuality quality);

    DataSet getSequenceItem(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t itemId);

    ReadingDataHandler getReadingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId) const;

    WritingDataHandler getWritingDataHandler(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, const std::string& defaultDataType = "");

    bool bufferExists(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId);

    int getSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    void setSignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, int newValue, const std::string& defaultType = "");

    unsigned int getUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    void setUnsignedLong(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, unsigned int newValue, const std::string& defaultType = "");

    double getDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    void setDouble(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, double newValue, const std::string& defaultType = "");

    std::wstring getString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    void setString(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const std::wstring& newString, const std::string& defaultType = "");

    void setAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, int age, imebra::ageUnit_t units, const std::string& defaultType = "");

    int getAge(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, imebra::ageUnit_t* pUnits) const;

    void setDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber, const Date& date, const std::string& defaultType = "");

    Date getDate(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, size_t elementNumber) const;

    size_t getRawData(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize) const;

    void setRawData(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId, size_t bufferId, char* buffer, size_t bufferSize, const std::string& defaultType = "");

    std::string getDefaultDataType(std::uint16_t groupId, std::uint16_t tagId) const;

    std::string getDataType(std::uint16_t groupId, std::uint16_t order, std::uint16_t tagId) const;

#ifndef SWIG
	std::shared_ptr<puntoexe::imebra::dataSet> m_pDataSet;
#endif
};

}

#endif // !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
