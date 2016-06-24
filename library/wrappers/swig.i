%module imebra

#ifdef SWIGJAVA
	%javaconst(1);
	%include <arrays_java.i>
	%include <enums.swg>
	%apply(char *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };
	%apply(char *STRING, size_t LENGTH) { (char* destination, size_t destinationSize) };
	%rename(assign) operator=;
#endif

#define IMEBRA_API

// Declare which methods return an object that should be
// managed by the client.
////////////////////////////////////////////////////////
%newobject imebra::CodecFactory::load;

%newobject imebra::ColorTransformsFactory::getTransform;

%newobject imebra::DataSet::getTag;
%newobject imebra::DataSet::getTagCreate;
%newobject imebra::DataSet::getImage;
%newobject imebra::DataSet::getImageApplyModalityTransform;
%newobject imebra::DataSet::getSequenceItem;
%newobject imebra::DataSet::getLUT;
%newobject imebra::DataSet::getReadingDataHandler;
%newobject imebra::DataSet::getWritingDataHandler;
%newobject imebra::DataSet::getReadingDataHandlerNumeric;
%newobject imebra::DataSet::getWritingDataHandlerNumeric;
%newobject imebra::DataSet::getReadingDataHandlerRaw;
%newobject imebra::DataSet::getWritingDataHandlerRaw;
%newobject imebra::DataSet::getAge;
%newobject imebra::DataSet::getDate;

%newobject imebra::DicomDir::getNewEntry;
%newobject imebra::DicomDir::getFirstRootEntry;
%newobject imebra::DicomDir::updateDataSet;

%newobject imebra::DicomDirEntry::getEntryDataSet;
%newobject imebra::DicomDirEntry::getNextEntry;
%newobject imebra::DicomDirEntry::getFirstChildEntry;

%newobject imebra::DrawBitmap::getBitmap;

%newobject imebra::Image::getReadingDataHandler;
%newobject imebra::Image::getWritingDataHandler;

%newobject imebra::LUT::getReadingDataHandler;
%newobject imebra::LUT::getReadingDataHandler;
%newobject imebra::LUT::getReadingDataHandler;
%newobject imebra::LUT::getReadingDataHandler;

%newobject imebra::ReadingDataHandlerNumeric::getMemory;

%newobject imebra::Tag::getReadingDataHandler;
%newobject imebra::Tag::getWritingDataHandler;
%newobject imebra::Tag::getReadingDataHandlerNumeric;
%newobject imebra::Tag::getReadingDataHandlerRaw;
%newobject imebra::Tag::getWritingDataHandlerNumeric;
%newobject imebra::Tag::getWritingDataHandlerRaw;
%newobject imebra::Tag::getStreamReader;
%newobject imebra::Tag::getStreamWriter;
%newobject imebra::Tag::getSequenceItem;

%newobject imebra::Transform::allocateOutputImage;

%newobject imebra::WritingDataHandlerNumeric::getMemory;

%include <std_string.i>
%include <std_wstring.i>

%include <exception.i>
%include <stdint.i>
%include <std_except.i>
%include <std_vector.i>
%include <std_map.i>

%apply int[] {int *};
%template(FileParts) std::vector<std::string>;
%template(Groups) std::vector<std::uint16_t>;
%template(TagsIds) std::vector<imebra::TagId>;
%template(VOIs) std::vector<imebra::VOIDescription>;

%apply(const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes, char *STRING, size_t LENGTH)
    { (const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes, char* buffer, size_t bufferSize) };


%{
#include "../include/imebra/imebra.h"
%}

%include "../include/imebra/tagsEnumeration.h"
%include "../include/imebra/definitions.h"
%include "../include/imebra/tagId.h"
%include "../include/imebra/readMemory.h"
%include "../include/imebra/readWriteMemory.h"
%include "../include/imebra/memoryPool.h"
%include "../include/imebra/baseStreamInput.h"
%include "../include/imebra/baseStreamOutput.h"
%include "../include/imebra/streamReader.h"
%include "../include/imebra/streamWriter.h"
%include "../include/imebra/readingDataHandler.h"
%include "../include/imebra/readingDataHandlerNumeric.h"
%include "../include/imebra/writingDataHandler.h"
%include "../include/imebra/writingDataHandlerNumeric.h"
%include "../include/imebra/lut.h"
%include "../include/imebra/image.h"
%include "../include/imebra/tag.h"
%include "../include/imebra/dataSet.h"
%include "../include/imebra/codecFactory.h"
%include "../include/imebra/transform.h"
%include "../include/imebra/transformHighBit.h"
%include "../include/imebra/transformsChain.h"
%include "../include/imebra/modalityVOILUT.h"
%include "../include/imebra/VOILUT.h"
%include "../include/imebra/colorTransformsFactory.h"
%include "../include/imebra/dicomDirEntry.h"
%include "../include/imebra/dicomDir.h"
%include "../include/imebra/dicomDictionary.h"
%include "../include/imebra/drawBitmap.h"
%include "../include/imebra/exceptions.h"
%include "../include/imebra/fileStreamInput.h"
%include "../include/imebra/fileStreamOutput.h"
%include "../include/imebra/memoryStreamInput.h"
%include "../include/imebra/memoryStreamOutput.h"



