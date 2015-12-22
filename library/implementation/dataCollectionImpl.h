/*
$fileHeader$
*/

/*! \file dataCollection.h
    \brief Declaration of the base class used by the dataSet and the dataGroup
	        classes.

*/

#if !defined(imebraDataCollection_22668C4B_A480_4f6e_B5DC_ADAD585444DA__INCLUDED_)
#define imebraDataCollection_22668C4B_A480_4f6e_B5DC_ADAD585444DA__INCLUDED_

#include "exceptionImpl.h"
#include "dataImpl.h"
#include "charsetsListImpl.h"


#include <map>
#include <string>

///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

// The following classes are used in the declaration
class data;

/// \addtogroup group_dataset
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class accesses to all the %data stored
///         in a dataCollection derived class (dataGroup or
///         dataSet).
///
/// When retrieved from a dataSet this class accesses all
///  the groups (class dataGroup) in the dataSet, while
///  when retrieved from a dataGroup it accesses all the
///  tags (class data) in the dataGroup.
///
/// After the creation the iterator references the first
///  data or dataGroup in the collection.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <class collectionType>
class dataCollectionIterator
{
public:
	dataCollectionIterator()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollectionIterator::dataCollectionIterator");

		m_iterator=m_collection.begin();

		PUNTOEXE_FUNCTION_END();
	}

	/// \brief Increase the iterator so it references the next 
	///         data or dataGroup in the collection.
	///
	/// @return true if after the increment the iterator 
	///          references a valid data or dataGroup, or false 
	///          if after the increment the iterator references
	///          the end of the collection (invalid data or
	///          dataGroup)
	///
	///////////////////////////////////////////////////////////
	bool incIterator()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollectionIterator::incIterator");

		if(isValid())
		{
			++m_iterator;
		}
		return isValid();

		PUNTOEXE_FUNCTION_END();
	}
	

	/// \brief Reset the iterator so it referencesthe first
	///         data or dataGroup in the collection.
	///
	/// @return true if after the reset the iterator references
	///          to a valid data or dataGroup, or false if
	///          after the reset the iterator references
	///          the end of the collection (it means that the
	///          collection is empty)
	///
	///////////////////////////////////////////////////////////
	bool reset()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollectionIterator::reset");

		m_iterator=m_collection.begin();
		return isValid();

		PUNTOEXE_FUNCTION_END();
	}
	
	/// \brief Returns true if the iterator references a valid
	///         data or dataGroup in the collection.
	///
	/// @return true if the iterator references a valid data or
	///          dataGroup, or false if the iterator references
	///          the end of the collection
	///
	///////////////////////////////////////////////////////////
	bool isValid()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollectionIterator::isValid");

		return m_iterator!=m_collection.end();

		PUNTOEXE_FUNCTION_END();
	}

	/// \brief Retrieve the data or dataGroup referenced by the
	///         iterator.
	///
	/// This function returns 0 if the iterator references an
	///  invalid data or dataGroup (isValid() returns false).
	///
	/// @return the data or dataGroup referenced by the
	///          iterator
	///
	///////////////////////////////////////////////////////////
	std::shared_ptr<collectionType> getData()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollectionIterator::getData");

		std::shared_ptr<collectionType> collection;

		if(isValid())
		{
			collection = m_iterator->second;
		}

		return collection;

		PUNTOEXE_FUNCTION_END();
	}
	
	/// \brief Return the id of the data or dataGroup
	///         referenced by the iterator.
	///
	/// If the iterator references an invalid data or dataGroup
	///  (isValid() returns false) then the function returns 0.
	///
	/// @return the id of the referenced data or dataGroup
	///
	///////////////////////////////////////////////////////////
	std::uint16_t getId()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollectionIterator::getId");

		if(m_iterator==m_collection.end())
		{
			return 0;
		}

		return (std::uint16_t)((m_iterator->first)>>16);

		PUNTOEXE_FUNCTION_END();
	}
	
	/// \brief Retrieve the order of the referenced data or
	///         dataGroup.
	///
	/// This function is used only while retrieving dataGroups
	///  because there can be several groups with the same id;
	///  in this case the function retrieve the order of
	///  the dataGroup, that could be bigger than 0 when 
	///  several %data groups with the same id are stored in
	///  the collection.
	///
	/// When used while retrieving the tags (class data) this
	///  function always returns 0.
	///
	/// The function returns 0 also when used while the 
	///  iterator references an invalid dataGroup (isValid()
	///  returns 0).
	///
	/// @return the dataGroup's order
	///
	///////////////////////////////////////////////////////////
	std::uint16_t getOrder()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollectionIterator::getOrder");

		if(m_iterator==m_collection.end())
		{
			return 0;
		}

		return (std::uint16_t)((m_iterator->first) & 0x0000ffff);

		PUNTOEXE_FUNCTION_END();
	}

public:
	std::map<std::uint32_t, std::shared_ptr<collectionType> > m_collection;
	typename std::map<std::uint32_t, std::shared_ptr<collectionType> >::iterator m_iterator;
};



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class stores a collection of Dicom tags or
///         groups (classes \ref puntoexe::imebra::data or 
///         \ref puntoexe::imebra::dataGroup).
///        It is used as base class by dataGroup and
///         dataSet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <class collectionType>
class dataCollection
{
public:
	/// \brief Set the charsets used in the collection
	///
	/// The charsets contained in the list are copied in a
	///  local list.
	///
	/// @param pCharsetsList a pointer to the list of charsets
	///                       used in the collection.
	///                      The list's content is copied in
	///                       a local list
	///
	///////////////////////////////////////////////////////////
	virtual void setCharsetsList(charsetsList::tCharsetsList* pCharsetsList)
	{
		m_charsetsList.clear();
		charsetsList::updateCharsets(pCharsetsList, &m_charsetsList);
		
		for(
			typename std::map<std::uint32_t, std::shared_ptr<collectionType> >::iterator dataIterator=m_collection.begin(); 
			dataIterator!=m_collection.end(); 
			++dataIterator)
		{
			dataIterator->second->setCharsetsList(pCharsetsList);
		}
	}
	
	/// \internal
	/// \brief Fill a list with the charsets used in the
	///         collection.
	///
	/// Queries all the children objects (dataGroup or data)
	///  for their charsets, update the local charsets list
	///  and the list specified as a parameter.
	///
	/// @param pCharsetsList a pointer to the list that will
	///                       be filled with the used charsets
	///
	///////////////////////////////////////////////////////////
	virtual void getCharsetsList(charsetsList::tCharsetsList* pCharsetsList)
	{
		m_charsetsList.clear();
		for(
			typename std::map<std::uint32_t, std::shared_ptr<collectionType> >::iterator dataIterator=m_collection.begin(); 
			dataIterator!=m_collection.end(); 
			++dataIterator)
		{
			charsetsList::tCharsetsList charsets;
			dataIterator->second->getCharsetsList(&charsets);
			charsetsList::updateCharsets(&charsets, &m_charsetsList);
		}

        pCharsetsList->insert(pCharsetsList->end(), m_charsetsList.begin(), m_charsetsList.end());
	}


protected:

	//
	// In a dataGroup class returns the tag (std::shared_ptr<data>with 
	//  the specified ID, while in a dataSet class returns
	//  the group (std::shared_ptr<dataGroup>) with the specified ID.
	//
	///////////////////////////////////////////////////////////
	std::shared_ptr<collectionType> getData(std::uint16_t dataId, std::uint16_t order)
	{
		PUNTOEXE_FUNCTION_START(L"dataCollection::getData");

		std::uint32_t dataUid = (((std::uint32_t)dataId)<<16) | (std::uint32_t)order;

		std::shared_ptr<collectionType> returnCollection;

		typename std::map<std::uint32_t, std::shared_ptr<collectionType> >::iterator findCollection = m_collection.find(dataUid);
		if(findCollection != m_collection.end())
		{
			returnCollection = findCollection->second;
		}

		return returnCollection;

		PUNTOEXE_FUNCTION_END();
	}
	
	// Set the data (tag or group)
	///////////////////////////////////////////////////////////
	void setData(std::uint16_t dataId, std::uint16_t order, const std::shared_ptr<collectionType>& pData)
	{
		PUNTOEXE_FUNCTION_START(L"dataCollection::setData");

		std::uint32_t dataUid = (((std::uint32_t)dataId)<<16) | (std::uint32_t)order;
		m_collection[dataUid] = pData;
		pData->setCharsetsList(&m_charsetsList);

		PUNTOEXE_FUNCTION_END();
	}

public:
	/// \brief Return an iterator pointing to the first tag or
	///         group (data or dataGroup) in the collection.
	///
	/// You can use this function to scan all the tags (data)
	///  in a dataGroup or all the groups (dataGroup) in a 
	///  dataSet.
	///
	/// See dataCollectionIterator for more information.
	///
	/// @return an iterator that accesses all the %data in
	///          the collection
	///
	///////////////////////////////////////////////////////////
	std::shared_ptr<dataCollectionIterator<collectionType> > getDataIterator()
	{
		PUNTOEXE_FUNCTION_START(L"dataCollection::getDataIterator");

		std::shared_ptr<dataCollectionIterator<collectionType> > pIterator(new dataCollectionIterator<collectionType>);

		
		for(
			typename std::map<std::uint32_t, std::shared_ptr<collectionType> >::iterator dataIterator=m_collection.begin(); 
			dataIterator!=m_collection.end(); 
			++dataIterator)
		{
			pIterator->m_collection[dataIterator->first]=dataIterator->second;
		}
		pIterator->reset();

		return pIterator;

		PUNTOEXE_FUNCTION_END();
	}

protected:
	// Stored data (tags or groups)
	///////////////////////////////////////////////////////////
	std::map<std::uint32_t, std::shared_ptr<collectionType> > m_collection;

	charsetsList::tCharsetsList m_charsetsList;
};

/// @}

} // namespace imebra

} // namespace puntoexe


#endif // !defined(imebraDataCollection_22668C4B_A480_4f6e_B5DC_ADAD585444DA__INCLUDED_)