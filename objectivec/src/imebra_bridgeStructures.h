#if !defined(imebraObjcBridgeStructures__INCLUDED_)
#define imebraObjcBridgeStructures__INCLUDED_

#include <imebra/imebra.h>
#import "imebra_nserror.h"
#import "imebra_strings.h"
#import <imebraobjc/imebra.h>

#define castWritingDataHandler(dataHandler) ((imebra::WritingDataHandler*)dataHandler)
#define m_pWritingDataHandler castWritingDataHandler(m_pWritingDataHandlerVoidPointer)

#endif // imebraObjcBridgeStructures__INCLUDED_


