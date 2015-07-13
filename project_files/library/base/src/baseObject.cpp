/*
$fileHeader$
*/

/*! \file baseObject.cpp
    \brief Implementation of the baseObject class.

*/

#include "../include/baseObject.h"
#include "../include/exception.h"
#include <iostream>

namespace puntoexe
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// basePtr
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Default constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
basePtr::basePtr() : object(0)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor with initialization
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
basePtr::basePtr(baseObject* pObject): object(pObject)
{
	addRef();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
basePtr::~basePtr()
{
	release();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Release
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void basePtr::release()
{
	if(object != 0)
	{
		object->release();
		object = 0;
	}
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Increase reference counter
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void basePtr::addRef()
{
	if(object != 0)
	{
		object->addRef();
	}
}




///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// baseObject
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
// Default constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
baseObject::baseObject(): m_lockCounter(0), m_bValid(true), m_pCriticalSection(new CObjectCriticalSection)
{
    m_pCriticalSection->addRef();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructs the object and set an external lock
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
baseObject::baseObject(const ptr<baseObject>& externalLock): 
	m_lockCounter(0), m_bValid(true)
{
    if(externalLock == 0)
    {
        m_pCriticalSection = new CObjectCriticalSection;
    }
    else
    {
        m_pCriticalSection = externalLock->m_pCriticalSection;
    }
    m_pCriticalSection->addRef();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return true if the object is referenced once.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool baseObject::isReferencedOnce()
{
	return m_lockCounter == 1;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
baseObject::~baseObject()
{
    m_pCriticalSection->release();
    m_bValid = false;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Increase the references counter
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void baseObject::addRef()
{
    if(this != 0)
	{
        ++m_lockCounter;
	}
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Decrease the references counter and delete the object
//  if the counter reaches 0
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void baseObject::release()
{
	// Calling release on a non-existing object.
	// Simply return
	///////////////////////////////////////////////////////////
	if(this == 0)
	{
		return;
	}

	// Decrease the reference counter
	///////////////////////////////////////////////////////////
    if(--m_lockCounter != 0)
    {
        return;
    }

	if(!preDelete())
	{
		return;
	}

	delete this;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// This function is called by release() just before
//  the object is deleted.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool baseObject::preDelete()
{
	return true;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Lock the object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void baseObject::lock()
{
	if(this == 0)
	{
		return;
	}
	m_pCriticalSection->m_criticalSection.lock();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Unlock the object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void baseObject::unlock()
{
	if(this == 0)
	{
		return;
	}
	m_pCriticalSection->m_criticalSection.unlock();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// lockObject
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
// Lock the specified object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
lockObject::lockObject(baseObject* pObject)
{
	m_pObject = pObject;
	if(m_pObject != 0)
	{
		m_pObject->lock();
	}
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Unlock the specified object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
lockObject::~lockObject()
{
	unlock();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Unlock the specified object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void lockObject::unlock()
{
	if( m_pObject != 0)
	{
		m_pObject->unlock();
		m_pObject = 0;
	}
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// lockMultipleObject
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
// Lock the specified objects
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
lockMultipleObjects::lockMultipleObjects(tObjectsList* pObjectsList)
{
	tCriticalSectionsList csList;
	for(tObjectsList::iterator scanObjects = pObjectsList->begin(); scanObjects != pObjectsList->end(); ++scanObjects)
	{
		if((*scanObjects) == 0)
		{
			continue;
		}
		csList.push_back(&( (*scanObjects)->m_pCriticalSection->m_criticalSection) );
	}
	m_pLockedCS.reset(puntoexe::lockMultipleCriticalSections(&csList));
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Unlock the locked objects
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
lockMultipleObjects::~lockMultipleObjects()
{
	unlock();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Unlock the locked objects
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void lockMultipleObjects::unlock()
{
	if(m_pLockedCS.get() == 0)
	{
		return;
	}
	puntoexe::unlockMultipleCriticalSections(m_pLockedCS.get());
        m_pLockedCS.reset();
}


} // namespace puntoexe
