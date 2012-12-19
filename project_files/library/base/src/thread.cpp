/*
$fileHeader$
*/

/*! \file thread.cpp
    \brief Implementation of the thread-related functions.

*/

#include "../include/thread.h"
#include "../include/exception.h"
#include <map>
#include <memory>

#ifdef PUNTOEXE_WINDOWS
#include <process.h>
#endif

#ifdef PUNTOEXE_POSIX
#include <sched.h>
#include <errno.h>
#endif

namespace puntoexe
{

#ifdef PUNTOEXE_POSIX
static thread::forceKeyConstruction forceKey;
#endif

typedef std::map<thread::tThreadId, thread*> tActiveThreads;
static tActiveThreads m_activeThreads;
criticalSection m_lockActiveThreads;

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// thread
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
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
thread::thread():
    m_bThreadHandleValid(false),
        m_bTerminate(false),
        m_bIsRunning(false)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Stop the thread before deallocating it
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool thread::preDelete()
{
	PUNTOEXE_FUNCTION_START(L"thread::preDelete");

	// If the thread's handle is not valid (not started yet),
	//  then return immediatly
	///////////////////////////////////////////////////////////
	{
		lockCriticalSection lockThreadHandle(&m_lockThreadHandle);
		if( !m_bThreadHandleValid )
		{
			return true;
		}
	}

	// Send a termination request to the thread's function
	///////////////////////////////////////////////////////////
	terminate();

#ifdef PUNTOEXE_WINDOWS

	// Wait for the thread termination, then close and
	//  invalidate the thread
	///////////////////////////////////////////////////////////
	::WaitForSingleObject(m_threadHandle, INFINITE);

	lockCriticalSection lockThreadHandle(&m_lockThreadHandle);
	::CloseHandle(m_threadHandle);
	m_bThreadHandleValid = false;

#else

	// Join the thread, then invalidate the handle
	///////////////////////////////////////////////////////////
	pthread_join(m_threadHandle, 0);

	lockCriticalSection lockThreadHandle(&m_lockThreadHandle);
	m_bThreadHandleValid = false;

#endif

	return true;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Function that is launched in a separate thread
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
#ifdef PUNTOEXE_WINDOWS

unsigned int __stdcall thread::privateThreadFunction(void* pParameter)

#else

void* thread::privateThreadFunction(void* pParameter)

#endif
{
	// Get the thread object that launched the function
	///////////////////////////////////////////////////////////
	thread* pThread( (thread*)pParameter );

	tThreadId id(thread::getThreadId());

	bool bStopped(false);

	{
		lockCriticalSection lockActiveThreads(&m_lockActiveThreads);
		m_activeThreads[id] = pThread;
	}

	try
	{
		PUNTOEXE_FUNCTION_START(L"thread::privateThreadFunction");

		// Enable the "isRunning" flag
		///////////////////////////////////////////////////////////
		{
			lockCriticalSection lockRunningFlag(&(pThread->m_lockRunningFlag));
			pThread->m_bIsRunning = true;
			pThread->m_bStopped = false;
		}

		// Call the virtual thread function
		///////////////////////////////////////////////////////////
		pThread->threadFunction();

		PUNTOEXE_FUNCTION_END();
	}
	catch(threadStopped& e)
	{
		bStopped = true;
	}
	catch(...)
	{
		exceptionsManager::getMessage();
	}

	{
		lockCriticalSection lockActiveThreads(&m_lockActiveThreads);
		tActiveThreads::iterator findThread(m_activeThreads.find(id) );
		if(findThread != m_activeThreads.end())
		{
			m_activeThreads.erase(findThread);
		}
	}

	// Disable the "isRunning" flag
	///////////////////////////////////////////////////////////
	{
		lockCriticalSection lockRunningFlag(&(pThread->m_lockRunningFlag));
		pThread->m_bIsRunning = false;
		pThread->m_bStopped = bStopped;
	}

	return 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Start the thread's function
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void thread::start()
{
	PUNTOEXE_FUNCTION_START(L"thread::start");

	lockCriticalSection lockThreadHandle(&m_lockThreadHandle);

	// Throw an exception if the thread is already running
	///////////////////////////////////////////////////////////
	if(m_bThreadHandleValid)
	{
		PUNTOEXE_THROW(threadExceptionAlreadyRunning, "Thread already running");
	}

#ifdef PUNTOEXE_WINDOWS
	// Start the thread
	///////////////////////////////////////////////////////////
	unsigned dummy;
	m_threadHandle = (HANDLE)::_beginthreadex(0, 0, thread::privateThreadFunction, this, 0, &dummy);
	if(m_threadHandle == 0)
	{
		PUNTOEXE_THROW(threadExceptionFailedToLaunch, "Failed to launch the thread");
	}
#else
	pthread_attr_t threadAttributes;
	pthread_attr_init(&threadAttributes);
	pthread_attr_setdetachstate(&threadAttributes, PTHREAD_CREATE_JOINABLE);
	int errorCode = pthread_create(&m_threadHandle, &threadAttributes, thread::privateThreadFunction, this);
	pthread_attr_destroy(&threadAttributes);

	if(errorCode != 0)
	{
		PUNTOEXE_THROW(threadExceptionFailedToLaunch, "Failed to launch the thread");
	}
#endif

	m_bThreadHandleValid = true;

	PUNTOEXE_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Send a termination request to the running thread
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void thread::terminate()
{
	lockCriticalSection lockTerminateFlag(&m_lockTerminateFlag);
	m_bTerminate = true;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Called by the thread's function to know if it has to
//  terminate
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool thread::shouldTerminate()
{
	lockCriticalSection lockTerminateFlag(&m_lockTerminateFlag);
	return m_bTerminate;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return true if the thread's function is running
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool thread::isRunning()
{
	lockCriticalSection lockRunningFlag(&m_lockRunningFlag);
	return m_bIsRunning;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return an indentifier for the current thread
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
thread::tThreadId thread::getThreadId()
{
#ifdef PUNTOEXE_WINDOWS
	return (tThreadId)::GetCurrentThreadId();
#else
	pthread_key_t* pKey = getSharedKey();
	void* id = pthread_getspecific(*pKey);
	if(id == 0)
	{
		id = getNextId();
		pthread_setspecific(*pKey, id);
	}
	return id;
#endif
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the thread object related to the thread id
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
thread* thread::getThreadObject(tThreadId id)
{
	lockCriticalSection lockActiveThreads(&m_lockActiveThreads);
	tActiveThreads::const_iterator findThread(m_activeThreads.find(id) );
	if(findThread != m_activeThreads.end())
	{
		return findThread->second;
	}
	return 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Switch to another thread
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void thread::yield()
{
#ifdef PUNTOEXE_WINDOWS // WINDOWS

#if(_WIN32_WINNT>=0x0400)
			SwitchToThread();
#else
			Sleep(0);
#endif

#else // POSIX
			sched_yield();
#endif
}


#ifdef PUNTOEXE_POSIX

pthread_key_t* thread::getSharedKey()
{
	static sharedKey m_key;
	return &(m_key.m_key);
}

void* thread::getNextId()
{
	static char* m_nextId(0);
	static criticalSection m_criticalSection;

	lockCriticalSection lockHere(&m_criticalSection);
	if(++m_nextId == 0)
	{
		m_nextId = (char*)100; // Overflow. Assume that the first created threads live longer
	}
	return (void*)m_nextId;
}

#endif

} // namespace puntoexe
