/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero/dataSet.h"
#include "../include/dicomhero/tag.h"
#include "../include/dicomhero/lut.h"
#include "../include/dicomhero/date.h"
#include "../include/dicomhero/age.h"
#include "../include/dicomhero/patientName.h"
#include "../include/dicomhero/VOIDescription.h"
#include "../include/dicomhero/streamReader.h"
#include "../include/dicomhero/overlay.h"
#include "../implementation/dataSetImpl.h"
#include "../include/dicomhero/streamWriter.h"
#include "../include/dicomhero/uidsEnumeration.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/charsetConversionBaseImpl.h"
#include "../implementation/streamWriterImpl.h"
#include "../implementation/streamReaderImpl.h"
#include <typeinfo>
#include <memory>

namespace dicomhero
{

DataSet::DataSet(const DataSet& source): m_pDataSet(getDataSetImplementation(source))
{
}

DataSet::DataSet(const std::shared_ptr<dicomhero::implementation::dataSet>& pDataSet): m_pDataSet(pDataSet)
{
}

DataSet::~DataSet()
{
}

const std::shared_ptr<implementation::dataSet>& getDataSetImplementation(const DataSet& dataSet)
{
    return dataSet.m_pDataSet;
}

tagsIds_t DataSet::getTags() const
{
    DICOMHERO_FUNCTION_START();

    tagsIds_t returnTags;

    implementation::dataSet::tGroupsIds groups = m_pDataSet->getGroups();
    for(implementation::dataSet::tGroupsIds::const_iterator scanGroups(groups.begin()), endGroups(groups.end());
        scanGroups != endGroups;
        ++scanGroups)
    {
        std::uint32_t orders = m_pDataSet->getGroupsNumber(*scanGroups);
        for(std::uint32_t scanOrders(0); scanOrders != orders; ++scanOrders)
        {
            const implementation::dataSet::tTags tags = m_pDataSet->getGroupTags(*scanGroups, scanOrders);
            for(implementation::dataSet::tTags::const_iterator scanTags(tags.begin()), endTags(tags.end());
                scanTags != endTags;
                ++scanTags)
            {
                returnTags.push_back(TagId(*scanGroups, scanOrders, scanTags->first));
            }
        }
    }

    return returnTags;

    DICOMHERO_FUNCTION_END_LOG();
}

const Tag DataSet::getTag(const TagId& tagId) const
{
    DICOMHERO_FUNCTION_START();

    return Tag(m_pDataSet->getTag(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId()));

    DICOMHERO_FUNCTION_END_LOG();
}

const Image DataSet::getImage(size_t frameNumber) const
{
    DICOMHERO_FUNCTION_START();

    return Image(m_pDataSet->getImage(static_cast<std::uint32_t>(frameNumber)));

    DICOMHERO_FUNCTION_END_LOG();
}

const Overlay DataSet::getOverlay(size_t overlayNumber) const
{
    DICOMHERO_FUNCTION_START();

    return Overlay(m_pDataSet->getOverlay(static_cast<std::uint32_t>(overlayNumber)));

    DICOMHERO_FUNCTION_END();
}

const Image DataSet::getImageApplyModalityTransform(size_t frameNumber) const
{
    DICOMHERO_FUNCTION_START();

    return Image(m_pDataSet->getModalityImage((std::uint32_t)frameNumber));

    DICOMHERO_FUNCTION_END_LOG();
}

StreamReader DataSet::getStreamReader(const TagId& tagId, size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return StreamReader(m_pDataSet->getStreamReader(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));

    DICOMHERO_FUNCTION_END_LOG();
}

const DataSet DataSet::getSequenceItem(const TagId& tagId, size_t itemId) const
{
    DICOMHERO_FUNCTION_START();

    return DataSet(m_pDataSet->getSequenceItem(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), itemId));

    DICOMHERO_FUNCTION_END_LOG();
}

const LUT DataSet::getLUT(const TagId &tagId, size_t itemId) const
{
    DICOMHERO_FUNCTION_START();

    return LUT(m_pDataSet->getLut(tagId.getGroupId(), tagId.getTagId(), itemId));

    DICOMHERO_FUNCTION_END_LOG();
}

vois_t DataSet::getVOIs() const
{
    DICOMHERO_FUNCTION_START();

    vois_t vois;
    for(const std::shared_ptr<const implementation::VOIDescription>& voi: m_pDataSet->getVOIs())
    {
        vois.push_back(VOIDescription(voi));
    }

    return vois;

    DICOMHERO_FUNCTION_END_LOG();
}


const DataSet DataSet::getFunctionalGroupDataSet(size_t frameNumber) const
{
    DICOMHERO_FUNCTION_START();

    return DataSet(m_pDataSet->getFunctionalGroupDataSet(frameNumber));

    DICOMHERO_FUNCTION_END_LOG();
}


ReadingDataHandler DataSet::getReadingDataHandler(const TagId& tagId, size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return ReadingDataHandler(m_pDataSet->getReadingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));

    DICOMHERO_FUNCTION_END_LOG();
}

ReadingDataHandlerNumeric DataSet::getReadingDataHandlerNumeric(const TagId& tagId, size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return ReadingDataHandlerNumeric(m_pDataSet->getReadingDataHandlerNumeric(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));

    DICOMHERO_FUNCTION_END_LOG();
}

ReadingDataHandlerNumeric DataSet::getReadingDataHandlerRaw(const TagId& tagId, size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericHandler = m_pDataSet->getReadingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);
    return ReadingDataHandlerNumeric(numericHandler);

    DICOMHERO_FUNCTION_END_LOG();
}

bool DataSet::bufferExists(const TagId& tagId, size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->bufferExists(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int32_t DataSet::getInt32(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int32_t DataSet::getInt32(const TagId& tagId, size_t elementNumber, std::int32_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int32_t DataSet::getSignedLong(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int32_t DataSet::getSignedLong(const TagId& tagId, size_t elementNumber, std::int32_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DataSet::getUint32(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DataSet::getUint32(const TagId& tagId, size_t elementNumber, std::uint32_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DataSet::getUnsignedLong(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t DataSet::getUnsignedLong(const TagId& tagId, size_t elementNumber, std::uint32_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int16_t DataSet::getInt16(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int16_t DataSet::getInt16(const TagId& tagId, size_t elementNumber, std::int16_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint16_t DataSet::getUint16(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint16_t DataSet::getUint16(const TagId& tagId, size_t elementNumber, std::uint16_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int8_t DataSet::getInt8(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt8(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int8_t DataSet::getInt8(const TagId& tagId, size_t elementNumber, std::int8_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getInt8(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint8_t DataSet::getUint8(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint8(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint8_t DataSet::getUint8(const TagId& tagId, size_t elementNumber, std::uint8_t defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUint8(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

double DataSet::getDouble(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

float DataSet::getFloat(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getFloat(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

double DataSet::getDouble(const TagId& tagId, size_t elementNumber, double defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

float DataSet::getFloat(const TagId& tagId, size_t elementNumber, float defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getFloat(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::string DataSet::getString(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::string DataSet::getString(const TagId& tagId, size_t elementNumber, const std::string& defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

std::wstring DataSet::getUnicodeString(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);

    DICOMHERO_FUNCTION_END_LOG();
}

std::wstring DataSet::getUnicodeString(const TagId& tagId, size_t elementNumber, const std::wstring& defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);

    DICOMHERO_FUNCTION_END_LOG();
}

const Age DataSet::getAge(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return Age(m_pDataSet->getAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber));

    DICOMHERO_FUNCTION_END_LOG();
}

const Age DataSet::getAge(const TagId& tagId, size_t elementNumber, const Age& defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return Age(m_pDataSet->getAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, getAgeImplementation(defaultValue)));

    DICOMHERO_FUNCTION_END_LOG();
}

const Date DataSet::getDate(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return Date(m_pDataSet->getDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber));

    DICOMHERO_FUNCTION_END_LOG();
}

const Date DataSet::getDate(const TagId& tagId, size_t elementNumber, const Date& defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return Date(m_pDataSet->getDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, getDateImplementation(defaultValue)));

    DICOMHERO_FUNCTION_END_LOG();
}

const PatientName DataSet::getPatientName(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return PatientName(m_pDataSet->getPatientName(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber));

    DICOMHERO_FUNCTION_END_LOG();
}

const PatientName DataSet::getPatientName(const TagId& tagId, size_t elementNumber, const PatientName& defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return PatientName(m_pDataSet->getPatientName(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, getPatientNameImplementation(defaultValue)));

    DICOMHERO_FUNCTION_END_LOG();
}

const UnicodePatientName DataSet::getUnicodePatientName(const TagId& tagId, size_t elementNumber) const
{
    DICOMHERO_FUNCTION_START();

    return UnicodePatientName(m_pDataSet->getUnicodePatientName(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber));

    DICOMHERO_FUNCTION_END_LOG();
}

const UnicodePatientName DataSet::getUnicodePatientName(const TagId& tagId, size_t elementNumber, const UnicodePatientName& defaultValue) const
{
    DICOMHERO_FUNCTION_START();

    return UnicodePatientName(m_pDataSet->getUnicodePatientName(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, getUnicodePatientNameImplementation(defaultValue)));

    DICOMHERO_FUNCTION_END_LOG();
}

tagVR_t DataSet::getDataType(const TagId& tagId) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataSet->getDataType(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId());

    DICOMHERO_FUNCTION_END_LOG();
}

MutableDataSet::MutableDataSet(const MutableDataSet &source): DataSet(source)
{
}

MutableDataSet::MutableDataSet(): DataSet(std::make_shared<dicomhero::implementation::dataSet>(uidImplicitVRLittleEndian_1_2_840_10008_1_2, charsetsList_t()))
{
}

MutableDataSet::MutableDataSet(const std::shared_ptr<implementation::dataSet>& pDataSet): DataSet(pDataSet)
{
}

MutableDataSet::MutableDataSet(const std::string &transferSyntax): DataSet(std::make_shared<dicomhero::implementation::dataSet>(transferSyntax, charsetsList_t()))
{
}

MutableDataSet::MutableDataSet(const std::string &transferSyntax, const charsetsList_t &charsets):
    DataSet(std::make_shared<dicomhero::implementation::dataSet>(transferSyntax, charsets))
{
}

MutableDataSet::~MutableDataSet()
{
}

MutableTag MutableDataSet::getTagCreate(const TagId& tagId, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    return MutableTag(getDataSetImplementation(*this)->getTagCreate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), tagVR));

    DICOMHERO_FUNCTION_END_LOG();
}

MutableTag MutableDataSet::getTagCreate(const TagId& tagId)
{
    DICOMHERO_FUNCTION_START();

    return MutableTag(getDataSetImplementation(*this)->getTagCreate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId()));

    DICOMHERO_FUNCTION_END_LOG();
}

WritingDataHandler MutableDataSet::getWritingDataHandler(const TagId& tagId, size_t bufferId, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    return WritingDataHandler(getDataSetImplementation(*this)->getWritingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, tagVR));

    DICOMHERO_FUNCTION_END_LOG();
}

WritingDataHandler MutableDataSet::getWritingDataHandler(const TagId& tagId, size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return WritingDataHandler(getDataSetImplementation(*this)->getWritingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));

    DICOMHERO_FUNCTION_END_LOG();
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerNumeric(const TagId& tagId, size_t bufferId, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    return WritingDataHandlerNumeric(getDataSetImplementation(*this)->getWritingDataHandlerNumeric(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, tagVR));

    DICOMHERO_FUNCTION_END_LOG();
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerNumeric(const TagId& tagId, size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return WritingDataHandlerNumeric(getDataSetImplementation(*this)->getWritingDataHandlerNumeric(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));

    DICOMHERO_FUNCTION_END_LOG();
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerRaw(const TagId& tagId, size_t bufferId, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler = getDataSetImplementation(*this)->getWritingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, tagVR);
    return WritingDataHandlerNumeric(numericHandler);

    DICOMHERO_FUNCTION_END_LOG();
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerRaw(const TagId& tagId, size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler = getDataSetImplementation(*this)->getWritingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);
    return WritingDataHandlerNumeric(numericHandler);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setImage(size_t frameNumber, const Image& image, imageQuality_t quality)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setImage(static_cast<std::uint32_t>(frameNumber), getImageImplementation(image), quality);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setOverlay(size_t overlayNumber, const Overlay& overlay)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setOverlay(static_cast<std::uint32_t>(overlayNumber), getOverlayImplementation(overlay));

    DICOMHERO_FUNCTION_END();
}

StreamWriter MutableDataSet::getStreamWriter(const TagId& tagId, size_t bufferId, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    return StreamWriter(getDataSetImplementation(*this)->getStreamWriter(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, tagVR));

    DICOMHERO_FUNCTION_END_LOG();
}

StreamWriter MutableDataSet::getStreamWriter(const TagId& tagId, size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return StreamWriter(getDataSetImplementation(*this)->getStreamWriter(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));

    DICOMHERO_FUNCTION_END_LOG();
}

MutableDataSet MutableDataSet::appendSequenceItem(const TagId &tagId)
{
    DICOMHERO_FUNCTION_START();

    return MutableDataSet(getDataSetImplementation(*this)->appendSequenceItem(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId()));

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setInt32(const TagId& tagId, std::int32_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setSignedLong(const TagId& tagId, std::int32_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setInt32(const TagId& tagId, std::int32_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setSignedLong(const TagId& tagId, std::int32_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUint32(const TagId& tagId, std::uint32_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUnsignedLong(const TagId& tagId, std::uint32_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUint32(const TagId& tagId, std::uint32_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUnsignedLong(const TagId& tagId, std::uint32_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint32(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setInt8(const TagId& tagId, std::int8_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt8(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setInt8(const TagId& tagId, std::int8_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt8(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUint8(const TagId& tagId, std::uint8_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint8(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUint8(const TagId& tagId, std::uint8_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setInt16(const TagId& tagId, std::int16_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setInt16(const TagId& tagId, std::int16_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setInt16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUint16(const TagId& tagId, std::uint16_t newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUint16(const TagId& tagId, std::uint16_t newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUint16(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setDouble(const TagId& tagId, double newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setDouble(const TagId& tagId, double newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setFloat(const TagId& tagId, float newValue, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setFloat(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setFloat(const TagId& tagId, float newValue)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setFloat(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setString(const TagId& tagId, const std::string& newString, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setString(const TagId& tagId, const std::string& newString)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUnicodeString(const TagId& tagId, const std::wstring& newString, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString, tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUnicodeString(const TagId& tagId, const std::wstring& newString)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setAge(const TagId& tagId, const Age& age)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, getAgeImplementation(age));

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setDate(const TagId& tagId, const Date& date, tagVR_t tagVR)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, getDateImplementation(date), tagVR);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setDate(const TagId& tagId, const Date& date)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, getDateImplementation(date));

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setPatientName(const TagId& tagId, const PatientName& patientName)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setPatientName(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, getPatientNameImplementation(patientName));

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableDataSet::setUnicodePatientName(const TagId& tagId, const UnicodePatientName& patientName)
{
    DICOMHERO_FUNCTION_START();

    getDataSetImplementation(*this)->setUnicodePatientName(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, getUnicodePatientNameImplementation(patientName));

    DICOMHERO_FUNCTION_END_LOG();
}

} // namespace dicomhero
