/*
$fileHeader$
*/

#include "../include/imebra/tag.h"
#include "../include/imebra/dataSet.h"
#include "../implementation/dataImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"

namespace imebra
{

Tag::Tag()
{
    implementation::charsetsList::tCharsetsList tempCharset;
    m_pData = std::make_shared<imebra::implementation::data>(tempCharset);
}

Tag::Tag(const Tag& right): m_pData(right.m_pData)
{
}

Tag::~Tag()
{
}

Tag::Tag(std::shared_ptr<imebra::implementation::data> pData): m_pData(pData)
{
}

Tag& Tag::operator=(const Tag& right)
{
    m_pData = right.m_pData;
    return *this;
}


size_t Tag::getBuffersCount() const
{
    return m_pData->getBuffersCount();
}

bool Tag::bufferExists(size_t bufferId) const
{
    return m_pData->bufferExists(bufferId);
}

size_t Tag::getBufferSize(size_t bufferId) const
{
    return m_pData->getBufferSize(bufferId);
}

ReadingDataHandler Tag::getReadingDataHandler(size_t bufferId) const
{
    return ReadingDataHandler(m_pData->getReadingDataHandler(bufferId));
}

WritingDataHandler Tag::getWritingDataHandler(size_t bufferId, const std::string& tagVR)
{
    return WritingDataHandler(m_pData->getWritingDataHandler(bufferId, tagVR));
}

ReadingDataHandlerNumeric Tag::getReadingDataHandlerNumeric(size_t bufferId) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(m_pData->getReadingDataHandler(bufferId));
    if(numericHandler.get() == 0)
    {
        throw std::bad_cast();
    }
    return ReadingDataHandlerNumeric(numericHandler);
}

ReadingDataHandlerNumeric Tag::getReadingDataHandlerRaw(size_t bufferId) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericHandler = m_pData->getReadingDataHandlerRaw(bufferId);
    return ReadingDataHandlerNumeric(numericHandler);
}

WritingDataHandlerNumeric Tag::getWritingDataHandlerNumeric(size_t bufferId, const std::string& tagVR)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(m_pData->getWritingDataHandler(bufferId, tagVR));
    if(numericHandler.get() == 0)
    {
        throw std::bad_cast();
    }
    return WritingDataHandlerNumeric(numericHandler);
}

WritingDataHandlerNumeric Tag::getWritingDataHandlerRaw(size_t bufferId, const std::string& tagVR)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler = m_pData->getWritingDataHandlerRaw(bufferId, tagVR);
    return WritingDataHandlerNumeric(numericHandler);
}

StreamReader Tag::getStreamReader(size_t bufferId)
{
    return StreamReader(m_pData->getStreamReader(bufferId));
}

StreamWriter Tag::getStreamWriter(size_t bufferId, const std::string& dataType)
{
    return StreamWriter(m_pData->getStreamWriter(bufferId, dataType));
}

DataSet Tag::getSequenceItem(size_t dataSetId) const
{
    return DataSet(m_pData->getSequenceItem(dataSetId));
}

bool Tag::sequenceItemExists(size_t dataSetId) const
{
    return m_pData->dataSetExists(dataSetId);
}

void Tag::setSequenceItem(size_t dataSetId, const DataSet& dataSet)
{
    m_pData->setDataSet(dataSetId, dataSet.m_pDataSet);
}

void Tag::appendSequenceItem(const DataSet& dataSet)
{
    m_pData->appendDataSet(dataSet.m_pDataSet);
}

std::string Tag::getDataType(size_t bufferId) const
{
    return m_pData->getDataType(bufferId);
}

}
