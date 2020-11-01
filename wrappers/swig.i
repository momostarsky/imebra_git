%module (threads="1") dicomhero


#ifdef SWIGJAVA
    %include <arrays_java.i>
    %include <enums.swg>

    %apply(char *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };
    %apply(char *STRING, size_t LENGTH) { (char* destination, size_t destinationSize) };

        %rename(assign) operator=;
#endif
#ifdef SWIGPYTHON
    %include <cdata.i>
    %include <pybuffer.i>
    %pybuffer_mutable_binary(void *STRING, size_t LENGTH)
    %apply(void *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };
    %apply(void *STRING, size_t LENGTH) { (char* destination, size_t destinationSize) };

        %rename(assign) operator=;

#endif

#ifdef SWIGGO
    %include <cdata.i>
    %include <gostring.swg>

        %typemap(gotype) (char* destination, size_t destinationSize) %{[]byte%}

        %typemap(in) (char* destination, size_t destinationSize) {
         $1 = ($1_ltype)$input.array;
         $2 = $input.len;
        }
    %apply(void *STRING, size_t LENGTH) { (const char *source, size_t sourceSize) };

%insert(cgo_comment_typedefs) %{
#cgo LDFLAGS: -ldicomhero
%}

#endif

#define DICOMHERO_API

%{

#include <dicomhero/dicomhero.h>

%}

%include <stl.i>
%include <std_string.i>

%include <exception.i>
%include <stdint.i>
%include <std_common.i>
%include <std_except.i>
%include <std_vector.i>
%include <std_map.i>


%template(StringsList) std::vector<std::string>;
%template(Groups) std::vector<std::uint16_t>;
%template(TagsIds) std::vector<dicomhero::TagId>;
%template(VOIs) std::vector<dicomhero::VOIDescription>;

%exception {
    try {
        $action
    } catch(const dicomhero::MissingDataElementError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IndexError, error.c_str());
    } catch(const dicomhero::LutError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const dicomhero::StreamError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IOError, error.c_str());
    } catch(const dicomhero::DictionaryError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::CharsetConversionError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const dicomhero::CodecError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_IOError, error.c_str());
    } catch(const dicomhero::DataHandlerError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::DataSetError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::DicomDirError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const dicomhero::ImageError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::TransformError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_ValueError, error.c_str());
    } catch(const dicomhero::MemoryError& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_MemoryError, error.c_str());
    } catch(const std::bad_cast& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_TypeError, error.c_str());
    } catch(const std::runtime_error& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    } catch(const std::exception& e) {
        std::string error(dicomhero::ExceptionsManager::getExceptionTrace());
        SWIG_exception(SWIG_RuntimeError, error.c_str());
    }
}


%include "../library/include/dicomhero/dicomDefinitions.h"
%include "../library/include/dicomhero/tagId.h"
%include "../library/include/dicomhero/definitions.h"
%include "../library/include/dicomhero/memory.h"
%include "../library/include/dicomhero/mutableMemory.h"
%include "../library/include/dicomhero/memoryPool.h"
%include "../library/include/dicomhero/baseStreamInput.h"
%include "../library/include/dicomhero/baseStreamOutput.h"
%include "../library/include/dicomhero/streamReader.h"
%include "../library/include/dicomhero/streamWriter.h"
%include "../library/include/dicomhero/readingDataHandler.h"
%include "../library/include/dicomhero/readingDataHandlerNumeric.h"
%include "../library/include/dicomhero/writingDataHandler.h"
%include "../library/include/dicomhero/writingDataHandlerNumeric.h"
%include "../library/include/dicomhero/lut.h"
%include "../library/include/dicomhero/image.h"
%include "../library/include/dicomhero/overlay.h"
%include "../library/include/dicomhero/tag.h"
%include "../library/include/dicomhero/dataSet.h"
%include "../library/include/dicomhero/codecFactory.h"
%include "../library/include/dicomhero/tcpAddress.h"
%include "../library/include/dicomhero/tcpListener.h"
%include "../library/include/dicomhero/tcpStream.h"
%include "../library/include/dicomhero/pipeStream.h"
%include "../library/include/dicomhero/transform.h"
%include "../library/include/dicomhero/transformHighBit.h"
%include "../library/include/dicomhero/transformsChain.h"
%include "../library/include/dicomhero/modalityVOILUT.h"
%include "../library/include/dicomhero/VOILUT.h"
%include "../library/include/dicomhero/VOIDescription.h"
%include "../library/include/dicomhero/colorTransformsFactory.h"
%include "../library/include/dicomhero/dicomDirEntry.h"
%include "../library/include/dicomhero/dicomDir.h"
%include "../library/include/dicomhero/dicomDictionary.h"
%include "../library/include/dicomhero/drawBitmap.h"
%include "../library/include/dicomhero/fileStreamInput.h"
%include "../library/include/dicomhero/fileStreamOutput.h"
%include "../library/include/dicomhero/memoryStreamInput.h"
%include "../library/include/dicomhero/memoryStreamOutput.h"
%include "../library/include/dicomhero/acse.h"
%include "../library/include/dicomhero/dimse.h"
%include "../library/include/dicomhero/date.h"
%include "../library/include/dicomhero/age.h"
%include "../library/include/dicomhero/patientName.h"
%include "../library/include/dicomhero/uidGeneratorFactory.h"
%include "../library/include/dicomhero/baseUidGenerator.h"
%include "../library/include/dicomhero/randomUidGenerator.h"
%include "../library/include/dicomhero/serialNumberUidGenerator.h"




