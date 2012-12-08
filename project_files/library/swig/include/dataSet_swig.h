/*
$fileHeader$
*/

/*! \file dataSet_swig.h
    \brief Declaration of the class dataSet for SWIG.

*/

#if !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
#define imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_

#ifndef SWIG
#include "../../imebra/include/dataSet.h"
#endif

/// \addtogroup group_swig_bindings Bindings
///
/// The binding classes interface the Imebra library
///  with software written in Java, PHP, Python and others.
///
///////////////////////////////////////////////////////////
/// @{

class dataSet
{
#ifndef SWIG
	friend class directoryRecord;
	friend class dicomDir;
#endif
public:
	// Costructor
	///////////////////////////////////////////////////////////
	dataSet();

	dataSet(const dataSet& right);

	dataSet& operator=(const dataSet& right);

#ifndef SWIG
	dataSet(puntoexe::ptr<puntoexe::imebra::dataSet> pDataSet);
#endif

	image getImage(unsigned int frameNumber);

	dataSet getSequenceItem(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long itemId);

	long getSignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber);

	void setSignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, long newValue, std::string defaultType = "");

	unsigned long getUnsignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber);

	void setUnsignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, unsigned long newValue, std::string defaultType = "");

	double getDouble(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber);

	void setDouble(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, double newValue, std::string defaultType = "");

	std::wstring getString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber);

	void setString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber, std::wstring newString, std::string defaultType = "");

	std::string getDefaultDataType(unsigned int groupId, unsigned int order, unsigned int tagId);

	/// \brief Return the data type of a tag
	///
	/// @param groupId    The group to which the tag belongs
	/// @param order      When multiple groups with the same
	///                    it are present, then use this
	///                    parameter to specify which group
	///                    must be used. The first group as
	///                    an order of 0.
	/// @param tagId      The id of the tag for which the type
	///                    must be retrieved.
	/// @return           a string with the tag's type.
	///
	///////////////////////////////////////////////////////////
	std::string getDataType(unsigned int groupId, unsigned int order, unsigned int tagId);

#ifndef SWIG
protected:
	puntoexe::ptr<puntoexe::imebra::dataSet> m_pDataSet;
#endif
};

///@}

#endif // !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
