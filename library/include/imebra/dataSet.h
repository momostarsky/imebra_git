/*
$fileHeader$
*/

/*! \file dataSet_swig.h
    \brief Declaration of the class dataSet for SWIG.

*/

#if !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
#define imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#ifndef SWIG
#include "../../implementation/baseObjectImpl.h"

namespace puntoexe
{
namespace imebra
{
class dataSet;
}
}
#endif

#include "image.h"

/// \addtogroup group_swig_bindings Bindings
///
/// The binding classes interface the Imebra library
///  with software written in Java, PHP, Python and others.
///
///////////////////////////////////////////////////////////
/// @{

class DataSet
{
#ifndef SWIG
	friend class DirectoryRecord;
	friend class DicomDir;
#endif
public:
	// Costructor
	///////////////////////////////////////////////////////////
	DataSet();

	DataSet(const DataSet& right);

	DataSet& operator=(const DataSet& right);

#ifndef SWIG
	DataSet(puntoexe::ptr<puntoexe::imebra::dataSet> pDataSet);
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

	Image getImage(int frameNumber);

	void setImage(int frameNumber, Image image, std::wstring transferSyntax, imageQuality quality);

	DataSet getSequenceItem(int groupId, int order, int tagId, int itemId);

	int getSignedLong(int groupId, int order, int tagId, int elementNumber);

	void setSignedLong(int groupId, int order, int tagId, int elementNumber, int newValue, std::string defaultType = "");

	int getUnsignedLong(int groupId, int order, int tagId, int elementNumber);

	void setUnsignedLong(int groupId, int order, int tagId, int elementNumber, int newValue, std::string defaultType = "");

	double getDouble(int groupId, int order, int tagId, int elementNumber);

	void setDouble(int groupId, int order, int tagId, int elementNumber, double newValue, std::string defaultType = "");

	std::wstring getString(int groupId, int order, int tagId, int elementNumber);

	void setString(int groupId, int order, int tagId, int elementNumber, std::wstring newString, std::string defaultType = "");

        size_t getRawData(int groupId, int order, int tagId, int bufferId, char* buffer, int bufferSize);

        void setRawData(int groupId, int order, int tagId, int bufferId, char* buffer, int bufferSize, std::string defaultType = "");

	std::string getDefaultDataType(int groupId, int order, int tagId);

	std::string getDataType(int groupId, int order, int tagId);

#ifndef SWIG
	puntoexe::ptr<puntoexe::imebra::dataSet> m_pDataSet;
#endif
};

///@}

#endif // !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
