/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#import <imebraobjc/dicomhero.h>

@compatibility_alias DicomheroVOIDescription ImebraVOIDescription;
@compatibility_alias DicomheroVOILUT ImebraVOILUT;
@compatibility_alias DicomheroPresentationContext ImebraPresentationContext;
@compatibility_alias DicomheroPresentationContexts ImebraPresentationContexts;
@compatibility_alias DicomheroAssociationMessage ImebraAssociationMessage;
@compatibility_alias DicomheroMutableAssociationMessage ImebraMutableAssociationMessage;
@compatibility_alias DicomheroAssociationBase ImebraAssociationBase;
@compatibility_alias DicomheroAssociationSCU ImebraAssociationSCU;
@compatibility_alias DicomheroAssociationSCP ImebraAssociationSCP;
@compatibility_alias DicomheroBaseStreamInput ImebraBaseStreamInput;
@compatibility_alias DicomheroStreamTimeout ImebraStreamTimeout;
@compatibility_alias DicomheroBaseStreamOutput ImebraBaseStreamOutput;
@compatibility_alias DicomheroBaseUIDGenerator ImebraBaseUIDGenerator;
@compatibility_alias DicomheroCodecFactory ImebraCodecFactory;
@compatibility_alias DicomheroColorTransformsFactory ImebraColorTransformsFactory;
@compatibility_alias DicomheroDataSet ImebraDataSet;
@compatibility_alias DicomheroMutableDataSet ImebraMutableDataSet;
@compatibility_alias DicomheroAge ImebraAge;
@compatibility_alias DicomheroDate ImebraDate;
@compatibility_alias DicomheroDicomDictionary ImebraDicomDictionary;
@compatibility_alias DicomheroDicomDirEntry ImebraDicomDirEntry;
@compatibility_alias DicomheroMutableDicomDirEntry ImebraMutableDicomDirEntry;
@compatibility_alias DicomheroDicomDir ImebraDicomDir;
@compatibility_alias DicomheroMutableDicomDir ImebraMutableDicomDir;
@compatibility_alias DicomheroDimseCommandBase ImebraDimseCommandBase;
@compatibility_alias DicomheroDimseCommand ImebraDimseCommand;
@compatibility_alias DicomheroDimseResponse ImebraDimseResponse;
@compatibility_alias DicomheroCPartialResponse ImebraCPartialResponse;
@compatibility_alias DicomheroCStoreCommand ImebraCStoreCommand;
@compatibility_alias DicomheroCStoreResponse ImebraCStoreResponse;
@compatibility_alias DicomheroCGetCommand ImebraCGetCommand;
@compatibility_alias DicomheroCGetResponse ImebraCGetResponse;
@compatibility_alias DicomheroCFindCommand ImebraCFindCommand;
@compatibility_alias DicomheroCFindResponse ImebraCFindResponse;
@compatibility_alias DicomheroCMoveCommand ImebraCMoveCommand;
@compatibility_alias DicomheroCMoveResponse ImebraCMoveResponse;
@compatibility_alias DicomheroCEchoCommand ImebraCEchoCommand;
@compatibility_alias DicomheroCEchoResponse ImebraCEchoResponse;
@compatibility_alias DicomheroCCancelCommand ImebraCCancelCommand;
@compatibility_alias DicomheroNEventReportCommand ImebraNEventReportCommand;
@compatibility_alias DicomheroNEventReportResponse ImebraNEventReportResponse;
@compatibility_alias DicomheroNGetCommand ImebraNGetCommand;
@compatibility_alias DicomheroNGetResponse ImebraNGetResponse;
@compatibility_alias DicomheroNSetCommand ImebraNSetCommand;
@compatibility_alias DicomheroNSetResponse ImebraNSetResponse;
@compatibility_alias DicomheroNActionCommand ImebraNActionCommand;
@compatibility_alias DicomheroNActionResponse ImebraNActionResponse;
@compatibility_alias DicomheroNCreateCommand ImebraNCreateCommand;
@compatibility_alias DicomheroNCreateResponse ImebraNCreateResponse;
@compatibility_alias DicomheroNDeleteCommand ImebraNDeleteCommand;
@compatibility_alias DicomheroNDeleteResponse ImebraNDeleteResponse;
@compatibility_alias DicomheroDimseService ImebraDimseService;
@compatibility_alias DicomheroDrawBitmap ImebraDrawBitmap;
@compatibility_alias DicomheroFileStreamInput ImebraFileStreamInput;
@compatibility_alias DicomheroFileStreamOutput ImebraFileStreamOutput;
@compatibility_alias DicomheroImage ImebraImage;
@compatibility_alias DicomheroMutableImage ImebraMutableImage;
@compatibility_alias DicomheroLUT ImebraLUT;
@compatibility_alias DicomheroMemoryPool ImebraMemoryPool;
@compatibility_alias DicomheroMemoryStreamInput ImebraMemoryStreamInput;
@compatibility_alias DicomheroMemoryStreamOutput ImebraMemoryStreamOutput;
@compatibility_alias DicomheroModalityVOILUT ImebraModalityVOILUT;
@compatibility_alias DicomheroOverlay ImebraOverlay;
@compatibility_alias DicomheroMutableOverlay ImebraMutableOverlay;
@compatibility_alias DicomheroPatientName ImebraPatientName;
@compatibility_alias DicomheroPipeStream ImebraPipeStream;
@compatibility_alias DicomheroRandomUIDGenerator ImebraRandomUIDGenerator;
@compatibility_alias DicomheroMemory ImebraMemory;
@compatibility_alias DicomheroMutableMemory ImebraMutableMemory;
@compatibility_alias DicomheroReadingDataHandler ImebraReadingDataHandler;
@compatibility_alias DicomheroReadingDataHandlerNumeric ImebraReadingDataHandlerNumeric;
@compatibility_alias DicomheroSerialNumberUIDGenerator ImebraSerialNumberUIDGenerator;
@compatibility_alias DicomheroStreamReader ImebraStreamReader;
@compatibility_alias DicomheroStreamWriter ImebraStreamWriter;
@compatibility_alias DicomheroTag ImebraTag;
@compatibility_alias DicomheroMutableTag ImebraMutableTag;
@compatibility_alias DicomheroTagId ImebraTagId;
@compatibility_alias DicomheroTCPAddress ImebraTCPAddress;
@compatibility_alias DicomheroTCPActiveAddress ImebraTCPActiveAddress;
@compatibility_alias DicomheroTCPPassiveAddress ImebraTCPPassiveAddress;
@compatibility_alias DicomheroTCPListener ImebraTCPListener;
@compatibility_alias DicomheroTCPStream ImebraTCPStream;
@compatibility_alias DicomheroTransform ImebraTransform;
@compatibility_alias DicomheroTransformHighBit ImebraTransformHighBit;
@compatibility_alias DicomheroTransformsChain ImebraTransformsChain;
@compatibility_alias DicomheroUIDGeneratorFactory ImebraUIDGeneratorFactory;
@compatibility_alias DicomheroWritingDataHandler ImebraWritingDataHandler;
@compatibility_alias DicomheroWritingDataHandlerNumeric ImebraWritingDataHandlerNumeric;

// Exceptions
@compatibility_alias DicomheroLutError ImebraLutError;
@compatibility_alias DicomheroLutCorruptedError ImebraLutCorruptedError;
@compatibility_alias DicomheroMissingDataElementError ImebraMissingDataElementError;
@compatibility_alias DicomheroMissingGroupError ImebraMissingGroupError;
@compatibility_alias DicomheroMissingTagError ImebraMissingTagError;
@compatibility_alias DicomheroMissingBufferError ImebraMissingBufferError;
@compatibility_alias DicomheroMissingItemError ImebraMissingItemError;
@compatibility_alias DicomheroStreamError ImebraStreamError;
@compatibility_alias DicomheroStreamOpenError ImebraStreamOpenError;
@compatibility_alias DicomheroStreamReadError ImebraStreamReadError;
@compatibility_alias DicomheroStreamWriteError ImebraStreamWriteError;
@compatibility_alias DicomheroTCPConnectionRefused ImebraTCPConnectionRefused;
@compatibility_alias DicomheroTCPAddressAlreadyInUse ImebraTCPAddressAlreadyInUse;
@compatibility_alias DicomheroPermissionDeniedError ImebraPermissionDeniedError;
@compatibility_alias DicomheroAddressError ImebraAddressError;
@compatibility_alias DicomheroAddressTryAgainError ImebraAddressTryAgainError;
@compatibility_alias DicomheroAddressNoNameError ImebraAddressNoNameError;
@compatibility_alias DicomheroAddressServiceNotSupportedError ImebraAddressServiceNotSupportedError;
@compatibility_alias DicomheroDictionaryError ImebraDictionaryError;
@compatibility_alias DicomheroDictionaryUnknownTagError ImebraDictionaryUnknownTagError;
@compatibility_alias DicomheroDictionaryUnknownDataTypeError ImebraDictionaryUnknownDataTypeError;
@compatibility_alias DicomheroCharsetConversionError ImebraCharsetConversionError;
@compatibility_alias DicomheroCharsetConversionNoTableError ImebraCharsetConversionNoTableError;
@compatibility_alias DicomheroCharsetConversionNoSupportedTableError ImebraCharsetConversionNoSupportedTableError;
@compatibility_alias DicomheroCharsetConversionCannotConvert ImebraCharsetConversionCannotConvert;
@compatibility_alias DicomheroCodecError ImebraCodecError;
@compatibility_alias DicomheroCodecWrongFormatError ImebraCodecWrongFormatError;
@compatibility_alias DicomheroCodecCorruptedFileError ImebraCodecCorruptedFileError;
@compatibility_alias DicomheroCodecWrongTransferSyntaxError ImebraCodecWrongTransferSyntaxError;
@compatibility_alias DicomheroCodecImageTooBigError ImebraCodecImageTooBigError;
@compatibility_alias DicomheroInvalidSequenceItemError ImebraInvalidSequenceItemError;
@compatibility_alias DicomheroDataHandlerError ImebraDataHandlerError;
@compatibility_alias DicomheroDataHandlerConversionError ImebraDataHandlerConversionError;
@compatibility_alias DicomheroDataHandlerCorruptedBufferError ImebraDataHandlerCorruptedBufferError;
@compatibility_alias DicomheroDataHandlerInvalidDataError ImebraDataHandlerInvalidDataError;
@compatibility_alias DicomheroDataSetError ImebraDataSetError;
@compatibility_alias DicomheroDataSetDifferentFormatError ImebraDataSetDifferentFormatError;
@compatibility_alias DicomheroDataSetUnknownTransferSyntaxError ImebraDataSetUnknownTransferSyntaxError;
@compatibility_alias DicomheroDataSetWrongFrameError ImebraDataSetWrongFrameError;
@compatibility_alias DicomheroDataSetImageDoesntExistError ImebraDataSetImageDoesntExistError;
@compatibility_alias DicomheroDataSetImagePaletteColorIsReadOnly ImebraDataSetImagePaletteColorIsReadOnly;
@compatibility_alias DicomheroDataSetCorruptedOffsetTableError ImebraDataSetCorruptedOffsetTableError;
@compatibility_alias DicomheroDicomDirError ImebraDicomDirError;
@compatibility_alias DicomheroDicomDirCircularReferenceError ImebraDicomDirCircularReferenceError;
@compatibility_alias DicomheroImageError ImebraImageError;
@compatibility_alias DicomheroImageUnknownDepthError ImebraImageUnknownDepthError;
@compatibility_alias DicomheroImageUnknownColorSpaceError ImebraImageUnknownColorSpaceError;
@compatibility_alias DicomheroImageInvalidSizeError ImebraImageInvalidSizeError;
@compatibility_alias DicomheroTransformError ImebraTransformError;
@compatibility_alias DicomheroTransformInvalidAreaError ImebraTransformInvalidAreaError;
@compatibility_alias DicomheroTransformDifferentHighBitError ImebraTransformDifferentHighBitError;
@compatibility_alias DicomheroTransformDifferentColorSpacesError ImebraTransformDifferentColorSpacesError;
@compatibility_alias DicomheroColorTransformError ImebraColorTransformError;
@compatibility_alias DicomheroColorTransformWrongColorSpaceError ImebraColorTransformWrongColorSpaceError;
@compatibility_alias DicomheroColorTransformsFactoryError ImebraColorTransformsFactoryError;
@compatibility_alias DicomheroColorTransformsFactoryNoTransformError ImebraColorTransformsFactoryNoTransformError;
@compatibility_alias DicomheroStreamEOFError ImebraStreamEOFError;
@compatibility_alias DicomheroStreamClosedError ImebraStreamClosedError;
@compatibility_alias DicomheroModalityVOILUTError ImebraModalityVOILUTError;
@compatibility_alias DicomheroDicomCodecError ImebraDicomCodecError;
@compatibility_alias DicomheroDicomCodecDepthLimitReachedError ImebraDicomCodecDepthLimitReachedError;
@compatibility_alias DicomheroJpegCodecError ImebraJpegCodecError;
@compatibility_alias DicomheroJpegCodecCannotHandleSyntaxError ImebraJpegCodecCannotHandleSyntaxError;
@compatibility_alias DicomheroBadAlloc ImebraBadAlloc;
@compatibility_alias DicomheroMemoryError ImebraMemoryError;
@compatibility_alias DicomheroMemorySizeError ImebraMemorySizeError;
@compatibility_alias DicomheroAcseError ImebraAcseError;
@compatibility_alias DicomheroAcseCorruptedMessageError ImebraAcseCorruptedMessageError;
@compatibility_alias DicomheroAcseNoTransferSyntaxError ImebraAcseNoTransferSyntaxError;
@compatibility_alias DicomheroAcsePresentationContextNotRequestedError ImebraAcsePresentationContextNotRequestedError;
@compatibility_alias DicomheroAcseWrongRoleError ImebraAcseWrongRoleError;
@compatibility_alias DicomheroAcseWrongIdError ImebraAcseWrongIdError;
@compatibility_alias DicomheroAcseWrongResponseIdError ImebraAcseWrongResponseIdError;
@compatibility_alias DicomheroAcseWrongCommandIdError ImebraAcseWrongCommandIdError;
@compatibility_alias DicomheroAcseRejectedAssociationError ImebraAcseRejectedAssociationError;
@compatibility_alias DicomheroAcseSCUNoReasonGivenError ImebraAcseSCUNoReasonGivenError;
@compatibility_alias DicomheroAcseSCUApplicationContextNameNotSupportedError ImebraAcseSCUApplicationContextNameNotSupportedError;
@compatibility_alias DicomheroAcseSCUCallingAETNotRecognizedError ImebraAcseSCUCallingAETNotRecognizedError;
@compatibility_alias DicomheroAcseSCUCalledAETNotRecognizedError ImebraAcseSCUCalledAETNotRecognizedError;
@compatibility_alias DicomheroAcseSCPNoReasonGivenError ImebraAcseSCPNoReasonGivenError;
@compatibility_alias DicomheroAcseSCPAcseProtocolVersionNotSupportedError ImebraAcseSCPAcseProtocolVersionNotSupportedError;
@compatibility_alias DicomheroAcseSCPPresentationReservedError ImebraAcseSCPPresentationReservedError;
@compatibility_alias DicomheroAcseSCPPresentationTemporaryCongestionError ImebraAcseSCPPresentationTemporaryCongestionError;
@compatibility_alias DicomheroAcseSCPPresentationLocalLimitExcededError ImebraAcseSCPPresentationLocalLimitExcededError;
@compatibility_alias DicomheroAcseTooManyOperationsPerformedError ImebraAcseTooManyOperationsPerformedError;
@compatibility_alias DicomheroAcseTooManyOperationsInvokedError ImebraAcseTooManyOperationsInvokedError;
@compatibility_alias DicomheroAcseNoPayloadError ImebraAcseNoPayloadError;
@compatibility_alias DicomheroDimseError ImebraDimseError;
@compatibility_alias DicomheroDimseInvalidCommand ImebraDimseInvalidCommand;
@compatibility_alias DicomheroUIDGeneratorError ImebraUIDGeneratorError;
@compatibility_alias DicomheroNonRegisteredUIDGenerator ImebraNonRegisteredUIDGenerator;

// Enumerations
typedef NS_ENUM(int, DicomheroDicomVOIFunction)
{
    DicomheroDicomVOIFunctionLinear = 0,      ///< Correspond to the DICOM VOI function "LINEAR"
    DicomheroDicomVOIFunctionLinearExact = 1, ///< Correspond to the DICOM VOI function "LINEAR_EXACT"
    DicomheroDicomVOIFunctionSigmoid = 2      ///< Correspond to the DICOM VOI function "SIGMOID"
};

typedef NS_ENUM(unsigned short, DicomheroCodecType)
{
    DicomheroCodecTypeDicom = 0, ///< DICOM codec
    DicomheroCodecTypeJpeg  = 1  ///< JPEG codec
};

typedef NS_ENUM(unsigned short, DicomheroTagType)
{
    DicomheroTagTypeAE = 0x4145, ///< Application Entity
    DicomheroTagTypeAS = 0x4153, ///< Age String
    DicomheroTagTypeAT = 0x4154, ///< Attribute Tag
    DicomheroTagTypeCS = 0x4353, ///< Code String
    DicomheroTagTypeDA = 0x4441, ///< Date
    DicomheroTagTypeDS = 0x4453, ///< Decimal String
    DicomheroTagTypeDT = 0x4454, ///< Date Time
    DicomheroTagTypeFL = 0x464c, ///< Floating Point Single
    DicomheroTagTypeFD = 0x4644, ///< Floating Point Double
    DicomheroTagTypeIS = 0x4953, ///< Integer String
    DicomheroTagTypeLO = 0x4c4f, ///< Long String
    DicomheroTagTypeLT = 0x4c54, ///< Long Text
    DicomheroTagTypeOB = 0x4f42, ///< Other Byte String
    DicomheroTagTypeSB = 0x5342, ///< Non standard. Used internally for signed bytes
    DicomheroTagTypeOD = 0x4f44, ///< Other Double String
    DicomheroTagTypeOF = 0x4f46, ///< Other Float String
    DicomheroTagTypeOL = 0x4f4c, ///< Other Long String
    DicomheroTagTypeOW = 0x4f57, ///< Other Word String
    DicomheroTagTypePN = 0x504e, ///< Person Name
    DicomheroTagTypeSH = 0x5348, ///< Short String
    DicomheroTagTypeSL = 0x534c, ///< Signed Long
    DicomheroTagTypeSQ = 0x5351, ///< Sequence of Items
    DicomheroTagTypeSS = 0x5353, ///< Signed Short
    DicomheroTagTypeST = 0x5354, ///< Short Text
    DicomheroTagTypeTM = 0x544d, ///< Time
    DicomheroTagTypeUC = 0x5543, ///< Unlimited characters
    DicomheroTagTypeUI = 0x5549, ///< Unique Identifier
    DicomheroTagTypeUL = 0x554c, ///< Unsigned Long
    DicomheroTagTypeUN = 0x554e, ///< Unknown
    DicomheroTagTypeUR = 0x5552, ///< Unified Resource Identifier
    DicomheroTagTypeUS = 0x5553, ///< Unsigned Short
    DicomheroTagTypeUT = 0x5554  ///< Unlimited Text
};

typedef NS_ENUM(unsigned int, DicomheroImageQuality)
{
    DicomheroImageQualityVeryHigh = 0,      ///< the image is saved with very high quality. No subsampling is performed and no quantization
    DicomheroImageQualityHigh = 100,        ///< the image is saved with high quality. No subsampling is performed. Quantization ratios are low
    DicomheroImageQualityAboveMedium = 200, ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are low
    DicomheroImageQualityMedium = 300,      ///< the image is saved in medium quality. Horizontal subsampling is applied. Quantization ratios are medium
    DicomheroImageQualityBelowMedium = 400, ///< the image is saved in medium quality. Horizontal and vertical subsampling are applied. Quantization ratios are medium
    DicomheroImageQualityLow = 500,         ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are higher than the ratios used in the belowMedium quality
    DicomheroImageQualityVeryLow = 600      ///< the image is saved in low quality. Horizontal and vertical subsampling are applied. Quantization ratios are high
};

typedef NS_ENUM(char, DicomheroAgeUnit)
{
    DicomheroAgeUnitDays = (char)'D',   ///< Days
    DicomheroAgeUnitWeeks = (char)'W',  ///< Weeks
    DicomheroAgeUnitMonths = (char)'M', ///< Months
    DicomheroAgeUnitYears = (char)'Y'   ///< Years
};

typedef NS_ENUM(unsigned short, DicomheroDimseCommandType)
{
    DicomheroDimseCommandTypeCStore = 0x1,         ///< C-STORE
    DicomheroDimseCommandTypeCGet = 0x10,          ///< C-GET
    DicomheroDimseCommandTypeCFind = 0x20,         ///< C-FIND
    DicomheroDimseCommandTypeCMove = 0x21,         ///< C-MOVE
    DicomheroDimseCommandTypeCCancel = 0xfff,      ///< C-CANCEL
    DicomheroDimseCommandTypeCEcho = 0x30,         ///< C-ECHO
    DicomheroDimseCommandTypeNEventReport = 0x100, ///< N-EVENT_REPORT
    DicomheroDimseCommandTypeNGet = 0x110,         ///< N-GET
    DicomheroDimseCommandTypeNSet = 0x120,         ///< N-SET
    DicomheroDimseCommandTypeNAction = 0x130,      ///< N-ACTION
    DicomheroDimseCommandTypeNCreate = 0x140,      ///< N-CREATE
    DicomheroDimseCommandTypeNDelete = 0x150       ///< N-DELETE
};

typedef NS_ENUM(unsigned short, DicomheroDimseCommandPriority)
{
    DicomheroDimseCommandPriorityLow = 0x2,  ///< Low priority
    DicomheroDimseCommandPriorityMedium = 0, ///< Medium priority
    DicomheroDimseCommandPriorityHigh = 0x1  ///< High priority

};

typedef NS_ENUM(unsigned short, DicomheroDimseStatusCode)
{
    DicomheroDimseStatusCodeSuccess = 0,                                           ///< Success
    DicomheroDimseStatusCodeUnsupportedOptionalAttributes = 0x0001,                ///< Requested optional Attributes are not supported
    DicomheroDimseStatusCodeCannotUpdateperformedProcedureStepObject = 0x0110,     ///< Performed Procedure Step Object may no longer be updated
    DicomheroDimseStatusCodeUnsupportedSOPClass = 0x0122,                          ///< SOP Class not Supported
    DicomheroDimseStatusCodeOutOfResources = 0xa700,                               ///< Refused: Out of resources
    DicomheroDimseStatusCodeOutOfResourcesCannotCalculateNumberOfMatches = 0xa701, ///< Refused: Out of Resources - Unable to calculate number of matches
    DicomheroDimseStatusCodeOutOfResourcesCannotPerformSubOperations = 0xa702,     ///< Refused: Out of Resources - Unable to perform sub-operations
    DicomheroDimseStatusCodeMoveDestinationUnknown = 0xa801,                       ///< Refused: Move Destination unknown
    DicomheroDimseStatusCodeIdentifierDoesNotMatchSOPClass = 0xa900,               ///< Identifier does not match SOP Class
    DicomheroDimseStatusCodeSubOperationCompletedWithErrors = 0xb000,              ///< Sub-operations Complete - One or more Failures
    DicomheroDimseStatusCodeElementDiscarded = 0xb006,                             ///< Element discarded
    DicomheroDimseStatusCodeDatasetDoesNotMatchSOPClass = 0xb007,                  ///< Data Set does not match SOP Class
    DicomheroDimseStatusCodeUPSAlreadyCanceled = 0xb304,                           ///< The UPS is already in the requested state of CANCELED
    DicomheroDimseStatusCodeCoercedInvalidValuesToValidValues = 0xb305,            ///< Coerced invalid values to valid values
    DicomheroDimseStatusCodeUPSStateAlreadyCompleted = 0xb306,                     ///< The UPS is already in the requested state of COMPLETED
    DicomheroDimseStatusCodeUnableToProcess = 0xc000,                              ///< Unable to process
    DicomheroDimseStatusCodeMoreThanOneMatchFound = 0xc100,                        ///< More than one match found,
    DicomheroDimseStatusCodeCannotSupportRequestedTemplate = 0xc200,               ///< Unable to support requested template
    DicomheroDimseStatusCodeUPSNotUpdated = 0xc300,                                ///< Refused: The UPS may no longer be updated
    DicomheroDimseStatusCodeTransactionUIDNotProvided = 0xc301,                    ///< Refused: The correct Transaction UID was not provided
    DicomheroDimseStatusCodeUPSAlreadyInProgress = 0xc302,                         ///< Refused: The UPS is already IN PROGRESS
    DicomheroDimseStatusCodeCanScheduleOnlyWithNCreate = 0xc303,                   ///< Refused: The UPS may only become SCHEDULED via N-CREATE, not N-SET or N-ACTION
    DicomheroDimseStatusCodeUPSCannotChangeState = 0xc304,                         ///< Refused: The UPS has not met final state requirements for the requested state change
    DicomheroDimseStatusCodeInstanceUIDDoesNotExist = 0xc307,                      ///< Specified SOP Instance UID does not exist or is not a UPS Instance managed by this SCP
    DicomheroDimseStatusCodeUnknownAETitle = 0xc308,                               ///< Receiving AE-TITLE is Unknown to this SCP
    DicomheroDimseStatusCodeUPSNotSchedule = 0xc309,                               ///< Refused: The provided value of UPS State was not SCHEDULED
    DicomheroDimseStatusCodeUPSNotInProgress = 0xc310,                             ///< Refused: The UPS is not yet in the "IN PROGRESS" state
    DicomheroDimseStatusCodeUPSAlreadyCompleted = 0xc311,                          ///< Refused: The UPS is already COMPLETED
    DicomheroDimseStatusCodePerformerCannotBeContacted = 0xc312,                   ///< Refused: The performer cannot be contacted
    DicomheroDimseStatusCodePerformerDoesNotCancel = 0xc313,                       ///< Refused: Performer chooses not to cancel
    DicomheroDimseStatusCodeUnappropriateActionForInstance = 0xc314,               ///< Refused: Specified action not appropriate for specified instance
    DicomheroDimseStatusCodeSCPDoesNotSupportEventReports = 0xc315,                ///< Refused: SCP does not support Event Reports
    DicomheroDimseStatusCodeCanceled = 0xfe00,                                     ///< Terminated due to Cancel request
    DicomheroDimseStatusCodePending = 0xff00,                                      ///< Pending
    DicomheroDimseStatusCodePendingWithWarnings = 0xff01                           ///< Pending with warnings
};

typedef NS_ENUM(unsigned short, DicomheroDimseStatus)
{
    DicomheroDimseStatusSuccess = 0, ///< The operation was completed succesfully
    DicomheroDimseStatusWarning = 1, ///< The operation was completed with warnings
    DicomheroDimseStatusFailure = 2, ///< The operation failed
    DicomheroDimseStatusCancel  = 3, ///< The operation was canceled
    DicomheroDimseStatusPending = 4  ///< The operation is still running
};

typedef NS_ENUM(unsigned int, DicomheroDrawBitmapType)
{
    DicomheroDrawBitmapTypeRGB  = 0, ///< Generates a BMP image where each pixel contains 3 bytes (R, G and B)
    DicomheroDrawBitmapTypeBGR  = 1, ///< Generates a BMP image where each pixel contains 3 bytes (B, G and R)
    DicomheroDrawBitmapTypeRGBA = 2, ///< Generates a BMP image where each pixel contains 4 bytes (R, G, B and A)
    DicomheroDrawBitmapTypeBGRA = 3  ///< Generates a BMP image where each pixel contains 4 bytes (B, G, R and A)
};

typedef NS_ENUM(unsigned int, DicomheroBitDepth)
{
    DicomheroBitDepthU8 = 0,  ///< 8 bit integer, unsigned
    DicomheroBitDepthS8 = 1,  ///< 8 bit integer, signed
    DicomheroBitDepthU16 = 2, ///< 16 bit integer, unsigned
    DicomheroBitDepthS16 = 3, ///< 16 bit integer, signed
    DicomheroBitDepthU32 = 4, ///< 32 bit integer, unsigned
    DicomheroBitDepthS32 = 5  ///< 32 bit integer, signed
};

typedef NS_ENUM(unsigned int, DicomheroOverlayType)
{
    DicomheroOverlayTypeGraphic = 0,  ///< The overlay is a superimposed graphic
    DicomheroOverlayTypeROI = 1,      ///< 8The overlay specifies a region of interest
};




