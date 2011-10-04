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

class imebraDataSet
{
public:
	// Costructor
	///////////////////////////////////////////////////////////
	imebraDataSet();

	imebraDataSet(const imebraDataSet& right);

	imebraDataSet& operator=(const imebraDataSet& right);

#ifndef SWIG
	imebraDataSet(puntoexe::ptr<puntoexe::imebra::dataSet> pDataSet);
#endif
/*
	data getTag(unsigned int groupId, unsigned int order, unsigned int tagId, bool bCreate=false);
	
	dataGroup getGroup(unsigned int groupId, unsigned int order, bool bCreate=false);
	
	void setGroup(unsigned int groupId, unsigned int order, dataGroup group);

	image getImage(unsigned int frameNumber);
	
	dataSet getSequenceItem(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long itemId);

	long getSignedLong(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber);

	void setSignedLong(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 elementNumber, imbxInt32 newValue, std::string defaultType = "");

	imbxUint32 getUnsignedLong(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 elementNumber);

	void setUnsignedLong(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 elementNumber, imbxUint32 newValue, std::string defaultType = "");

	double getDouble(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 elementNumber);

	void setDouble(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 elementNumber, double newValue, std::string defaultType = "");

	std::string getString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber);
*/
	std::wstring getUnicodeString(unsigned int groupId, unsigned int order, unsigned int tagId, unsigned long elementNumber);

	/*
	void setString(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 elementNumber, std::string newString, std::string defaultType = "");

	/// \brief Set a tag's value as an unicode string.
	///
	/// If the specified tag doesn't exist, then a new one
	///  will be created and inserted into the dataset.
	///
	/// @param groupId The group to which the tag to be write
	///                 belongs
	/// @param order   If the group is recurring in the file
	///                 (it appears several times), then use
	///                 this parameter to specify to which
	///                 group the group belongs.
	///                This parameter is used to deal with
	///                 old DICOM files, since the new one
	///                 should use the sequence items to
	///                 achieve the same result.
	///                It should be set to zero
	/// @param tagId   The id of the tag to set
	/// @param elementNumber The element's number to set.
	///                A buffer can store several elements:
	///                 this parameter specifies which element
	///                 must be set.
	///                The first element's number is 0
	/// @param newString the value to be written into the tag
	/// @param defaultType if the specified tag doesn't exist
	///                 then the function will create a new
	///                 tag with the data type specified in
	///                 this parameter
	///
	///////////////////////////////////////////////////////////
	void setUnicodeString(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 elementNumber, std::wstring newString, std::string defaultType = "");

	//@}


	///////////////////////////////////////////////////////////
	/// \name Data handlers
	///
	///////////////////////////////////////////////////////////
	//@{
public:
	/// \brief Return the default data type for the specified
	///        tag's id.
	///
	/// The default data type is retrieved from an internal
	///  dictionary which stores the default properties of
	///  each dicom's tag.
	///
	/// @param groupId    The group to which the tag
	///                   belongs
	/// @param tagId      The id of the tag.
	/// @return           the tag's default type.
	///                   The returned string is a constant.
	///////////////////////////////////////////////////////////
	std::string getDefaultDataType(imbxUint16 groupId, imbxUint16 tagId);

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
	std::string getDataType(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId);

	/// \brief Return a data handler for the specified tag's
	///         buffer.
	///
	/// The data handler allows the application to read, write
	///  and resize the tag's buffer.
	///
	/// A tag can store several buffers, then the application
	///  must specify the buffer's id it wants to deal with.
	///
	/// @param groupId the group to which the tag belongs
	/// @param order   if the group is recurring in the file
	///                 (it appears several times), then use
	///                 this parameter to specify to which
	///                 group the tag belongs.
	///                This parameter is used to deal with
	///                 old DICOM files, since the new one
	///                 should use the sequence items to
	///                 achieve the same result.
	///                It should be set to zero
	/// @param tagId   the tag's id
	/// @param bufferId the buffer's id (zero based)
	/// @param bWrite  true if the application wants to write
	///                 into the buffer
	/// @param defaultType a string with the dicom data type 
	///                 to use if the buffer doesn't exist.
	///                If none is specified, then a default
	///                 data type will be used
	/// @return a pointer to the data handler.
	///
	///////////////////////////////////////////////////////////
	ptr<handlers::dataHandler> getDataHandler(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 bufferId, bool bWrite, std::string defaultType="");

	/// \brief Return a raw data handler for the specified 
	///         tag's buffer.
	///
	/// A raw data handler always sees the buffer as a 
	///  collection of bytes, no matter what the tag's data
	///  type is.
	///
	/// A tag can store several buffers, then the application
	///  must specify the buffer's id it wants to deal with.
	///
	/// @param groupId the group to which the tag belongs
	/// @param order   if the group is recurring in the file
	///                 (it appears several times), then use
	///                 this parameter to specify to which
	///                 group the tag belongs.
	///                This parameter is used to deal with
	///                 old DICOM files, since the new one
	///                 should use the sequence items to
	///                 achieve the same result.
	///                It should be set to zero
	/// @param tagId   the tag's id
	/// @param bufferId the buffer's id (zero based)
	/// @param bWrite  true if the application wants to write
	///                 into the buffer
	/// @param defaultType a string with the dicom data type 
	///                 to use if the buffer doesn't exist.
	///                If none is specified, then a default
	///                 data type will be used
	/// @return a pointer to the data handler.
	///
	///////////////////////////////////////////////////////////
	ptr<handlers::dataHandlerRaw> getDataHandlerRaw(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 bufferId, bool bWrite, std::string defaultType="");

	/// \brief Return a streamReader connected to the specified
	///         tag's buffer's memory.
	///
	/// A tag can store several buffers: the application
	///  must specify the buffer's id it wants to deal with.
	///
	/// @param groupId the group to which the tag belongs
	/// @param order   if the group is recurring in the file
	///                 (it appears several times), then use
	///                 this parameter to specify to which
	///                 group the tag belongs.
	///                This parameter is used to deal with
	///                 old DICOM files, since the new one
	///                 should use the sequence items to
	///                 achieve the same result.
	///                It should be set to zero
	/// @param tagId   the tag's id
	/// @param bufferId the buffer's id (zero based)
	/// @return a pointer to the streamReader
	///
	///////////////////////////////////////////////////////////
	ptr<streamReader> getStreamReader(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 bufferId);

	/// \brief Return a streamWriter connected to the specified
	///         tag's buffer's memory.
	///
	/// A tag can store several buffers, then the application
	///  must specify the buffer's id it wants to deal with.
	///
	/// @param groupId the group to which the tag belongs
	/// @param order   if the group is recurring in the file
	///                 (it appears several times), then use
	///                 this parameter to specify to which
	///                 group the tag belongs.
	///                This parameter is used to deal with
	///                 old DICOM files, since the new one
	///                 should use the sequence items to
	///                 achieve the same result.
	///                It should be set to zero
	/// @param tagId   the tag's id
	/// @param bufferId the buffer's id (zero based)
	/// @param dataType the datatype used to create the 
	///                 buffer if it doesn't exist already
	/// @return a pointer to the streamWriter
	///
	///////////////////////////////////////////////////////////
	ptr<streamWriter> getStreamWriter(imbxUint16 groupId, imbxUint16 order, imbxUint16 tagId, imbxUint32 bufferId, std::string dataType = "");

	//@}


	///////////////////////////////////////////////////////////
	/// \name Syncronize the charset tag (0008,0005)
	///
	///////////////////////////////////////////////////////////
	//@{
	
	/// \brief Collect all the charsets used in the dataSet's
	///         tags and then update the content of the tag
	///         0008,0005.
	///
	/// This function is called by the codecs before the dicom
	///  stream is saved, therefore the application doesn't
	///  need to call the function before saving the stream.
	///
	///////////////////////////////////////////////////////////
	void updateCharsetTag();

	/// \brief Update all the dataSet's tags with the charsets
	///         specified in the tag 0008,0005.
	///
	/// This function is called by the codecs after the stream
	///  has been loaded, therefore the application doesn't
	///  need to call the function after the stream has been
	///  loaded.
	///
	///////////////////////////////////////////////////////////
	void updateTagsCharset();

	//@}


	///////////////////////////////////////////////////////////
	/// \name Set/get the item offset.
	///
	///////////////////////////////////////////////////////////
	//@{
	
	/// \brief Called by codecs::dicomCodec when the dataset
	///         is written into a stream.
	///        Tells the dataSet the position at which it has
	///         been written into the stream
	///
	/// @param offset   the position at which the dataSet has
	///                  been written into the stream
	///
	///////////////////////////////////////////////////////////
	void setItemOffset(imbxUint32 offset);

	/// \brief Retrieve the offset at which the dataSet is
	///         located in the dicom stream.
	///
	/// @return the position at which the dataSet is located
	///          in the dicom stream
	///
	///////////////////////////////////////////////////////////
	imbxUint32 getItemOffset();

	//@}

protected:
	// Convert an image using the attributes specified in the
	//  the dataset
	///////////////////////////////////////////////////////////
	ptr<image> convertImageForDataSet(ptr<image> sourceImage);

	std::vector<imbxUint32> m_imagesPositions;

	// Position of the sequence item in the stream. Used to
	//  parse DICOMDIR items
	///////////////////////////////////////////////////////////
	imbxUint32 m_itemOffset;
	*/
#ifndef SWIG
protected:
	puntoexe::ptr<puntoexe::imebra::dataSet> m_pDataSet;
#endif
};




#endif // !defined(imebraDataSet_SWIG_93F684BF_0024_4bf3_89BA_D98E82A1F44C__INCLUDED_)
