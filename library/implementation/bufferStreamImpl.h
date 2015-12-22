///////////////////////////////////////////////////////////
//  bufferStream.h
//  Declaration of the Class bufferStream
///////////////////////////////////////////////////////////

#if !defined(imebraBufferStream_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
#define imebraBufferStream_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_

#include "memoryStreamImpl.h"
#include "dataHandlerNumericImpl.h"

namespace puntoexe
{

namespace imebra
{

/// \addtogroup group_dataset
///
/// @{

class bufferStream: public memoryStream
{
public:
	bufferStream(std::shared_ptr<handlers::dataHandlerRaw> pDataHandler):
	  memoryStream(pDataHandler->getMemory()),
	  m_pDataHandler(pDataHandler){}
protected:

	std::shared_ptr<handlers::dataHandlerRaw> m_pDataHandler;
};

/// @}

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraBufferStream_DE3F98A9_664E_47c0_A29B_B681F9AEB118__INCLUDED_)
