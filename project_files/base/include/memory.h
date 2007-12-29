/*
$fileHeader$
*/

/*! \file memory.h
    \brief Declaration of the memory manager and the memory class.

*/

#if !defined(imebraMemory_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraMemory_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include "baseObject.h"
#include "criticalSection.h"
#include <list>
#include <map>
#include <memory>


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

typedef std::basic_string<imbxUint8> stringUint8;

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class is used to supply a reference counter
///         to a string of bytes.
///
/// New instances of this class should be obtained through
///  the class \ref memoryPool; 
///  call \ref memoryPool::getMemory() in order to
///  obtain a new instance of memory.
///
/// This class is usually used by \ref imebra::buffer 
///  objects to store the tags values.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class memory : public baseObject
{
public:
	memory();

	/// \brief Return a pointer to the string of bytes.
	///
	/// Please note that the string of bytes may be detached
	///  from this class by a call to attach() or detach().
	///
	/// @return     a pointer to the string of bytes used by
	///              the memory object
	///
	///////////////////////////////////////////////////////////
	stringUint8* getStringPointer();

	/// \brief Detach a string of bytes from the memory object.
	///
	/// Subsequent calls to a function of this class will
	///  cause an allocation of a new string (except for
	///  getStringPointer() that will return 0).
	///
	/// @return a pointer to the detached string of bytes
	///
	///////////////////////////////////////////////////////////
	stringUint8* detach();

	/// \brief Attach a string of bytes to the memory object.
	///
	/// The previously attached string will be deleted.
	///
	/// @param pString a pointer to the string of bytes to
	///                 attach to the memory object
	///
	///////////////////////////////////////////////////////////
	void attach(stringUint8* pString);

	/// \brief Copy the content of the string of bytes managed
	///         by another memory object into the string of 
	///         bytes managed by the memory object for which
	///         the function is called.
	///
	/// If the object doesn't have any managed string, then a
	///  new string of bytes is created and attached to the
	///  memory object.
	///
	/// @param sourceMemory a pointer to the memory object from
	///                      which the data has to be copied
	///
	///////////////////////////////////////////////////////////
	void copyFrom(ptr<memory> sourceMemory);

	/// \brief Clear the content of the managed string of 
	///         bytes.
	///
	///////////////////////////////////////////////////////////
	void clear();

	/// \brief Return the size, in bytes, of the managed
	///         string of bytes.
	///
	/// @return the size of the managed string of bytes, in
	///          bytes, or 0 if there isn't any string managed
	///          by the memory object
	///
	///////////////////////////////////////////////////////////
	imbxUint32 size();

	/// \brief Return true if the managed string of bytes is
	///         empty (its size is 0) or if there isn't any
	///         string of bytes managed by the memory object.
	///
	/// @return true if the managed string of bytes is empty
	///          (its size is 0) or if there isn't any string
	///          of bytes managed by the memory object (a
	///          call to getStringPointer() returns 0),
	///          otherwise it returns false
	///
	///////////////////////////////////////////////////////////
	bool empty();

	/// \brief Copy the specified array of bytes into the
	///         managed string.
	///
	/// If the object doesn't have any managed string, then a
	///  new string of bytes is created and attached to the
	///  memory object.
	///
	/// @param pSource      a pointer to the buffer containing
	///                      the bytes to be copied
	/// @param sourceLength the number of bytes stored in the
	///                      buffer pSource and to be copied
	///                      into the managed string of bytes.
	///
	///////////////////////////////////////////////////////////
	void assign(imbxUint8* pSource, imbxUint32 sourceLength);

	/// \internal
	/// \brief This function is called by 
	///         \ref baseObject::release() before deleting
	///         the memory object.
	/// 
	/// The function tries to move the memory object into
	///  the memory pool (puntoexe::memoryPool), so the memory
	///  can be reused without being reallocated.
	///
	/// See \ref memoryPool for more information about
	///  this feature.
	///
	///////////////////////////////////////////////////////////
	virtual bool preDelete();

protected:
	std::auto_ptr<stringUint8> m_pMemoryBuffer;
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Stores unused memory objects (see 
///         \ref puntoexe::memory) so they can be reused 
///         when needed.
///
/// One instance of this class is statically allocated
///  by the library. Don't allocate new instance of this
///  class.
///
/// To obtain a pointer to the statically allocated 
///  instance of memoryPool call the static function
///  memoryPool::getMemoryPool().
///
/// When the reference counter of a \ref memory object
///  reaches 0, the memory object may not be deleted 
///  immediatly; infact, if the memory managed by the 
///  memory pool matches some predefined requisites, the
///  memory object is temporarily stored in the memory
///  pool and reused when a request for a \ref memory
///  object is received.
///
/// The memory pool tries to reuse the \ref memory
///  object that manages an amount of memory similar to
///  the amount of memory requested through getMemory().
///
/// When a memory object is not used for a while then it
///  is deleted permanently.
///
///////////////////////////////////////////////////////////
class memoryPool
{
	friend class memory;
protected:
#if(!defined IMEBRA_MEMORY_POOL_SLOTS)
	#define IMEBRA_MEMORY_POOL_SLOTS 256
#endif
#if(!defined IMEBRA_MEMORY_POOL_MAX_SIZE)
	#define IMEBRA_MEMORY_POOL_MAX_SIZE 20000000
#endif
#if(!defined IMEBRA_MEMORY_POOL_MIN_SIZE)
	#define IMEBRA_MEMORY_POOL_MIN_SIZE 1024
#endif

	imbxUint32 m_memorySize[IMEBRA_MEMORY_POOL_SLOTS];
	memory*    m_memoryPointer[IMEBRA_MEMORY_POOL_SLOTS];
	imbxUint32 m_firstUsedCell;
	imbxUint32 m_firstFreeCell;

	imbxUint32 m_actualSize;

public:
	memoryPool(): m_actualSize(0){}

	virtual ~memoryPool();

	/// \brief Retrieve a new or reused 
	///         \ref puntoexe::memory object.
	///
	/// The function look for an unused \ref memory object
	///  that has a managed string with the same size of the
	///  specified one and tries to reuse it.
	///
	/// If none of the unused objects has the requested
	///  size, then a new memory object is created and 
	///  returned.
	///
	/// @param requestedSize the size that the string managed
	///                       by the returned memory object
	///                       must have
	/// @return              a pointer to the reused or new
	///                       memory object: in any case the
	///                       reference counter of the returned
	///                       object will be 1
	///
	///////////////////////////////////////////////////////////
	memory* getMemory(imbxUint32 requestedSize);

	/// \brief Discard all the currently unused memory.
	///
	///////////////////////////////////////////////////////////
	void flush();

	/// \brief Get a pointer to the statically allocated 
	///         instance of memoryPool.
	///
	/// @return a pointer to the statically allocated instance
	///          of memoryPool
	///
	///////////////////////////////////////////////////////////
	static memoryPool* getMemoryPool();

protected:
	/// \internal
	/// \brief Called by \ref memory before the object
	///         is deleted.
	///
	/// This function returns true if the memory object will
	///  be reused and shouldn't be deleted.
	///
	/// @param pMemoryToReuse a pointer to the memory object
	///                        that call this function
	/// @return               true if the memory object has
	///                        been saved in the memory pool
	///                        and will be reused, false
	///                        otherwise
	///
	///////////////////////////////////////////////////////////
	bool reuseMemory(memory* pMemoryToReuse);

	criticalSection m_criticalSection;

};

} // namespace puntoexe

#endif // !defined(imebraMemory_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
