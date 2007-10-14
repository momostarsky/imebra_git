#include <cppunit/extensions/HelperMacros.h>
#include "streamBitsTest.h"

#include "../../imebra/include/imebra.h"

#include <vector>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

CPPUNIT_TEST_SUITE_REGISTRATION(puntoexe::imebra::tests::streamBitsTest);


void streamBitsTest::test()
{
	ptr<memory> myMemory(new memory);
	ptr<baseStream> theMemoryStream(new memoryStream(myMemory));
	ptr<streamWriter> writer(new streamWriter(theMemoryStream));
	
	imbxUint8 tagByte;
	writer->m_pTagByte = &tagByte;

	std::vector<imbxUint8> bitsNumber(4000);
	std::vector<imbxUint32> bitsValue(4000);
	for(size_t fillValues = 0; fillValues < bitsValue.size(); ++fillValues)
	{
		imbxUint8 bits =  rand() * 16 / RAND_MAX;
		if(bits == 0) bits = 4;
		imbxUint32 maxValue = (1 << bits) - 1;
		imbxUint32 value = rand() * maxValue / RAND_MAX;
		bitsNumber[fillValues] = bits;
		bitsValue[fillValues] = value;
		writer->writeBits(&value, bits);
	}
	writer->resetOutBitsBuffer();

	ptr<streamReader> reader(new streamReader(theMemoryStream));
	reader->m_pTagByte = &tagByte;

	for(size_t readValues = 0; readValues < bitsValue.size(); ++readValues)
	{
		imbxUint32 value;
		reader->readBits(&value, bitsNumber[readValues]);
		CPPUNIT_ASSERT(value == bitsValue[readValues]);
	}
}




} // namespace tests

} // namespace imebra

} // namespace puntoexe