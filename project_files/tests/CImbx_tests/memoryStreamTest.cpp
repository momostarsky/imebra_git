#include <cppunit/extensions/HelperMacros.h>
#include "memoryStreamTest.h"

#include "../../imebra/include/imebra.h"

#include <vector>
#include <stdlib.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::memoryStreamTest);


// A buffer initialized to a default data type should use the data type OB
void memoryStreamTest::test()
{
	ptr<memory> myMemory(new memory);
	ptr<baseStream> theMemoryStream(new memoryStream(myMemory));
	ptr<streamWriter> writer(new streamWriter(theMemoryStream));

	std::vector<imbxUint8> values(4000);
	for(size_t fillValues = 0; fillValues < values.size(); ++fillValues)
	{
		imbxUint8 value =  rand() * 255 / RAND_MAX;
		values[fillValues] = value;
		writer->write(&value, 1);
	}
	writer->flushDataBuffer();

	ptr<streamReader> reader(new streamReader(theMemoryStream));

	for(size_t readValues = 0; readValues < values.size(); ++readValues)
	{
		imbxUint8 value;
		reader->read(&value, 1);
		CPPUNIT_ASSERT(value == values[readValues]);
	}
}

void memoryStreamTest::testBytes()
{
	ptr<memory> myMemory(new memory);
	ptr<baseStream> theMemoryStream(new memoryStream(myMemory));
	ptr<streamWriter> writer(new streamWriter(theMemoryStream));
	imbxUint8 tagByte;
	writer->m_pTagByte = &tagByte;

	std::vector<imbxUint8> values(4000);
	for(size_t fillValues = 0; fillValues < values.size(); ++fillValues)
	{
		imbxUint8 value =  rand() * 255 / RAND_MAX;
		if(fillValues % 10 == 0)
		{
			value = 0xff;
		}
		values[fillValues] = value;
		writer->writeByte(&value);
	}
	writer->flushDataBuffer();

	ptr<streamReader> reader(new streamReader(theMemoryStream));
	reader->m_pTagByte = &tagByte;

	for(size_t readValues = 0; readValues < values.size(); ++readValues)
	{
		imbxUint8 value;
		reader->readByte(&value);
		CPPUNIT_ASSERT(value == values[readValues]);
	}
}


} // namespace tests

} // namespace imebra

} // namespace puntoexe