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

    Image getImage(unsigned int frameNumber);

    void setImage(unsigned int frameNumber, Image image, const std::string& transferSyntax, imageQuality quality);

	DataSet getSequenceItem(int groupId, int order, int tagId, int itemId);

    ReadingDataHandler getReadingDataHandler(int groupId, int order, int tagId, int bufferId) const;

    WritingDataHandler getWritingDataHandler(int groupId, int order, int tagId, int bufferId, const std::string& defaultDataType = "");

    bool bufferExists(int groupId, int order, int tagId, int bufferId);

    int getSignedLong(int groupId, int order, int tagId, int bufferId, int elementNumber) const;

    void setSignedLong(int groupId, int order, int tagId, int bufferId, int elementNumber, int newValue, const std::string& defaultType = "");

    unsigned int getUnsignedLong(int groupId, int order, int tagId, int bufferId, int elementNumber) const;

    void setUnsignedLong(int groupId, int order, int tagId, int bufferId, int elementNumber, unsigned int newValue, const std::string& defaultType = "");

    double getDouble(int groupId, int order, int tagId, int bufferId, int elementNumber) const;

    void setDouble(int groupId, int order, int tagId, int bufferId, int elementNumber, double newValue, const std::string& defaultType = "");

    std::wstring getString(int groupId, int order, int tagId, int bufferId, int elementNumber) const;

    void setString(int groupId, int order, int tagId, int bufferId, int elementNumber, const std::wstring& newString, const std::string& defaultType = "");

    void setAge(int groupId, int order, int tagId, int bufferId, int elementNumber, int age, imebra::ageUnit_t units, const std::string& defaultType = "");

    int getAge(int groupId, int order, int tagId, int bufferId, int elementNumber, imebra::ageUnit_t* pUnits) const;

    void setDate(int groupId, int order, int tagId, int bufferId, int elementNumber, const Date& date, const std::string& defaultType = "");

    Date getDate(int groupId, int order, int tagId, int bufferId, int elementNumber) const;

    size_t getRawData(int groupId, int order, int tagId, int bufferId, char* buffer, size_t bufferSize) const;

    void setRawData(int groupId, int order, int tagId, int bufferId, char* buffer, size_t bufferSize, const std::string& defaultType = "");

    std::string getDefaultDataType(int groupId, int order, int tagId) const;

    std::string getDataType(int groupId, int order, int tagId) const;

#ifndef SWIG
	std::shared_ptr<puntoexe::imebra::dataSet> m_pDataSet;
#endif
};

}

#endif // !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
