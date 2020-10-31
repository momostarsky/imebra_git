/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(imebraObjcNSError__INCLUDED_)
#define imebraObjcNSError__INCLUDED_

#include <imebra/exceptions.h>
#import <imebraobjc/imebra_exceptions.h>
#import <Foundation/Foundation.h>

#include <stdexcept>

namespace dicomhero
{
    void setNSError(const std::runtime_error& error, NSError** pError, Class errorClass);
}

#define OBJC_DICOMHERO_FUNCTION_START() try {

#define OBJC_DICOMHERO_FUNCTION_END() } \
    catch(dicomhero::LutCorruptedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraLutCorruptedError class]);\
    }\
    catch(dicomhero::LutError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraLutError class]);\
    }\
    catch(dicomhero::MissingGroupError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraMissingGroupError class]);\
    }\
    catch(dicomhero::MissingTagError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraMissingTagError class]);\
    }\
    catch(dicomhero::MissingBufferError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraMissingBufferError class]);\
    }\
    catch(dicomhero::MissingItemError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraMissingItemError class]);\
    }\
    catch(dicomhero::MissingDataElementError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraMissingDataElementError class]);\
    }\
    catch(dicomhero::StreamReadError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraStreamReadError class]);\
    }\
    catch(dicomhero::StreamWriteError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraStreamWriteError class]);\
    }\
    catch(dicomhero::TCPConnectionRefused& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraTCPConnectionRefused class]);\
    }\
    catch(dicomhero::TCPAddressAlreadyInUse& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraTCPAddressAlreadyInUse class]);\
    }\
    catch(dicomhero::PermissionDeniedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraPermissionDeniedError class]);\
    }\
    catch(dicomhero::StreamOpenError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraStreamOpenError class]);\
    }\
    catch(dicomhero::AddressTryAgainError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAddressTryAgainError class]);\
    }\
    catch(dicomhero::AddressNoNameError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAddressNoNameError class]);\
    }\
    catch(dicomhero::AddressServiceNotSupportedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAddressServiceNotSupportedError class]);\
    }\
    catch(dicomhero::AddressError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAddressError class]);\
    }\
    catch(dicomhero::DictionaryUnknownTagError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDictionaryUnknownTagError class]);\
    }\
    catch(dicomhero::DictionaryUnknownDataTypeError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDictionaryUnknownDataTypeError class]);\
    }\
    catch(dicomhero::DictionaryError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDictionaryError class]);\
    }\
    catch(dicomhero::CharsetConversionNoTableError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCharsetConversionNoTableError class]);\
    }\
    catch(dicomhero::CharsetConversionNoSupportedTableError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCharsetConversionNoSupportedTableError class]);\
    }\
    catch(dicomhero::CharsetConversionCannotConvert& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCharsetConversionCannotConvert class]);\
    }\
    catch(dicomhero::CharsetConversionError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCharsetConversionError class]);\
    }\
    catch(dicomhero::CodecWrongFormatError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCodecWrongFormatError class]);\
    }\
    catch(dicomhero::CodecCorruptedFileError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCodecCorruptedFileError class]);\
    }\
    catch(dicomhero::CodecWrongTransferSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCodecWrongTransferSyntaxError class]);\
    }\
    catch(dicomhero::CodecImageTooBigError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCodecImageTooBigError class]);\
    }\
    catch(dicomhero::InvalidSequenceItemError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraInvalidSequenceItemError class]);\
    }\
    catch(dicomhero::DataHandlerConversionError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataHandlerConversionError class]);\
    }\
    catch(dicomhero::DataHandlerCorruptedBufferError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataHandlerCorruptedBufferError class]);\
    }\
    catch(dicomhero::DataHandlerInvalidDataError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataHandlerInvalidDataError class]);\
    }\
    catch(dicomhero::DataHandlerError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataHandlerError class]);\
    }\
    catch(dicomhero::DataSetDifferentFormatError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataSetDifferentFormatError class]);\
    }\
    catch(dicomhero::DataSetUnknownTransferSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataSetUnknownTransferSyntaxError class]);\
    }\
    catch(dicomhero::DataSetWrongFrameError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataSetWrongFrameError class]);\
    }\
    catch(dicomhero::DataSetImageDoesntExistError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataSetImageDoesntExistError class]);\
    }\
    catch(dicomhero::DataSetImagePaletteColorIsReadOnly& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataSetImagePaletteColorIsReadOnly class]);\
    }\
    catch(dicomhero::DataSetCorruptedOffsetTableError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataSetCorruptedOffsetTableError class]);\
    }\
    catch(dicomhero::DataSetError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDataSetError class]);\
    }\
    catch(dicomhero::DicomDirCircularReferenceError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDicomDirCircularReferenceError class]);\
    }\
    catch(dicomhero::DicomDirError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDicomDirError class]);\
    }\
    catch(dicomhero::ImageUnknownDepthError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraImageUnknownDepthError class]);\
    }\
    catch(dicomhero::ImageUnknownColorSpaceError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraImageUnknownColorSpaceError class]);\
    }\
    catch(dicomhero::ImageInvalidSizeError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraImageInvalidSizeError class]);\
    }\
    catch(dicomhero::ImageError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraImageError class]);\
    }\
    catch(dicomhero::TransformInvalidAreaError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraTransformInvalidAreaError class]);\
    }\
    catch(dicomhero::TransformDifferentHighBitError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraTransformDifferentHighBitError class]);\
    }\
    catch(dicomhero::ColorTransformWrongColorSpaceError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraColorTransformWrongColorSpaceError class]);\
    }\
    catch(dicomhero::ColorTransformsFactoryNoTransformError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraColorTransformsFactoryNoTransformError class]);\
    }\
    catch(dicomhero::ColorTransformsFactoryError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraColorTransformsFactoryError class]);\
    }\
    catch(dicomhero::TransformDifferentColorSpacesError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraTransformDifferentColorSpacesError class]);\
    }\
    catch(dicomhero::ColorTransformError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraColorTransformError class]);\
    }\
    catch(dicomhero::ModalityVOILUTError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraModalityVOILUTError class]);\
    }\
    catch(dicomhero::TransformError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraTransformError class]);\
    }\
    catch(dicomhero::StreamClosedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraStreamClosedError class]);\
    }\
    catch(dicomhero::StreamEOFError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraStreamEOFError class]);\
    }\
    catch(dicomhero::DicomCodecDepthLimitReachedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDicomCodecDepthLimitReachedError class]);\
    }\
    catch(dicomhero::DicomCodecError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDicomCodecError class]);\
    }\
    catch(dicomhero::JpegCodecCannotHandleSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraJpegCodecCannotHandleSyntaxError class]);\
    }\
    catch(dicomhero::JpegCodecError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraJpegCodecError class]);\
    }\
    catch(dicomhero::CodecError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraCodecError class]);\
    }\
    catch(dicomhero::MemorySizeError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraMemorySizeError class]);\
    }\
    catch(dicomhero::MemoryError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraMemoryError class]);\
    }\
    catch(dicomhero::AcseCorruptedMessageError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseCorruptedMessageError class]);\
    }\
    catch(dicomhero::AcseNoTransferSyntaxError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseNoTransferSyntaxError class]);\
    }\
    catch(dicomhero::AcsePresentationContextNotRequestedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcsePresentationContextNotRequestedError class]);\
    }\
    catch(dicomhero::AcseWrongRoleError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseWrongRoleError class]);\
    }\
    catch(dicomhero::AcseWrongResponseIdError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseWrongResponseIdError class]);\
    }\
    catch(dicomhero::AcseWrongCommandIdError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseWrongCommandIdError class]);\
    }\
    catch(dicomhero::AcseWrongIdError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseWrongIdError class]);\
    }\
    catch(dicomhero::AcseSCUNoReasonGivenError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCUNoReasonGivenError class]);\
    }\
    catch(dicomhero::AcseSCUApplicationContextNameNotSupportedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCUApplicationContextNameNotSupportedError class]);\
    }\
    catch(dicomhero::AcseSCUCallingAETNotRecognizedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCUCallingAETNotRecognizedError class]);\
    }\
    catch(dicomhero::AcseSCUCalledAETNotRecognizedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCUCalledAETNotRecognizedError class]);\
    }\
    catch(dicomhero::AcseSCPNoReasonGivenError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCPNoReasonGivenError class]);\
    }\
    catch(dicomhero::AcseSCPAcseProtocolVersionNotSupportedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCPAcseProtocolVersionNotSupportedError class]);\
    }\
    catch(dicomhero::AcseSCPPresentationReservedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCPPresentationReservedError class]);\
    }\
    catch(dicomhero::AcseSCPPresentationTemporaryCongestionError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCPPresentationTemporaryCongestionError class]);\
    }\
    catch(dicomhero::AcseSCPPresentationLocalLimitExcededError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseSCPPresentationLocalLimitExcededError class]);\
    }\
    catch(dicomhero::AcseTooManyOperationsPerformedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseTooManyOperationsPerformedError class]);\
    }\
    catch(dicomhero::AcseTooManyOperationsInvokedError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseTooManyOperationsInvokedError class]);\
    }\
    catch(dicomhero::AcseNoPayloadError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseNoPayloadError class]);\
    }\
    catch(dicomhero::AcseRejectedAssociationError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseRejectedAssociationError class]);\
    }\
    catch(dicomhero::AcseError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraAcseError class]);\
    }\
    catch(dicomhero::DimseInvalidCommand& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDimseInvalidCommand class]);\
    }\
    catch(dicomhero::DimseError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraDimseError class]);\
    }\
    catch(dicomhero::NonRegisteredUIDGenerator& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraNonRegisteredUIDGenerator class]);\
    }\
    catch(dicomhero::UIDGeneratorError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraUIDGeneratorError class]);\
    }\
    catch(const dicomhero::StreamError& e)\
    {\
        dicomhero::setNSError(e, pError, [ImebraStreamError class]);\
    }


#define OBJC_DICOMHERO_FUNCTION_END_RETURN(returnValue) \
    OBJC_DICOMHERO_FUNCTION_END(); \
    return returnValue;

#endif // imebraObjcNSError__INCLUDED_
