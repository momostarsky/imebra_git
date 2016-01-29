#include "../include/imebra/exceptions.h"

namespace imebra
{

LutError::LutError(const std::string& message): std::runtime_error(message)
{}

LutWrongIndexError::LutWrongIndexError(const std::string& message): LutError(message)
{}

LutCorruptedError::LutCorruptedError(const std::string& message): LutError(message)
{}

MissingDataElementError::MissingDataElementError(const std::string& message): std::runtime_error(message)
{}

MissingGroupError::MissingGroupError(const std::string& message): MissingDataElementError(message)
{}

MissingTagError::MissingTagError(const std::string& message): MissingDataElementError(message)
{}

MissingBufferError::MissingBufferError(const std::string& message): MissingDataElementError(message)
{}

MissingItemError::MissingItemError(const std::string& message): MissingDataElementError(message)
{}

TagContentError::TagContentError(const std::string &message): std::runtime_error(message)
{}

InvalidTagContentError::InvalidTagContentError(const std::string &message): TagContentError(message)
{}

StreamError::StreamError(const std::string& message): std::runtime_error(message)
{}

StreamOpenError::StreamOpenError(const std::string& message): StreamError(message)
{}

StreamReadError::StreamReadError(const std::string& message): StreamError(message)
{}

StreamWriteError::StreamWriteError(const std::string& message): StreamError(message)
{}

StreamCloseError::StreamCloseError(const std::string& message): StreamError(message)
{}

BufferError::BufferError(const std::string& message): std::runtime_error(message)
{}

BufferUnknownTypeError::BufferUnknownTypeError(const std::string& message): BufferError(message)
{}

CharsetConversionError::CharsetConversionError(const std::string& message): std::runtime_error(message)
{}

CharsetConversionNoTableError::CharsetConversionNoTableError(const std::string& message): CharsetConversionError(message)
{}

CharsetConversionNoSupportedTableError::CharsetConversionNoSupportedTableError(const std::string& message): CharsetConversionError(message)
{}

CharsetsListError::CharsetsListError(const std::string& message): std::runtime_error(message)
{}

CharsetListDiffDefaultError::CharsetListDiffDefaultError(const std::string& message): CharsetsListError(message)
{}

CodecError::CodecError(const std::string& message): std::runtime_error(message)
{}

CodecWrongFormatError::CodecWrongFormatError(const std::string& message): CodecError(message)
{}

CodecCorruptedFileError::CodecCorruptedFileError(const std::string& message): CodecError(message)
{}

CodecWrongTransferSyntaxError::CodecWrongTransferSyntaxError(const std::string& message): CodecError(message)
{}

CodecImageTooBigError::CodecImageTooBigError(const std::string& message): CodecError(message)
{}

DataHandlerError::DataHandlerError(const std::string& message): std::runtime_error(message)
{}

DataHandlerDeniedConversionError::DataHandlerDeniedConversionError(const std::string &message): DataHandlerError(message)
{}

DataHandlerConversionError::DataHandlerConversionError(const std::string &message)
{}

DataHandlerCorruptedBufferError::DataHandlerCorruptedBufferError(const std::string &message): DataHandlerError(message)
{}

DataSetError::DataSetError(const std::string& message): std::runtime_error(message)
{}

DataSetDifferentFormatError::DataSetDifferentFormatError(const std::string& message): DataSetError(message)
{}

DataSetUnknownTransferSyntaxError::DataSetUnknownTransferSyntaxError(const std::string& message): DataSetError(message)
{}

DataSetWrongFrameError::DataSetWrongFrameError(const std::string& message): DataSetError(message)
{}

DataSetOldFormatError::DataSetOldFormatError(const std::string& message): DataSetError(message)
{}

DataSetImageDoesntExistError::DataSetImageDoesntExistError(const std::string& message): DataSetError(message)
{}

DataSetCorruptedOffsetTableError::DataSetCorruptedOffsetTableError(const std::string& message): DataSetError(message)
{}

DicomDirError::DicomDirError(const std::string& message): std::runtime_error(message)
{}

DicomDirCircularReferenceError::DicomDirCircularReferenceError(const std::string& message): DicomDirError(message)
{}

DicomDirUnknownDirectoryRecordTypeError::DicomDirUnknownDirectoryRecordTypeError(const std::string& message): DicomDirError(message)
{}

HuffmanError::HuffmanError(const std::string& message): std::runtime_error(message)
{}

HuffmanCreateTableError::HuffmanCreateTableError(const std::string& message): HuffmanError(message)
{}

HuffmanReadError::HuffmanReadError(const std::string& message): HuffmanError(message)
{}

HuffmanWriteError::HuffmanWriteError(const std::string& message): HuffmanError(message)
{}

ImageError::ImageError(const std::string& message): std::runtime_error(message)
{}

ImageUnknownDepthError::ImageUnknownDepthError(const std::string& message): ImageError(message)
{}

ImageUnknownColorSpaceError::ImageUnknownColorSpaceError(const std::string& message): ImageError(message)
{}

ImageInvalidSizeError::ImageInvalidSizeError(const std::string& message): ImageError(message)
{}

TransformError::TransformError(const std::string& message): std::runtime_error(message)
{}

TransformInvalidAreaError::TransformInvalidAreaError(const std::string& message): TransformError(message)
{}

TransformsChainError::TransformsChainError(const std::string& what): TransformError(what)
{}

ColorTransformError::ColorTransformError(const std::string& message): TransformError(message)
{}

ColorTransformWrongColorSpaceError::ColorTransformWrongColorSpaceError(const std::string& message): ColorTransformError(message)
{}

ColorTransformWrongSizeError::ColorTransformWrongSizeError(const std::string& message): ColorTransformError(message)
{}

ColorTransformsFactoryError::ColorTransformsFactoryError(const std::string& message): TransformError(message)
{}

ColorTransformsFactoryNoTransformError::ColorTransformsFactoryNoTransformError(const std::string& message): ColorTransformsFactoryError(message)
{}

TransformHighBitError::TransformHighBitError(const std::string& message): TransformError(message)
{}

TransformHighBitDifferentColorSpacesError::TransformHighBitDifferentColorSpacesError(const std::string& message): TransformHighBitError(message)
{}

StreamEOFError::StreamEOFError(const std::string& message): StreamError(message)
{}

StreamJpegTagInStreamError::StreamJpegTagInStreamError(const std::string& message): StreamError(message)
{}

ModalityVOILUTError::ModalityVOILUTError(const std::string& message): TransformError(message)
{}

PALETTECOLORToRGBError::PALETTECOLORToRGBError(const std::string& message): ColorTransformError(message)
{}

DicomCodecError::DicomCodecError(const std::string& message): CodecError(message)
{}

DicomCodecDepthLimitReachedError::DicomCodecDepthLimitReachedError(const std::string&message): DicomCodecError(message)
{}

JpegCodecError::JpegCodecError(const std::string& message): CodecError(message)
{}

JpegCodecCannotHandleSyntaxError::JpegCodecCannotHandleSyntaxError(const std::string& message): JpegCodecError(message)
{}

}
