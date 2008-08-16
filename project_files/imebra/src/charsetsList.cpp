/*
$fileHeader$
*/

/*! \file charsetsList.cpp
    \brief Implementation of the basic class for the classes that handles the charsets.

*/

#include "../../base/include/exception.h"
#include "../include/charsetsList.h"


namespace puntoexe
{

namespace imebra
{

namespace charsetsList
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// charsetsList
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Copy the charsets in the list into the local list.
// An exception is thrown if a mismatch in the default
//  charset is detected
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void updateCharsets(tCharsetsList* pCharsetsList, tCharsetsList* pDestinationCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"charsetsList::updateCharsets");

	// Check the default charset
	///////////////////////////////////////////////////////////
	if(!pCharsetsList->empty() && !pDestinationCharsetsList->empty() && pCharsetsList->front() != pDestinationCharsetsList->front())
	{
		PUNTOEXE_THROW(charsetListExceptionDiffDefault, "Different default charsets");
	}

	// Copy the charsets in the local list (if they are not
	//  already there)
	///////////////////////////////////////////////////////////
	for(tCharsetsList::iterator scanCharsets = pCharsetsList->begin(); scanCharsets != pCharsetsList->end(); ++scanCharsets)
	{
		bool bExist = false;
		for(tCharsetsList::iterator scanExistingCharsets = pDestinationCharsetsList->begin(); scanExistingCharsets != pDestinationCharsetsList->end(); ++scanExistingCharsets)
		{
			if(*scanCharsets == *scanExistingCharsets)
			{
				bExist = true;
				break;
			}
		}
		if(!bExist)
		{
			pDestinationCharsetsList->push_back(*scanCharsets);
		}
	}

	PUNTOEXE_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Copy the charsets from the local list into the
//  specified list
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void copyCharsets(tCharsetsList* pSourceCharsetsList, tCharsetsList* pDestinationCharsetsList)
{
	PUNTOEXE_FUNCTION_START(L"charsetsList::copyCharsets");

	for(tCharsetsList::iterator scanCharsets = pSourceCharsetsList->begin(); scanCharsets != pSourceCharsetsList->end(); ++scanCharsets)
	{
		pDestinationCharsetsList->push_back(*scanCharsets);
	}

	PUNTOEXE_FUNCTION_END();
}

} // namespace charsetsList

} // namespace imebra

} // namespace puntoexe
