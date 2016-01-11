#if !defined(imebraExceptions_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_)
#define imebraExceptions_SWIG_A807A3CA_FA04_44f4_85D2_C7AA2FE103C4__INCLUDED_

#include <stdexcept>

#include "definitions.h"

namespace imebra
{

///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the lut class
///
///////////////////////////////////////////////////////////
class IMEBRA_API lutException: public std::runtime_error
{
public:
    lutException(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown by the lut class when
///         the wrong index or id is specified as a
///         parameter.
///
///////////////////////////////////////////////////////////
class IMEBRA_API lutExceptionWrongIndex: public lutException
{
public:
    lutExceptionWrongIndex(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown by the lut class when
///         the the LUT information is corrupted.
///
///////////////////////////////////////////////////////////
class IMEBRA_API lutExceptionCorrupted: public lutException
{
public:
    lutExceptionCorrupted(const std::string& message);
};

class IMEBRA_API missingDataElement: public std::runtime_error
{
public:
    missingDataElement(const std::string& message);
};

class IMEBRA_API missingGroup: public missingDataElement
{
public:
    missingGroup(const std::string& message);
};

class IMEBRA_API missingTag: public missingDataElement
{
public:
    missingTag(const std::string& message);
};

class IMEBRA_API missingBuffer: public missingDataElement
{
public:
    missingBuffer(const std::string& message);
};

class IMEBRA_API missingItem: public missingDataElement
{
public:
    missingItem(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief The base exception for all the exceptions
///         thrown by the function in baseStream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API streamException: public std::runtime_error
{
public:
    streamException(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when the stream cannot be
///         open.
///
///////////////////////////////////////////////////////////
class IMEBRA_API streamExceptionOpen : public streamException
{
public:
    streamExceptionOpen(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when there is an error during
///         the read phase.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API streamExceptionRead : public streamException
{
public:
    streamExceptionRead(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when there is an error during
///         the write phase.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API streamExceptionWrite : public streamException
{
public:
    streamExceptionWrite(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Exception thrown when there are problems during
///         the closure of the stream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API streamExceptionClose : public streamException
{
public:
    streamExceptionClose(const std::string& message);
};



///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the buffer class.
///
///////////////////////////////////////////////////////////
class IMEBRA_API bufferException: public std::runtime_error
{
public:
    /// \brief Build a buffer exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    bufferException(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is throw by the buffer when an
///         handler for an unknown data type is asked.
///
///////////////////////////////////////////////////////////
class IMEBRA_API bufferExceptionUnknownType: public bufferException
{
public:
    /// \brief Build a wrong data type exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    bufferExceptionUnknownType(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief Base class for the exceptions thrown by
///         charsetConversion.
///
///////////////////////////////////////////////////////////
class IMEBRA_API charsetConversionException: public std::runtime_error
{
public:
    charsetConversionException(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the requested charset
///         is not supported by the DICOM standard.
///
///////////////////////////////////////////////////////////
class IMEBRA_API charsetConversionExceptionNoTable: public charsetConversionException
{
public:
    charsetConversionExceptionNoTable(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the requested charset
///         is not supported by the system.
///
///////////////////////////////////////////////////////////
class IMEBRA_API charsetConversionExceptionNoSupportedTable: public charsetConversionException
{
public:
    charsetConversionExceptionNoSupportedTable(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief Exception thrown when the system doesn't have
///         a supported size for wchar_t
///
///////////////////////////////////////////////////////////
class IMEBRA_API charsetConversionExceptionUtfSizeNotSupported: public charsetConversionException
{
public:
    charsetConversionExceptionUtfSizeNotSupported(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the class charsetsList.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API charsetsListException: public std::runtime_error
{
public:
    charsetsListException(const std::string& message);
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
class IMEBRA_API charsetListExceptionDiffDefault: public charsetsListException
{
public:
    charsetListExceptionDiffDefault(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the codec derived classes.
///
///////////////////////////////////////////////////////////
class IMEBRA_API codecException: public std::runtime_error
{
public:
    /// \brief Build a codec exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    codecException(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the file being
///         parsed is not valid for the codec.
///
///////////////////////////////////////////////////////////
class IMEBRA_API codecExceptionWrongFormat: public codecException
{
public:
    /// \brief Build a codecExceptionWrongFormat exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    codecExceptionWrongFormat(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the file being
///         parsed is corrupted.
///
///////////////////////////////////////////////////////////
class IMEBRA_API codecExceptionCorruptedFile: public codecException
{
public:
    /// \brief Build a codecExceptionCorruptedFile exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    codecExceptionCorruptedFile(const std::string& message);
};


///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the transfer
///         syntax is not recognized by the codec.
///
///////////////////////////////////////////////////////////
class IMEBRA_API codecExceptionWrongTransferSyntax: public codecException
{
public:
    /// \brief Build a codecExceptionWrongTransferSyntax
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    codecExceptionWrongTransferSyntax(const std::string& message);
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
class IMEBRA_API codecExceptionImageTooBig: public codecException
{
public:
    /// \brief Build a codecExceptionImageTooBig
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    codecExceptionImageTooBig(const std::string& message);
};


class IMEBRA_API dataHandlerStringUnicodeException: public std::runtime_error
{
public:
    dataHandlerStringUnicodeException(const std::string& message);
};

class IMEBRA_API dataHandlerStringUnicodeExceptionUnknownCharset: public dataHandlerStringUnicodeException
{
public:
    dataHandlerStringUnicodeExceptionUnknownCharset(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the dataSet.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API dataSetException: public std::runtime_error
{
public:
    dataSetException(const std::string& message);
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
class IMEBRA_API dataSetExceptionDifferentFormat: public dataSetException
{
public:
    dataSetExceptionDifferentFormat(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown
///         transfer syntax is being used while reading or
///         writing a stream.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API dataSetExceptionUnknownTransferSyntax: public dataSetException
{
public:
    dataSetExceptionUnknownTransferSyntax(const std::string& message);
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
class IMEBRA_API dataSetExceptionWrongFrame: public dataSetException
{
public:
    dataSetExceptionWrongFrame(const std::string& message);
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
class IMEBRA_API dataSetExceptionOldFormat: public dataSetException
{
public:
    dataSetExceptionOldFormat(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the an image that
///         doesn't exist is requested.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API dataSetImageDoesntExist: public dataSetException
{
public:
    /// \brief Build a dataSetImageDoesntExist exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    dataSetImageDoesntExist(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown when the basic offset
///         table is corrupted.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API dataSetCorruptedOffsetTable: public dataSetException
{
public:
    /// \brief Build a dataSetImageDoesntExist exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    dataSetCorruptedOffsetTable(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Base class from which the exceptions thrown
///         by directoryRecord and dicomDir derive.
///
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API dicomDirException: public std::runtime_error
{
public:
    /// \brief Build a dicomDirException exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    dicomDirException(const std::string& message);
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
class IMEBRA_API dicomDirCircularReferenceException: public dicomDirException
{
public:
    /// \brief Build a dicomDirCircularReferenceException
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    dicomDirCircularReferenceException(const std::string& message);
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
class IMEBRA_API dicomDirUnknownDirectoryRecordType: public dicomDirException
{
public:
    /// \brief Build a dicomDirUnknownDirectoryRecordType
    ///         exception.
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    dicomDirUnknownDirectoryRecordType(const std::string& message);
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief Base class used for the exceptions thrown by
///         drawBitmap.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API drawBitmapException: public std::runtime_error
{
public:
    drawBitmapException(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by
///         declareBitmapType() if the image's area that
///         has to be generated is not valid.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API drawBitmapExceptionInvalidArea: public drawBitmapException
{
public:
    drawBitmapExceptionInvalidArea(const std::string& message);
};


class IMEBRA_API huffmanException: public std::runtime_error
{
public:
    huffmanException(const std::string& message);
};

class IMEBRA_API huffmanExceptionCreateTable: public huffmanException
{
public:
    huffmanExceptionCreateTable(const std::string& message);
};

class IMEBRA_API huffmanExceptionRead : public huffmanException
{
public:
    huffmanExceptionRead(const std::string& message);
};

class IMEBRA_API huffmanExceptionWrite : public huffmanException
{
public:
    huffmanExceptionWrite(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions thrown
///         by the image class.
///
///////////////////////////////////////////////////////////
class IMEBRA_API imageException: public std::runtime_error
{
public:
    /// \brief Build a codec exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    imageException(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown depth
///         is specified as a parameter.
///
///////////////////////////////////////////////////////////
class IMEBRA_API imageExceptionUnknownDepth: public imageException
{
public:
    imageExceptionUnknownDepth(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an unknown color
///         space is specified in the function create().
///
///////////////////////////////////////////////////////////
class IMEBRA_API imageExceptionUnknownColorSpace: public imageException
{
public:
    imageExceptionUnknownColorSpace(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown when an invalid size
///         in pixels is specified in the function
///         create().
///
///////////////////////////////////////////////////////////
class IMEBRA_API imageExceptionInvalidSize: public imageException
{
public:
    imageExceptionInvalidSize(const std::string& message);
};


/// \brief Base class for the exceptions thrown by the
///         transforms.
///
///////////////////////////////////////////////////////////
class IMEBRA_API transformException: public std::runtime_error
{
public:
    /// \brief Constructor.
    ///
    /// @param message the cause of the exception
    ///
    ///////////////////////////////////////////////////////////
    transformException(const std::string& message);
};

/// \brief Exception thrown when the image areas to be
///         processed are out of bounds.
///
///////////////////////////////////////////////////////////
class IMEBRA_API transformExceptionInvalidArea: public transformException
{
public:
    /// \brief Constructor.
    ///
    /// @param message the cause of the exception
    ///
    ///////////////////////////////////////////////////////////
    transformExceptionInvalidArea(const std::string& message);
};

class IMEBRA_API transformsChainException: public transformException
{
public:
    transformsChainException(const std::string& what);
};

class IMEBRA_API colorTransformException: public transformException
{
public:
    colorTransformException(const std::string& message);
};

class IMEBRA_API colorTransformExceptionWrongColorSpace: public colorTransformException
{
public:
    colorTransformExceptionWrongColorSpace(const std::string& message);
};

class IMEBRA_API colorTransformExceptionWrongSize: public colorTransformException
{
public:
    colorTransformExceptionWrongSize(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This is the base class for the exceptions
///         thrown by colorTransformsFactory.
///
///////////////////////////////////////////////////////////
class IMEBRA_API colorTransformsFactoryException: public transformException
{
public:
    colorTransformsFactoryException(const std::string& message);
};

///////////////////////////////////////////////////////////
/// \brief This exception is thrown by the function
///         colorTransformsFactory::getTransform() when
///         it cannot find any transform that can convert
///         the specified color spaces.
///
///////////////////////////////////////////////////////////
class IMEBRA_API colorTransformsFactoryExceptionNoTransform: public colorTransformsFactoryException
{
public:
    colorTransformsFactoryExceptionNoTransform(const std::string& message);
};

class IMEBRA_API transformHighBitException: public transformException
{
public:
        transformHighBitException(const std::string& message);
};

class IMEBRA_API transformHighBitDifferentColorSpaces: public transformHighBitException
{
public:
    transformHighBitDifferentColorSpaces(const std::string& message);
};


/// \brief Exception thrown when an attempt to read past
///         the end of the file is made.
///
///////////////////////////////////////////////////////////
class IMEBRA_API streamExceptionEOF : public streamException
{
public:
    streamExceptionEOF(const std::string& message);
};

/// \addtogroup group_baseclasses
///
/// @{

/// \brief Exception thrown when a jpeg tag is found but
///         wasn't expected.
///
///////////////////////////////////////////////////////////
class IMEBRA_API streamJpegTagInStream : public streamException
{
public:
    streamJpegTagInStream(const std::string& message);
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This exception is thrown by modalityVOILUT
///         when the images passed to the transform are
///         not monochromatic.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API modalityVOILUTException: public transformException
{
public:
    modalityVOILUTException(const std::string& message);
};

class IMEBRA_API PALETTECOLORToRGBException: public colorTransformException
{
public:
    PALETTECOLORToRGBException(const std::string& message);
};

/// \brief This is the base class for the exceptions thrown
///         by the dicom codec (dicomCodec).
///
///////////////////////////////////////////////////////////
class IMEBRA_API dicomCodecException: public codecException
{
public:
    /// \brief Build a dicomCodecException exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    dicomCodecException(const std::string& message);
};

/// \brief This exception is thrown when
///         dicomCodec::parseStream reaches the maximum
///         depth for embedded datasets.
///
///////////////////////////////////////////////////////////
class IMEBRA_API dicomCodecExceptionDepthLimitReached: public dicomCodecException
{
public:
    /// \brief Build a dicomCodecExceptionDepthLimitReached
    ///        exception
    ///
    /// @param message the message to store into the exception
    ///
    ///////////////////////////////////////////////////////////
    dicomCodecExceptionDepthLimitReached(const std::string&message);

};

/// \brief Base class for the exceptions thrown by the
///        jpeg codec
///
///////////////////////////////////////////////////////////
class IMEBRA_API jpegCodecException: public codecException
{
public:
    jpegCodecException(const std::string& message);
};

/// \brief Exception thrown when the jpeg variant cannot
///         be handled.
///
///////////////////////////////////////////////////////////
class IMEBRA_API jpegCodecCannotHandleSyntax: public jpegCodecException
{
public:
    /// \brief Constructs the exception.
    ///
    /// @param message   the cause of the exception
    ///
    ///////////////////////////////////////////////////////////
    jpegCodecCannotHandleSyntax(const std::string& message);
};



}

#endif
