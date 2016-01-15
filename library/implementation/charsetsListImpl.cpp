/*
$fileHeader$
*/

/*! \file charsetsList.cpp
    \brief Implementation of the basic class for the classes that handles the charsets.

*/

#include "exceptionImpl.h"
#include "charsetsListImpl.h"
#include "../include/imebra/exceptions.h"

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
void updateCharsets(const tCharsetsList* pCharsetsList, tCharsetsList* pDestinationCharsetsList)
{
	IMEBRA_FUNCTION_START(L"charsetsList::updateCharsets");

	// Check the default charset
	///////////////////////////////////////////////////////////
	if(!pCharsetsList->empty() && !pDestinationCharsetsList->empty() && pCharsetsList->front() != pDestinationCharsetsList->front())
	{
        IMEBRA_THROW(::imebra::charsetListExceptionDiffDefault, "Different default charsets");
	}

	// Copy the charsets in the local list (if they are not
	//  already there)
	///////////////////////////////////////////////////////////
	for(tCharsetsList::const_iterator scanCharsets = pCharsetsList->begin(); scanCharsets != pCharsetsList->end(); ++scanCharsets)
	{
        std::string charsetName(*scanCharsets);
        if(charsetName.empty())
        {
            charsetName = "ISO 2022 IR 6";
        }
		bool bExist = false;
		for(tCharsetsList::iterator scanExistingCharsets = pDestinationCharsetsList->begin(); scanExistingCharsets != pDestinationCharsetsList->end(); ++scanExistingCharsets)
		{
            if(charsetName == *scanExistingCharsets)
			{
				bExist = true;
				break;
			}
		}
		if(!bExist)
		{
            pDestinationCharsetsList->push_back(charsetName);
		}
	}

	IMEBRA_FUNCTION_END();
}


} // namespace charsetsList

} // namespace imebra

} // namespace puntoexe
