/*
$fileHeader$
*/

#include "../include/imebra/tagContent.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/dataImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"

namespace imebra
{

TagContent::TagContent()
{
    implementation::charsetsList::tCharsetsList tempCharset;
    m_pData = std::make_shared<imebra::implementation::data>(tempCharset);
}

TagContent::TagContent(const TagContent& right): m_pData(right.m_pData)
{
}

TagContent::~TagContent()
{
}

TagContent::TagContent(std::shared_ptr<imebra::implementation::data> pData): m_pData(pData)
{
}

TagContent& TagContent::operator=(const TagContent& right)
{
    m_pData = right.m_pData;
    return *this;
}


size_t TagContent::getBuffersCount() const
{
    return m_pData->getBuffersCount();
}

bool TagContent::bufferExists(size_t bufferId) const
{
    return m_pData->bufferExists(bufferId);
}

size_t TagContent::getBufferSizeThrow(size_t bufferId) const
{
    return m_pData->getBufferSizeThrow(bufferId);
}

ReadingDataHandler TagContent::getReadingDataHandlerThrow(size_t bufferId) const
{
    return ReadingDataHandler(m_pData->getReadingDataHandlerThrow(bufferId));
}

WritingDataHandler TagContent::getWritingDataHandler(size_t bufferId, const std::string& defaultType)
{
    return WritingDataHandler(m_pData->getWritingDataHandler(bufferId, defaultType));
}

ReadingDataHandlerNumeric TagContent::getReadingDataHandlerNumericThrow(size_t bufferId) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(m_pData->getReadingDataHandlerThrow(bufferId));
    if(numericHandler.get() == 0)
    {
        throw std::bad_cast();
    }
    return ReadingDataHandlerNumeric(numericHandler);
}

WritingDataHandlerNumeric TagContent::getWritingDataHandlerNumeric(size_t bufferId, const std::string& defaultType)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(m_pData->getWritingDataHandler(bufferId, defaultType));
    if(numericHandler.get() == 0)
    {
        throw std::bad_cast();
    }
    return WritingDataHandlerNumeric(numericHandler);
}

StreamReader TagContent::getStreamReaderThrow(size_t bufferId)
{
    return StreamReader(m_pData->getStreamReaderThrow(bufferId));
}

StreamWriter TagContent::getStreamWriter(size_t bufferId, const std::string& dataType)
{
    return StreamWriter(m_pData->getStreamWriter(bufferId, dataType));
}

DataSet TagContent::getSequenceItemThrow(size_t dataSetId) const
{
    return DataSet(m_pData->getSequenceItemThrow(dataSetId));
}

bool TagContent::dataSetExists(size_t dataSetId) const
{
    return m_pData->dataSetExists(dataSetId);
}

void TagContent::setDataSet(size_t dataSetId, const DataSet& dataSet)
{
    m_pData->setDataSet(dataSetId, dataSet.m_pDataSet);
}

void TagContent::appendDataSet(const DataSet& dataSet)
{
    m_pData->appendDataSet(dataSet.m_pDataSet);
}

std::string TagContent::getDataTypeThrow(size_t bufferId) const
{
    return m_pData->getDataTypeThrow(bufferId);
}

}
