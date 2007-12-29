%module imebra

%{
	/* Includes the header in the wrapper code */
	#include "../base/include/charsetConversion.h"
	#include "../base/include/thread.h"
	#include "../base/include/criticalSection.h"
%}
	%include "../base/include/configuration.h"
	%include "../base/include/configuration.h"
	%include "../base/include/baseObject.h"
	%include "../imebra/include/dataHandler.h"
	%include "../imebra/include/dataHandlerNumeric.h"

	%include "../base/include/baseStream.h"
	%include "../base/include/exception.h"
	%include "../base/include/memory.h"
	%include "../base/include/memoryStream.h"
	%include "../base/include/stream.h"
	%include "../base/include/streamController.h"
	%include "../base/include/streamReader.h"
	%include "../base/include/streamWriter.h"
	
	%include "../imebra/include/buffer.h"
	%include "../imebra/include/codec.h"
	%include "../imebra/include/codecFactory.h"
	%include "../imebra/include/transform.h"
	%include "../imebra/include/colorTransform.h"
	%include "../imebra/include/colorTransformsFactory.h"
	
	%include "../imebra/include/dataSet.h"
	%include "../imebra/include/dicomCodec.h"
	%include "../imebra/include/dicomDict.h"
	%include "../imebra/include/drawBitmap.h"
	%include "../imebra/include/image.h"
	%include "../imebra/include/jpegCodec.h"
	%include "../imebra/include/LUT.h"
	%include "../imebra/include/modalityVOILUT.h"
	%include "../imebra/include/transaction.h"
	%include "../imebra/include/transformsChain.h"
	%include "../imebra/include/transformHighBit.h"
 
 