%module imebraNet

%{
	/* Includes the header in the wrapper code */
	#include "../imebra/include/imebra.h"
%}
	%include "../base/include/configuration.h"
	%include "../base/include/baseObject.h"
	%include "../base/include/baseStream.h"
	%include "../base/include/exception.h"
	%include "../base/include/memory.h"
	%include "../base/include/memoryStream.h"
	%include "../base/include/stream.h"
	%include "../base/include/streamController.h"
	%include "../base/include/streamReader.h"
	%include "../base/include/streamWriter.h"
	
	%include "../imebra/include/charsetsList.h"
	%include "../imebra/include/dataHandler.h"
	%include "../imebra/include/dataHandlerNumeric.h"
	%include "../imebra/include/buffer.h"
	%include "../imebra/include/codec.h"
	%include "../imebra/include/codecFactory.h"
	%include "../imebra/include/transform.h"
	%include "../imebra/include/transformBuffers.h"
	%include "../imebra/include/colorTransform.h"
	%include "../imebra/include/colorTransformsFactory.h"
	
	%include "../imebra/include/data.h"
	%include "../imebra/include/dataCollection.h"
	%include "../imebra/include/dataGroup.h"
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
 
	%template(signedByteDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<imbxUint8>;
	%template(unsignedByteDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<imbxInt8>;
	%template(signedWordDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<imbxUint16>;
	%template(unsignedWordDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<imbxInt16>;
	%template(signedDWordDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<imbxUint32>;
	%template(unsignedDWordDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<imbxInt32>;
	%template(doubleDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<double>;
	%template(floatDataHandler) puntoexe::imebra::handlers::dataHandlerNumeric<float>;

	%template(ptrBuffer) puntoexe::ptr<puntoexe::imebra::buffer>;
	%template(ptrCodec) puntoexe::ptr<puntoexe::imebra::codecs::codec>;
	%template(ptrCodecFactory) puntoexe::ptr<puntoexe::imebra::codecs::codecFactory>;
	%template(ptrColorTransformsFactory) puntoexe::ptr<puntoexe::imebra::transforms::colorTransforms::colorTransformsFactory>;
	%template(ptrTransform) puntoexe::ptr<puntoexe::imebra::transforms::transform>;
	%template(ptrData) puntoexe::ptr<puntoexe::imebra::data>;
	%template(ptrDataGroup) puntoexe::ptr<puntoexe::imebra::dataGroup>;
	%template(ptrDataSet) puntoexe::ptr<puntoexe::imebra::dataSet>;
	%template(ptrDataHandler) puntoexe::ptr<puntoexe::imebra::handlers::dataHandler>;
	%template(imageHandler) dataHandlerNumeric<imbxInt32>;
	%template(ptrImageHandler) puntoexe::ptr<puntoexe::imebra::handlers::dataHandlerNumeric<imbxInt32> >;
	%template(ptrImage) puntoexe::ptr<puntoexe::imebra::image>;
	%template(ptrLut) puntoexe::ptr<puntoexe::imebra::lut>;
	%template(ptrWaveform) puntoexe::ptr<puntoexe::imebra::waveform>;
	%template(ptrBaseStream) puntoexe::ptr<puntoexe::baseStream>;
	%template(ptrStreamController) puntoexe::ptr<puntoexe::streamController>;
	%template(ptrMemory) puntoexe::ptr<puntoexe::memory>;
	%template(ptrStream) puntoexe::ptr<puntoexe::stream>;

