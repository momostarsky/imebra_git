%rename(assign) operator=;

%module imebra

#define IMEBRA_API

%include <std_string.i>
%include <std_wstring.i>
%include <arrays_java.i>
%include <exception.i>
%include <stdint.i>
%include std_except.i
%apply(char *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };
%apply(char *STRING, size_t LENGTH) { (char* destination, size_t destinationSize) };
%apply int[] {int *};

%apply(int totalWidthPixels, int totalHeightPixels, int visibleTopLeftX, int visibleTopLeftY, int visibleBottomRightX, int visibleBottomRightY, int *INT, int LENGTH)
    { (int totalWidthPixels, int totalHeightPixels, int visibleTopLeftX, int visibleTopLeftY, int visibleBottomRightX, int visibleBottomRightY, int *buffer, int bufferSize) };


%{
#include "include/imebra/imebra.h"
%}

%include "include/imebra/definitions.h"
%include "include/imebra/readMemory.h"
%include "include/imebra/readWriteMemory.h"
%include "include/imebra/memoryPool.h"
%include "include/imebra/baseStreamInput.h"
%include "include/imebra/baseStreamOutput.h"
%include "include/imebra/streamReader.h"
%include "include/imebra/streamWriter.h"
%include "include/imebra/readingDataHandler.h"
%include "include/imebra/readingDataHandlerNumeric.h"
%include "include/imebra/writingDataHandler.h"
%include "include/imebra/writingDataHandlerNumeric.h"
%include "include/imebra/tagId.h"
%include "include/imebra/tagsEnumeration.h"
%include "include/imebra/tagContent.h"
%include "include/imebra/image.h"
%include "include/imebra/dataSet.h"
%include "include/imebra/codecFactory.h"
%include "include/imebra/transform.h"
%include "include/imebra/transformHighBit.h"
%include "include/imebra/transformsChain.h"
%include "include/imebra/modalityVOILUT.h"
%include "include/imebra/VOILUT.h"
%include "include/imebra/colorTransformsFactory.h"
%include "include/imebra/dicomDirEntry.h"
%include "include/imebra/dicomDir.h"
%include "include/imebra/dicomDictionary.h"
%include "include/imebra/drawBitmap.h"
//%include "include/imebra/exceptions.h"
%include "include/imebra/fileStreamInput.h"
%include "include/imebra/fileStreamOutput.h"
%include "include/imebra/memoryStreamInput.h"
%include "include/imebra/memoryStreamOutput.h"


