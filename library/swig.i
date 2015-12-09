%rename(assign) operator=;

%module imebra

%include <std_string.i>
%include <std_wstring.i>
%include <arrays_java.i>
%include <exception.i>
%include <stdint.i>

%apply(char *STRING, int LENGTH) { (char *buffer, int bufferSize) };
%apply int[] {int *};

%apply(int totalWidthPixels, int totalHeightPixels, int visibleTopLeftX, int visibleTopLeftY, int visibleBottomRightX, int visibleBottomRightY, int *INT, int LENGTH)
    { (int totalWidthPixels, int totalHeightPixels, int visibleTopLeftX, int visibleTopLeftY, int visibleBottomRightX, int visibleBottomRightY, int *buffer, int bufferSize) };


%{
#include "include/imebra/dataSet.h"
#include "include/imebra/baseStream.h"
#include "include/imebra/stream.h"
#include "include/imebra/streamReader.h"
#include "include/imebra/streamWriter.h"
#include "include/imebra/codecFactory.h"
#include "include/imebra/dicomDir.h"
#include "include/imebra/dataHandler.h"
#include "include/imebra/image.h"
#include "include/imebra/transform.h"
#include "include/imebra/transformsChain.h"
#include "include/imebra/colorTransformsFactory.h"
#include "include/imebra/modalityVOILUT.h"
#include "include/imebra/VOILUT.h"
#include "include/imebra/memory.h"
%}


%exception {
    try {
        $action
    } catch(puntoexe::streamExceptionOpen) {
        SWIG_exception(SWIG_IOError, "The stream cannot be opened");
    } catch(puntoexe::streamExceptionRead) {
        SWIG_exception(SWIG_IOError, "Error while reading the stream");
    } catch(puntoexe::streamExceptionWrite) {
        SWIG_exception(SWIG_IOError, "Error while writing the stream");
    } catch(puntoexe::streamExceptionClose) {
        SWIG_exception(SWIG_IOError, "The stream cannot be closed");
    } catch(puntoexe::streamException e) {
        SWIG_exception(SWIG_IOError, e.what());
    } catch(puntoexe::imebra::dataSetExceptionDifferentFormat) {
        SWIG_exception(SWIG_ValueError, "The dataset already contains an image in a different format");
    } catch(puntoexe::imebra::dataSetExceptionUnknownTransferSyntax) {
        SWIG_exception(SWIG_ValueError, "Unknown Transfer Syntax");
    } catch(puntoexe::imebra::dataSetExceptionWrongFrame) {
        SWIG_exception(SWIG_ValueError, "The frames must be stored in ordered sequence");
    } catch(puntoexe::imebra::dataSetExceptionOldFormat) {
        SWIG_exception(SWIG_ValueError, "Imebra cannot save in old dicom format");
    } catch(puntoexe::imebra::dataSetImageDoesntExist) {
        SWIG_exception(SWIG_IndexError, "The requested frame doesn't exist");
    } catch(puntoexe::imebra::dataSetCorruptedOffsetTable) {
        SWIG_exception(SWIG_AttributeError, "The dataset offset table is corrupted");
    } catch(puntoexe::imebra::dataSetException e) {
        SWIG_exception(SWIG_ValueError, e.what());
    } catch(puntoexe::imebra::dicomDirCircularReferenceException) {
        SWIG_exception(SWIG_ValueError, "The DicomDir structure contains a circular reference");
    } catch(puntoexe::imebra::dicomDirUnknownDirectoryRecordType) {
        SWIG_exception(SWIG_ValueError, "The DicomDir record type is unknown");
    } catch(puntoexe::imebra::dicomDirException e) {
        SWIG_exception(SWIG_ValueError, e.what());
    } catch(std::runtime_error) {
        SWIG_exception(SWIG_RuntimeError, "Unknown runtime error");
    } catch(std::logic_error) {
        SWIG_exception(SWIG_NullReferenceError, "Null reference");
    } catch(std::exception) {
        SWIG_exception(SWIG_UnknownError, "Unknown error");
    }
}

%include "dataSet_swig.h"
%include "baseStream_swig.h"
%include "stream_swig.h"
%include "streamReader_swig.h"
%include "streamWriter_swig.h"
%include "codecFactory_swig.h"
%include "dicomDir_swig.h"
%include "dataHandler_swig.h"
%include "image_swig.h"
%include "transform_swig.h"
%include "transformsChain_swig.h"
%include "colorTransformsFactory_swig.h"
%include "modalityVOILUT_swig.h"
%include "VOILUT_swig.h"
%include "memory_swig.h"
%include "drawBitmap_swig.h"
