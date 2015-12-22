#include "../../library/implementation/imebraImpl.h"
#include <gtest/gtest.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

using namespace puntoexe::imebra;

TEST(dicomDirTest, createDicomDir)
{
    std::shared_ptr<dicomDir> newDicomDir(std::make_shared<dicomDir>(std::make_shared<dataSet>()));

	std::shared_ptr<directoryRecord> pRootRecord(newDicomDir->getNewRecord());
	pRootRecord->getRecordDataSet()->setUnicodeString(0x10, 0, 0x10, 0, L"Surname");
	pRootRecord->setType(directoryRecord::patient);
	newDicomDir->setFirstRootRecord(pRootRecord);

	std::shared_ptr<directoryRecord> pNextRecord(newDicomDir->getNewRecord());
	pNextRecord->getRecordDataSet()->setUnicodeString(0x10, 0, 0x10, 0, L"Surname 1");
	pNextRecord->setType(directoryRecord::patient);
	pRootRecord->setNextRecord(pNextRecord);

	std::shared_ptr<directoryRecord> pImageRecord(newDicomDir->getNewRecord());
	pImageRecord->getRecordDataSet()->setUnicodeString(0x8, 0, 0x18, 0, L"1.2.840.34.56.78999654.235");
	pImageRecord->setType(directoryRecord::image);
        pImageRecord->setFilePart(0, L"folder");
        pImageRecord->setFilePart(1, L"file.dcm");

	pNextRecord->setFirstChildRecord(pImageRecord);

	std::shared_ptr<dataSet> dicomDirDataSet(newDicomDir->buildDataSet());

	std::shared_ptr<memory> streamMemory(new memory);
	std::shared_ptr<memoryStream> memStream(new memoryStream(streamMemory));
	std::shared_ptr<streamWriter> memWriter(new streamWriter(memStream));
	std::shared_ptr<imebra::codecs::dicomCodec> dicomWriter(new imebra::codecs::dicomCodec);
	dicomWriter->write(memWriter, dicomDirDataSet);
    memWriter.reset();

	std::shared_ptr<streamReader> memReader(new streamReader(memStream));
	std::shared_ptr<imebra::codecs::dicomCodec> dicomReader(new imebra::codecs::dicomCodec);
	std::shared_ptr<dataSet> readDataSet(dicomReader->read(memReader));

	std::shared_ptr<dicomDir> testDicomDir(new dicomDir(readDataSet));
	std::shared_ptr<directoryRecord> testRootRecord(testDicomDir->getFirstRootRecord());
    EXPECT_EQ(directoryRecord::patient, testRootRecord->getType());
    EXPECT_EQ(std::wstring(L"Surname"), testRootRecord->getRecordDataSet()->getUnicodeString(0x10, 0, 0x10, 0));

	std::shared_ptr<directoryRecord> testNextRecord(testRootRecord->getNextRecord());
    EXPECT_EQ(directoryRecord::patient, testNextRecord->getType());
    EXPECT_EQ(std::wstring(L"Surname 1"), testNextRecord->getRecordDataSet()->getUnicodeString(0x10, 0, 0x10, 0));

	std::shared_ptr<directoryRecord> testImageRecord(testNextRecord->getFirstChildRecord());
    EXPECT_EQ(directoryRecord::image, testImageRecord->getType());
    EXPECT_EQ(std::wstring(L"1.2.840.34.56.78999654.235"), testImageRecord->getRecordDataSet()->getUnicodeString(0x8, 0, 0x18, 0));
    EXPECT_EQ(std::wstring(L"folder"), testImageRecord->getFilePart(0));
    EXPECT_EQ(std::wstring(L"file.dcm"), testImageRecord->getFilePart(1));
}


} // namespace tests

} // namespace imebra

} // namespace puntoexe
