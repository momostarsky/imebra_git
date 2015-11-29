/*
$fileHeader$
*/

/*! \file exception.cpp
    \brief Implementation of the exception classes.

*/

#include "../include/exception.h"
#include "../include/charsetConversion.h"

namespace puntoexe
{

///////////////////////////////////////////////////////////
// Force the construction of the exceptions manager before
//  main() starts
///////////////////////////////////////////////////////////
static exceptionsManager::forceExceptionsConstruction forceConstruction;

	
///////////////////////////////////////////////////////////
// Return the message info for the specified thread
///////////////////////////////////////////////////////////
std::wstring exceptionsManager::getMessage()
{
	tExceptionInfoList infoList;
	exceptionsManager::getExceptionInfo(&infoList);

	std::wstring message;
	for(tExceptionInfoList::iterator scanInfo = infoList.begin(); 
		scanInfo != infoList.end(); 
		++scanInfo)
	{
		message += scanInfo->getMessage();
		message += L"\n\n";
	}

	return message;
}


///////////////////////////////////////////////////////////
// Return the info objects for the specified thread
///////////////////////////////////////////////////////////
void exceptionsManager::getExceptionInfo(tExceptionInfoList* pList)
{
	ptr<exceptionsManager> pManager(getExceptionsManager());
	lockObject lock(pManager.get());

    tInfoMap::iterator findInformation = pManager->m_information.find(std::this_thread::get_id());
	if(findInformation == pManager->m_information.end())
	{
		return;
	}
	for(tExceptionInfoList::iterator scanInformation = findInformation->second.begin(); 
		scanInformation != findInformation->second.end(); 
		++scanInformation)
	{
		pList->push_back(*scanInformation);
	}
	pManager->m_information.erase(findInformation);
}


///////////////////////////////////////////////////////////
// Add an info object to the current thread
///////////////////////////////////////////////////////////
void exceptionsManager::addExceptionInfo(const exceptionInfo& info)
{
	ptr<exceptionsManager> pManager(getExceptionsManager());
	lockObject lock(pManager.get());
    pManager->m_information[std::this_thread::get_id()].push_back(info);
}


///////////////////////////////////////////////////////////
// Clears the information list for the current thread
///////////////////////////////////////////////////////////
void exceptionsManager::clearExceptionInfo()
{
	ptr<exceptionsManager> pManager(getExceptionsManager());
	lockObject lock(pManager.get());
    tInfoMap::iterator findInformation = pManager->m_information.find(std::this_thread::get_id());
	if(findInformation == pManager->m_information.end())
	{
		return;
	}
	pManager->m_information.erase(findInformation);
}

///////////////////////////////////////////////////////////
// Return a pointer to the exceptions manager
///////////////////////////////////////////////////////////
ptr<exceptionsManager> exceptionsManager::getExceptionsManager()
{
	static ptr<exceptionsManager> m_manager(new exceptionsManager);
	return m_manager;
}


///////////////////////////////////////////////////////////
// Construct the exceptionInfo object
///////////////////////////////////////////////////////////
exceptionInfo::exceptionInfo(const std::wstring& functionName, const std::string& fileName, const long lineNumber, const std::string& exceptionType, const std::string& exceptionMessage):
	m_functionName(functionName), 
	m_fileName(fileName),
	m_lineNumber(lineNumber),
	m_exceptionType(exceptionType),
	m_exceptionMessage(exceptionMessage)
{}

///////////////////////////////////////////////////////////
// Construct the exceptionInfo object
///////////////////////////////////////////////////////////
exceptionInfo::exceptionInfo(): m_lineNumber(0)
{}
	
///////////////////////////////////////////////////////////
// Copy constructor
///////////////////////////////////////////////////////////
exceptionInfo::exceptionInfo(const exceptionInfo& right):
			m_functionName(right.m_functionName), 
			m_fileName(right.m_fileName),
			m_lineNumber(right.m_lineNumber),
			m_exceptionType(right.m_exceptionType),
			m_exceptionMessage(right.m_exceptionMessage)
{}

///////////////////////////////////////////////////////////
// Copy operator
///////////////////////////////////////////////////////////
exceptionInfo& exceptionInfo::operator=(const exceptionInfo& right)
{
	m_functionName = right.m_functionName;
	m_fileName = right.m_fileName;
	m_lineNumber = right.m_lineNumber;
	m_exceptionType = right.m_exceptionType;
	m_exceptionMessage = right.m_exceptionMessage;
	return *this;
}

///////////////////////////////////////////////////////////
// Return the exceptionInfo content in a string
///////////////////////////////////////////////////////////
std::wstring exceptionInfo::getMessage()
{
    defaultCharsetConversion convertUnicode("ISO_IR 6");
	std::wostringstream message;
	message << "[" << m_functionName << "]" << "\n";
    message << " file: " << convertUnicode.toUnicode(m_fileName) << "  line: " << m_lineNumber << "\n";
    message << " exception type: " << convertUnicode.toUnicode(m_exceptionType) << "\n";
    message << " exception message: " << convertUnicode.toUnicode(m_exceptionMessage) << "\n";
	return message.str();
}



} // namespace puntoexe
