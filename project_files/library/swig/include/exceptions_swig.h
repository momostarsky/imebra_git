/*
$fileHeader$
*/

/*! \file exceptions_swig.h
	\brief Declaration of the exceptio classes for SWIG.

*/

#ifndef EXCEPTIONS_SWIG_H
#define EXCEPTIONS_SWIG_H

#ifndef SWIG
#include "../../imebra/include/imebra.h"

#define CATCH_IMEBRA_EXCEPTIONS \
	catch(const puntoexe::streamExceptionOpen& e) \
	{\
	throw ::streamExceptionOpen(e.what()); \
	}\
	catch(const puntoexe::streamExceptionRead& e) \
	{\
	throw ::streamExceptionRead(e.what()); \
	}\
	catch(const puntoexe::streamExceptionWrite& e) \
	{\
	throw ::streamExceptionWrite(e.what()); \
	}\
	catch(const puntoexe::streamExceptionClose& e) \
	{\
	throw ::streamExceptionClose(e.what()); \
	}\
	catch(const puntoexe::streamException& e) \
	{\
	throw ::streamException(e.what()); \
	}\
	catch(const puntoexe::imebra::dataSetExceptionDifferentFormat& e) \
	{\
	throw ::dataSetExceptionDifferentFormat(e.what()); \
	}\
	catch(const puntoexe::imebra::dataSetExceptionUnknownTransferSyntax& e) \
	{\
	throw ::dataSetExceptionUnknownTransferSyntax(e.what()); \
	}\
	catch(const puntoexe::imebra::dataSetExceptionWrongFrame& e) \
	{\
	throw ::dataSetExceptionWrongFrame(e.what()); \
	}\
	catch(const puntoexe::imebra::dataSetExceptionOldFormat& e) \
	{\
	throw ::dataSetExceptionOldFormat(e.what()); \
	}\
	catch(const puntoexe::imebra::dataSetImageDoesntExist& e) \
	{\
	throw ::dataSetCorruptedOffsetTable(e.what()); \
	}\
	catch(const puntoexe::imebra::dataSetCorruptedOffsetTable& e) \
	{\
	throw ::dataSetCorruptedOffsetTable(e.what()); \
	}\
	catch(const puntoexe::imebra::dataSetException& e) \
	{\
	throw ::dataSetException(e.what()); \
	}\
	catch(const puntoexe::imebra::dicomDirCircularReferenceException& e) \
	{\
	throw ::dicomDirCircularReferenceException(e.what()); \
	}\
	catch(const puntoexe::imebra::dicomDirUnknownDirectoryRecordType& e) \
	{\
	throw ::dicomDirUnknownDirectoryRecordType(e.what()); \
	}\
	catch(const puntoexe::imebra::dicomDirException& e) \
	{\
	throw ::dicomDirException(e.what()); \
	}


#endif

/// \addtogroup group_swig_bindings
/// @{

class imebraException
{
public:
	imebraException(const std::string& message);
	std::string what();
	std::wstring stack();
#ifndef SWIG
private:
	std::string m_what;
	std::wstring m_stack;
#endif
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief The base exception for all the exceptions
///         thrown by the function in baseStream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class streamException: public imebraException
{
public:
	streamException(const std::string& message): imebraException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when the stream cannot be
///         open.
///
///////////////////////////////////////////////////////////
class streamExceptionOpen : public streamException
{
public:
	streamExceptionOpen(const std::string& message): streamException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when there is an error during
///         the read phase.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class streamExceptionRead : public streamException
{
public:
	streamExceptionRead(const std::string& message): streamException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when there is an error during
///         the write phase.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class streamExceptionWrite : public streamException
{
public:
	streamExceptionWrite(const std::string& message): streamException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when there are problems during
///         the closure of the stream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class streamExceptionClose : public streamException
{
public:
	streamExceptionClose(const std::string& message): streamException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the dataSet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataSetException: public imebraException
{
public:
	dataSetException(const std::string& message): imebraException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the application is
///         trying to store an image in the dataSet but
///         the dataSet already stores other images that
///         have different attributes.
///
/// The exception is usually thrown by dataSet::setImage().
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataSetExceptionDifferentFormat: public dataSetException
{
public:
	dataSetExceptionDifferentFormat(const std::string& message): dataSetException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown
///         transfer syntax is being used while reading or
///         writing a stream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataSetExceptionUnknownTransferSyntax: public dataSetException
{
public:
	dataSetExceptionUnknownTransferSyntax(const std::string& message): dataSetException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the application
///         is storing several images in the dataSet but
///         doesn't store them in the right order.
///
/// The application must store the images following the
///  frame order, without skipping frames.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataSetExceptionWrongFrame: public dataSetException
{
public:
	dataSetExceptionWrongFrame(const std::string& message): dataSetException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the application
///         is trying to store an image in an old Dicom
///         format.
///
/// The application cannot store images in old Dicom
///  formats (before Dicom3).
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataSetExceptionOldFormat: public dataSetException
{
public:
	dataSetExceptionOldFormat(const std::string& message): dataSetException(message){}
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the an image that
///         doesn't exist is requested.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataSetImageDoesntExist: public dataSetException
{
public:
	/// \brief Build a dataSetImageDoesntExist exception
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	dataSetImageDoesntExist(const std::string& message): dataSetException(message){}
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the basic offset
///         table is corrupted.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dataSetCorruptedOffsetTable: public dataSetException
{
public:
	/// \brief Build a dataSetImageDoesntExist exception
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	dataSetCorruptedOffsetTable(const std::string& message): dataSetException(message){}
};



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Base class from which the exceptions thrown
///         by directoryRecord and dicomDir derive.
///
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dicomDirException: public imebraException
{
public:
	/// \brief Build a dicomDirException exception.
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	dicomDirException(const std::string& message): imebraException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when a call to
///        dicomDir::setFirstRootRecord() or
///        directoryRecord::setNextRecord() or
///        directoryRecord::setFirstChildRecord() or
///        directoryRecord::setReferencedRecord() causes
///        a circular reference between directoryRecord
///        objects.
///
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dicomDirCircularReferenceException: public dicomDirException
{
public:
	/// \brief Build a dicomDirCircularReferenceException
	///         exception.
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	dicomDirCircularReferenceException(const std::string& message): dicomDirException(message){}
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when an unknown record type
///        is detected in directoryRecord::getType(),
///        directoryRecord::getTypeString(),
///        directoryRecord::setType() or
///        directoryRecord::setTypeString().
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class dicomDirUnknownDirectoryRecordType: public dicomDirException
{
public:
	/// \brief Build a dicomDirUnknownDirectoryRecordType
	///         exception.
	///
	/// @param message the message to store into the exception
	///
	///////////////////////////////////////////////////////////
	dicomDirUnknownDirectoryRecordType(const std::string& message): dicomDirException(message){}
};

class dicomDirNullRecord: public dicomDirException
{
public:
	dicomDirNullRecord(const std::string& message): dicomDirException(message){}
};

///@}

#endif // EXCEPTIONS_SWIG_H
