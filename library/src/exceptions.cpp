#include "../include/imebra/exceptions.h"

namespace imebra
{

lutException::lutException(const std::string& message): std::runtime_error(message)
{}

lutExceptionWrongIndex::lutExceptionWrongIndex(const std::string& message): lutException(message)
{}

lutExceptionCorrupted::lutExceptionCorrupted(const std::string& message): lutException(message)
{}

missingDataElement::missingDataElement(const std::string& message): std::runtime_error(message)
{}

missingGroup::missingGroup(const std::string& message): missingDataElement(message)
{}

missingTag::missingTag(const std::string& message): missingDataElement(message)
{}

missingBuffer::missingBuffer(const std::string& message): missingDataElement(message)
{}

missingItem::missingItem(const std::string& message): missingDataElement(message)
{}

streamException::streamException(const std::string& message): std::runtime_error(message)
{}

streamExceptionOpen::streamExceptionOpen(const std::string& message): streamException(message)
{}

streamExceptionRead::streamExceptionRead(const std::string& message): streamException(message)
{}

streamExceptionWrite::streamExceptionWrite(const std::string& message): streamException(message)
{}

streamExceptionClose::streamExceptionClose(const std::string& message): streamException(message)
{}

bufferException::bufferException(const std::string& message): std::runtime_error(message)
{}

bufferExceptionUnknownType::bufferExceptionUnknownType(const std::string& message): bufferException(message)
{}

charsetConversionException::charsetConversionException(const std::string& message): std::runtime_error(message)
{}

charsetConversionExceptionNoTable::charsetConversionExceptionNoTable(const std::string& message): charsetConversionException(message)
{}

charsetConversionExceptionNoSupportedTable::charsetConversionExceptionNoSupportedTable(const std::string& message): charsetConversionException(message)
{}

charsetConversionExceptionUtfSizeNotSupported::charsetConversionExceptionUtfSizeNotSupported(const std::string& message): charsetConversionException(message)
{}

charsetsListException::charsetsListException(const std::string& message): std::runtime_error(message)
{}

charsetListExceptionDiffDefault::charsetListExceptionDiffDefault(const std::string& message): charsetsListException(message)
{}

codecException::codecException(const std::string& message): std::runtime_error(message)
{}

codecExceptionWrongFormat::codecExceptionWrongFormat(const std::string& message): codecException(message)
{}

codecExceptionCorruptedFile::codecExceptionCorruptedFile(const std::string& message): codecException(message)
{}

codecExceptionWrongTransferSyntax::codecExceptionWrongTransferSyntax(const std::string& message): codecException(message)
{}

codecExceptionImageTooBig::codecExceptionImageTooBig(const std::string& message): codecException(message)
{}

dataHandlerStringUnicodeException::dataHandlerStringUnicodeException(const std::string& message): std::runtime_error(message)
{}

dataHandlerStringUnicodeExceptionUnknownCharset::dataHandlerStringUnicodeExceptionUnknownCharset(const std::string& message): dataHandlerStringUnicodeException(message)
{}

dataSetException::dataSetException(const std::string& message): std::runtime_error(message)
{}

dataSetExceptionDifferentFormat::dataSetExceptionDifferentFormat(const std::string& message): dataSetException(message)
{}

dataSetExceptionUnknownTransferSyntax::dataSetExceptionUnknownTransferSyntax(const std::string& message): dataSetException(message)
{}

dataSetExceptionWrongFrame::dataSetExceptionWrongFrame(const std::string& message): dataSetException(message)
{}

dataSetExceptionOldFormat::dataSetExceptionOldFormat(const std::string& message): dataSetException(message)
{}

dataSetImageDoesntExist::dataSetImageDoesntExist(const std::string& message): dataSetException(message)
{}

dataSetCorruptedOffsetTable::dataSetCorruptedOffsetTable(const std::string& message): dataSetException(message)
{}

dicomDirException::dicomDirException(const std::string& message): std::runtime_error(message)
{}

dicomDirCircularReferenceException::dicomDirCircularReferenceException(const std::string& message): dicomDirException(message)
{}

dicomDirUnknownDirectoryRecordType::dicomDirUnknownDirectoryRecordType(const std::string& message): dicomDirException(message)
{}

drawBitmapException::drawBitmapException(const std::string& message): std::runtime_error(message)
{}

drawBitmapExceptionInvalidArea::drawBitmapExceptionInvalidArea(const std::string& message): drawBitmapException(message)
{}

huffmanException::huffmanException(const std::string& message): std::runtime_error(message)
{}

huffmanExceptionCreateTable::huffmanExceptionCreateTable(const std::string& message): huffmanException(message)
{}

huffmanExceptionRead::huffmanExceptionRead(const std::string& message): huffmanException(message)
{}

huffmanExceptionWrite::huffmanExceptionWrite(const std::string& message): huffmanException(message)
{}

imageException::imageException(const std::string& message): std::runtime_error(message)
{}

imageExceptionUnknownDepth::imageExceptionUnknownDepth(const std::string& message): imageException(message)
{}

imageExceptionUnknownColorSpace::imageExceptionUnknownColorSpace(const std::string& message): imageException(message)
{}

imageExceptionInvalidSize::imageExceptionInvalidSize(const std::string& message): imageException(message)
{}

transformException::transformException(const std::string& message): std::runtime_error(message)
{}

transformExceptionInvalidArea::transformExceptionInvalidArea(const std::string& message): transformException(message)
{}

transformsChainException::transformsChainException(const std::string& what): transformException(what)
{}

colorTransformException::colorTransformException(const std::string& message): transformException(message)
{}

colorTransformExceptionWrongColorSpace::colorTransformExceptionWrongColorSpace(const std::string& message): colorTransformException(message)
{}

colorTransformExceptionWrongSize::colorTransformExceptionWrongSize(const std::string& message): colorTransformException(message)
{}

colorTransformsFactoryException::colorTransformsFactoryException(const std::string& message): transformException(message)
{}

colorTransformsFactoryExceptionNoTransform::colorTransformsFactoryExceptionNoTransform(const std::string& message): colorTransformsFactoryException(message)
{}

transformHighBitException::transformHighBitException(const std::string& message): transformException(message)
{}

transformHighBitDifferentColorSpaces::transformHighBitDifferentColorSpaces(const std::string& message): transformHighBitException(message)
{}

streamExceptionEOF::streamExceptionEOF(const std::string& message): streamException(message)
{}

streamJpegTagInStream::streamJpegTagInStream(const std::string& message): streamException(message)
{}

modalityVOILUTException::modalityVOILUTException(const std::string& message): transformException(message)
{}

PALETTECOLORToRGBException::PALETTECOLORToRGBException(const std::string& message): colorTransformException(message)
{}

dicomCodecException::dicomCodecException(const std::string& message): codecException(message)
{}

dicomCodecExceptionDepthLimitReached::dicomCodecExceptionDepthLimitReached(const std::string&message): dicomCodecException(message)
{}

jpegCodecException::jpegCodecException(const std::string& message): codecException(message)
{}

jpegCodecCannotHandleSyntax::jpegCodecCannotHandleSyntax(const std::string& message): jpegCodecException(message)
{}

}
