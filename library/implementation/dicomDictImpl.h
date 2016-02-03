/*
$fileHeader$
*/

/*! \file dicomDict.h
    \brief Declaration of the class dicomDict.

*/


#if !defined(imebraDicomDict_CC44A2C5_2B8C_42c1_9704_3F9C582643B9__INCLUDED_)
#define imebraDicomDict_CC44A2C5_2B8C_42c1_9704_3F9C582643B9__INCLUDED_

#include <memory>
#include <map>


namespace imebra
{

namespace implementation
{

/// \addtogroup group_dictionary Dicom dictionary
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief The Dicom Dictionary.
///
/// This class can be used to retrieve the tags' default
///  data types and descriptions.
///
/// An instance of this class is automatically allocated
///  by the library: your application should use the
///  static function getDicomDictionary() in order to
///  get the only valid instance of this class.
/// 
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dicomDictionary
{
    dicomDictionary();

	struct imageDataDictionaryElement
	{
		std::wstring m_tagName;
		std::string m_tagType;
	};

	struct validDataTypesStruct
	{
		bool  m_longLength;       // true if the tag has a 4 bytes length descriptor
		std::uint32_t m_wordLength;       // Word's length, used for byte reversing in hi/lo endian conversion
		std::uint32_t m_maxLength;        // The maximum length for the tag. An exception will be trown while reading a tag which exceedes this size 
	};

public:
	void registerTag(std::uint32_t tagId, const wchar_t* tagName, const char* tagType);
    void registerVR(const std::string& vr, bool bLongLength, std::uint32_t wordSize, std::uint32_t maxLength);

	/// \brief Retrieve a tag's description.
	///
	/// @param groupId   The group which the tag belongs to
	/// @param tagId     The tag's id
	/// @return          The tag's description
	///
	///////////////////////////////////////////////////////////
	std::wstring getTagName(std::uint16_t groupId, std::uint16_t tagId) const;

	/// \brief Retrieve a tag's default data type.
	///
	/// @param groupId   The group which the tag belongs to
	/// @param tagId     The tag's id
	/// @return          The tag's data type
	///
	///////////////////////////////////////////////////////////
	std::string getTagType(std::uint16_t groupId, std::uint16_t tagId) const;

	/// \brief Retrieve the only valid instance of this class.
	///
	/// @return a pointer to the dicom dictionary
	///
	///////////////////////////////////////////////////////////
	static dicomDictionary* getDicomDictionary();

	/// \brief Return true if the specified string represents
	///         a valid dicom data type.
	///
	/// @param dataType the string to be checked
	/// @return         true if the specified string is a valid
	///                  dicom data type
	///
	///////////////////////////////////////////////////////////
    bool isDataTypeValid(const std::string& dataType) const;

	/// \brief Return true if the tag's length in the dicom 
	///         stream must be written using a DWORD
	///
	/// @param dataType the data type for which the information
	///                  is required
	/// @return         true if the specified data type's 
	///                  length must be written using a DWORD
	///
	///////////////////////////////////////////////////////////
    bool getLongLength(const std::string& dataType) const ;
	
	/// \brief Return the size of the data type's elements
	///
	/// @param dataType the data type for which the information
	///                  is required
	/// @return the size of a single element
	///
	///////////////////////////////////////////////////////////
    std::uint32_t getWordSize(const std::string& dataType) const;
	
	/// \brief Return the maximum size of the tags with
	///         the specified data type.
	///
	/// @param dataType the data type for which the information
	///                  is required
	/// @return         the maximum tag's size in bytes 
	///
	///////////////////////////////////////////////////////////
    std::uint32_t getMaxSize(const std::string& dataType) const;

protected:
	typedef std::map<std::uint32_t, imageDataDictionaryElement> tDicomDictionary;
	tDicomDictionary m_dicomDict;

	typedef std::map<std::string, validDataTypesStruct> tVRDictionary;
	tVRDictionary m_vrDict;

};

/// @}

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDicomDict_CC44A2C5_2B8C_42c1_9704_3F9C582643B9__INCLUDED_)
