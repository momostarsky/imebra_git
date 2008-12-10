#include <cppunit/extensions/HelperMacros.h>
#include "dicomDirTest.h"

#include "../../imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::dicomDirTest);

using namespace puntoexe::imebra;

void dicomDirTest::createDicomDir()
{
	ptr<dicomDir> newDicomDir(new dicomDir(new dataSet));

	ptr<directoryRecord> pRootRecord(newDicomDir->getNewRecord());
	pRootRecord->getRecordDataSet()->setUnicodeString(0x10, 0, 0x10, 0, L"Surname");
	pRootRecord->setType(directoryRecord::patient);
	newDicomDir->setFirstRootRecord(pRootRecord);

	ptr<directoryRecord> pNextRecord(newDicomDir->getNewRecord());
	pNextRecord->getRecordDataSet()->setUnicodeString(0x10, 0, 0x10, 0, L"Surname 1");
	pNextRecord->setType(directoryRecord::patient);
	pRootRecord->setNextRecord(pNextRecord);

	ptr<directoryRecord> pImageRecord(newDicomDir->getNewRecord());
	pImageRecord->getRecordDataSet()->setUnicodeString(0x8, 0, 0x24, 0, L"1.2.840.34.56.78999654.235");
	pImageRecord->setType(directoryRecord::image);
	pNextRecord->setFirstChildRecord(pImageRecord);

	ptr<dataSet> dicomDirDataSet(newDicomDir->getDirectoryDataSet());
	newDicomDir.release();

	ptr<memory> streamMemory(new memory);
	ptr<memoryStream> memStream(new memoryStream(streamMemory));
	ptr<streamWriter> memWriter(new streamWriter(memStream));
	ptr<imebra::codecs::dicomCodec> dicomWriter(new imebra::codecs::dicomCodec);
	dicomWriter->write(memWriter, dicomDirDataSet);
	memWriter.release();

	ptr<streamReader> memReader(new streamReader(memStream));
	ptr<imebra::codecs::dicomCodec> dicomReader(new imebra::codecs::dicomCodec);
	ptr<dataSet> readDataSet(dicomReader->read(memReader));

	ptr<dicomDir> testDicomDir(new dicomDir(readDataSet));
	ptr<directoryRecord> testRootRecord(testDicomDir->getFirstRootRecord());
	CPPUNIT_ASSERT(testRootRecord->getType() == directoryRecord::patient);
	CPPUNIT_ASSERT(testRootRecord->getRecordDataSet()->getUnicodeString(0x10, 0, 0x10, 0) == L"Surname");

	ptr<directoryRecord> testNextRecord(testRootRecord->getNextRecord());
	CPPUNIT_ASSERT(testNextRecord->getType() == directoryRecord::patient);
	CPPUNIT_ASSERT(testNextRecord->getRecordDataSet()->getUnicodeString(0x10, 0, 0x10, 0) == L"Surname 1");

	ptr<directoryRecord> testImageRecord(testRootRecord->getFirstChildRecord());
	CPPUNIT_ASSERT(testImageRecord->getType() == directoryRecord::image);
	CPPUNIT_ASSERT(testNextRecord->getRecordDataSet()->getUnicodeString(0x8, 0, 0x24, 0) == L"1.2.840.34.56.78999654.235");
}


} // namespace tests

} // namespace imebra

} // namespace puntoexe