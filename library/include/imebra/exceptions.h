#if !defined(imebraExceptions__INCLUDED_)
#define imebraExceptions__INCLUDED_

#include <stdexcept>
#include <string>
#include "definitions.h"

namespace imebra
{

class IMEBRA_API ExceptionsManager
{
public:
    static std::string getExceptionTrace();
};


///
/// \brief This is the base class for the exceptions thrown by the LUT class.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API LutError: public std::runtime_error
{
public:
    LutError(const std::string& message);
};


///
/// \brief This exception is thrown by the LUT class when the wrong index or
///        id is specified as a parameter.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API LutWrongIndexError: public LutError
{
public:
    LutWrongIndexError(const std::string& message);
};


///
/// \brief This exception is thrown by the lut class when the the LUT
///        information is corrupted.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API LutCorruptedError: public LutError
{
public:
    LutCorruptedError(const std::string& message);
};

class IMEBRA_API MissingDataElementError: public std::runtime_error
{
public:
    MissingDataElementError(const std::string& message);
};

class IMEBRA_API MissingGroupError: public MissingDataElementError
{
public:
    MissingGroupError(const std::string& message);
};

class IMEBRA_API MissingTagError: public MissingDataElementError
{
public:
    MissingTagError(const std::string& message);
};

class IMEBRA_API MissingBufferError: public MissingDataElementError
{
public:
    MissingBufferError(const std::string& message);
};

class IMEBRA_API MissingItemError: public MissingDataElementError
{
public:
    MissingItemError(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief The base exception for all the exceptions
///         thrown by the function in baseStream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API StreamError: public std::runtime_error
{
public:
    StreamError(const std::string& message);
};


///
/// \brief Exception thrown when the stream cannot be open.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamOpenError : public StreamError
{
public:
    StreamOpenError(const std::string& message);
};


///
/// \brief Exception thrown when there is an error during the read phase.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamReadError : public StreamError
{
public:
    StreamReadError(const std::string& message);
};


///
/// \brief Exception thrown when there is an error during the write phase.
///
///////////////////////////////////////////////////////////////////////////////

class IMEBRA_API StreamWriteError : public StreamError
{
public:
    StreamWriteError(const std::string& message);
};


///
/// \brief Exception thrown when there are problems while closing of the
///        stream.
///
///////////////////////////////////////////////////////////////////////////////
class IMEBRA_API StreamCloseError : public StreamError
{
public:
    StreamCloseError(const std::string& message);
};


class IMEBRA_API DictionaryError: public std::runtime_error
{
public:
    DictionaryError(const std::string& message);
};

class IMEBRA_API DictionaryUnknownTagError: public DictionaryError
{
public:
    DictionaryUnknownTagError(const std::string& message);
};

class IMEBRA_API DictionaryUnknownDataTypeError: public DictionaryError
{
public:
    DictionaryUnknownDataTypeError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief Base class for the exceptions thrown by
///         charsetConversion.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CharsetConversionError: public std::runtime_error
{
public:
    CharsetConversionError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the requested charset
///         is not supported by the DICOM standard.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CharsetConversionNoTableError: public CharsetConversionError
{
public:
    CharsetConversionNoTableError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the requested charset
///         is not supported by the system.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CharsetConversionNoSupportedTableError: public CharsetConversionError
{
public:
    CharsetConversionNoSupportedTableError(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the class charsetsList.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API CharsetsListError: public std::runtime_error
{
public:
    CharsetsListError(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when a conversion from
///         an unicode string causes the dicom dataSet
///         to change its default charset.
///
/// For instace, the default charset is ISO IR 6 but a
///  value written by the application in one tag causes
///  the default charset to switch to ISO 2022 IR 100.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API CharsetListDiffDefaultError: public CharsetsListError
{
public:
    CharsetListDiffDefaultError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the codec derived classes.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CodecError: public std::runtime_error
{
public:
    /// \brief Build a codec exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    CodecError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the file being
///         parsed is not valid for the codec.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CodecWrongFormatError: public CodecError
{
public:
    /// \brief Build a codecExceptionWrongFormat exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    CodecWrongFormatError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the file being
///         parsed is corrupted.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CodecCorruptedFileError: public CodecError
{
public:
    /// \brief Build a codecExceptionCorruptedFile exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    CodecCorruptedFileError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the transfer
///         syntax is not recognized by the codec.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CodecWrongTransferSyntaxError: public CodecError
{
public:
    /// \brief Build a codecExceptionWrongTransferSyntax
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    CodecWrongTransferSyntaxError(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the codec reads
///         a file that contains an image that is too big
///         according to the codecFactory settings.
///
/// Consider using codecFactory::setMaximumImageSize()
///  to change the allowed maximum image size.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CodecImageTooBigError: public CodecError
{
public:
    /// \brief Build a codecExceptionImageTooBig
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    CodecImageTooBigError(const std::string& message);
};


class IMEBRA_API DataHandlerError: public std::runtime_error
{
public:
    DataHandlerError(const std::string& message);
};

class IMEBRA_API DataHandlerDeniedConversionError: public DataHandlerError
{
public:
    DataHandlerDeniedConversionError(const std::string& message);
};

class IMEBRA_API DataHandlerConversionError: public DataHandlerError
{
public:
    DataHandlerConversionError(const std::string& message);
};

class IMEBRA_API DataHandlerCorruptedBufferError: public DataHandlerError
{
public:
    DataHandlerCorruptedBufferError(const std::string& message);
};

class IMEBRA_API DataHandlerInvalidDataError: public DataHandlerError
{
public:
    DataHandlerInvalidDataError(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the dataSet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API DataSetError: public std::runtime_error
{
public:
    DataSetError(const std::string& message);
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
class IMEBRA_API DataSetDifferentFormatError: public DataSetError
{
public:
    DataSetDifferentFormatError(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown
///         transfer syntax is being used while reading or
///         writing a stream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API DataSetUnknownTransferSyntaxError: public DataSetError
{
public:
    DataSetUnknownTransferSyntaxError(const std::string& message);
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
class IMEBRA_API DataSetWrongFrameError: public DataSetError
{
public:
    DataSetWrongFrameError(const std::string& message);
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
class IMEBRA_API DataSetOldFormatError: public DataSetError
{
public:
    DataSetOldFormatError(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the an image that
///         doesn't exist is requested.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API DataSetImageDoesntExistError: public DataSetError
{
public:
    /// \brief Build a dataSetImageDoesntExist exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    DataSetImageDoesntExistError(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the basic offset
///         table is corrupted.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API DataSetCorruptedOffsetTableError: public DataSetError
{
public:
    /// \brief Build a dataSetImageDoesntExist exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    DataSetCorruptedOffsetTableError(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Base class from which the exceptions thrown
///         by directoryRecord and dicomDir derive.
///
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API DicomDirError: public std::runtime_error
{
public:
    /// \brief Build a dicomDirException exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    DicomDirError(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when a call to
///        dicomDir::setFirstRootRecord() or
///        directoryRecord::setNextRecord() or
///        directoryRecord::setFirstChildRecord() causes
///        a circular reference between directoryRecord
///        objects.
///
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API DicomDirCircularReferenceError: public DicomDirError
{
public:
    /// \brief Build a dicomDirCircularReferenceException
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    DicomDirCircularReferenceError(const std::string& message);
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
class IMEBRA_API DicomDirUnknownDirectoryRecordTypeError: public DicomDirError
{
public:
    /// \brief Build a dicomDirUnknownDirectoryRecordType
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    DicomDirUnknownDirectoryRecordTypeError(const std::string& message);
};


class IMEBRA_API HuffmanError: public std::runtime_error
{
public:
    HuffmanError(const std::string& message);
};

class IMEBRA_API HuffmanCreateTableError: public HuffmanError
{
public:
    HuffmanCreateTableError(const std::string& message);
};

class IMEBRA_API HuffmanReadError : public HuffmanError
{
public:
    HuffmanReadError(const std::string& message);
};

class IMEBRA_API HuffmanWriteError : public HuffmanError
{
public:
    HuffmanWriteError(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the image class.
///
///////////////////////////////////////////////////////////
class IMEBRA_API ImageError: public std::runtime_error
{
public:
    /// \brief Build a codec exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    ImageError(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown depth
///         is specified as a parameter.
///
///////////////////////////////////////////////////////////
class IMEBRA_API ImageUnknownDepthError: public ImageError
{
public:
    ImageUnknownDepthError(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown color
///         space is specified in the function create().
///
///////////////////////////////////////////////////////////
class IMEBRA_API ImageUnknownColorSpaceError: public ImageError
{
public:
    ImageUnknownColorSpaceError(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an invalid size
///         in pixels is specified in the function
///         create().
///
///////////////////////////////////////////////////////////
class IMEBRA_API ImageInvalidSizeError: public ImageError
{
public:
    ImageInvalidSizeError(const std::string& message);
};


/// \brief Base class for the exceptions thrown by the
///         transforms.
///
///////////////////////////////////////////////////////////
class IMEBRA_API TransformError: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// @param message the cause of the exception
    ///
    ///////////////////////////////////////////////////////////
    TransformError(const std::string& message);
};

/// \brief Exception thrown when the image areas to be
///         processed are out of bounds.
///
///////////////////////////////////////////////////////////
class IMEBRA_API TransformInvalidAreaError: public TransformError
{
public:
    /// \brief Constructor.
    ///
    /// @param message the cause of the exception
    ///
    ///////////////////////////////////////////////////////////
    TransformInvalidAreaError(const std::string& message);
};

class IMEBRA_API TransformDifferentHighBitError: public TransformError
{
public:
    TransformDifferentHighBitError(const std::string& message);
};

class IMEBRA_API TransformsChainError: public TransformError
{
public:
    TransformsChainError(const std::string& message);
};

class IMEBRA_API ColorTransformError: public TransformError
{
public:
    ColorTransformError(const std::string& message);
};

class IMEBRA_API ColorTransformWrongColorSpaceError: public ColorTransformError
{
public:
    ColorTransformWrongColorSpaceError(const std::string& message);
};

class IMEBRA_API ColorTransformWrongSizeError: public ColorTransformError
{
public:
    ColorTransformWrongSizeError(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions
///         thrown by colorTransformsFactory.
///
///////////////////////////////////////////////////////////
class IMEBRA_API ColorTransformsFactoryError: public TransformError
{
public:
    ColorTransformsFactoryError(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown by the function
///         colorTransformsFactory::getTransform() when
///         it cannot find any transform that can convert
///         the specified color spaces.
///
///////////////////////////////////////////////////////////
class IMEBRA_API ColorTransformsFactoryNoTransformError: public ColorTransformsFactoryError
{
public:
    ColorTransformsFactoryNoTransformError(const std::string& message);
};

class IMEBRA_API TransformHighBitError: public TransformError
{
public:
        TransformHighBitError(const std::string& message);
};

class IMEBRA_API TransformHighBitDifferentColorSpacesError: public TransformHighBitError
{
public:
    TransformHighBitDifferentColorSpacesError(const std::string& message);
};


/// \brief Exception thrown when an attempt to read past
///         the end of the file is made.
///
///////////////////////////////////////////////////////////
class IMEBRA_API StreamEOFError : public StreamError
{
public:
    StreamEOFError(const std::string& message);
};

/// \addtogroup group_baseclasses
///
/// @{

/// \brief Exception thrown when a jpeg tag is found but
///         wasn't expected.
///
///////////////////////////////////////////////////////////
class IMEBRA_API StreamJpegTagInStreamError : public StreamError
{
public:
    StreamJpegTagInStreamError(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by modalityVOILUT
///         when the images passed to the transform are
///         not monochromatic.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API ModalityVOILUTError: public TransformError
{
public:
    ModalityVOILUTError(const std::string& message);
};

class IMEBRA_API PALETTECOLORToRGBError: public ColorTransformError
{
public:
    PALETTECOLORToRGBError(const std::string& message);
};

/// \brief This is the base class for the exceptions thrown
///         by the dicom codec (dicomCodec).
///
///////////////////////////////////////////////////////////
class IMEBRA_API DicomCodecError: public CodecError
{
public:
    /// \brief Build a dicomCodecException exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    DicomCodecError(const std::string& message);
};

/// \brief This exception is thrown when
///         dicomCodec::parseStream reaches the maximum
///         depth for embedded datasets.
///
///////////////////////////////////////////////////////////
class IMEBRA_API DicomCodecDepthLimitReachedError: public DicomCodecError
{
public:
    /// \brief Build a dicomCodecExceptionDepthLimitReached
    ///        exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    DicomCodecDepthLimitReachedError(const std::string&message);

};

/// \brief Base class for the exceptions thrown by the
///        jpeg codec
///
///////////////////////////////////////////////////////////
class IMEBRA_API JpegCodecError: public CodecError
{
public:
    JpegCodecError(const std::string& message);
};

/// \brief Exception thrown when the jpeg variant cannot
///         be handled.
///
///////////////////////////////////////////////////////////
class IMEBRA_API JpegCodecCannotHandleSyntaxError: public JpegCodecError
{
public:
    /// \brief Constructs the exception.
    ///
    /// @param message   the cause of the exception
    ///
    ///////////////////////////////////////////////////////////
    JpegCodecCannotHandleSyntaxError(const std::string& message);
};


class IMEBRA_API ImebraBadAlloc: public std::bad_alloc
{
};

}

#endif // !defined(imebraExceptions__INCLUDED_)
