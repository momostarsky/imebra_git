#include "../library/imebra/include/imebra.h"

#include <vector>
#include <cstdlib>
#include <gtest/gtest.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{


TEST(streamBitsTest, test)
{
	std::srand(100);
	ptr<memory> myMemory(new memory);
	ptr<baseStream> theMemoryStream(new memoryStream(myMemory));
	ptr<streamWriter> writer(new streamWriter(theMemoryStream));
	
	writer->m_bJpegTags = true;

	std::vector<std::uint8_t> bitsNumber(4000);
	std::vector<std::uint32_t> bitsValue(4000);
	for(size_t fillValues = 0; fillValues < bitsValue.size(); ++fillValues)
	{
		std::uint8_t bits =  rand() * 16 / RAND_MAX;
		if(bits == 0) bits = 4;
		std::uint32_t maxValue = (1 << bits) - 1;
		std::uint32_t value = std::rand() * maxValue / RAND_MAX;
		bitsNumber[fillValues] = bits;
		bitsValue[fillValues] = value;
		writer->writeBits(value, bits);
	}
	writer->resetOutBitsBuffer();
	writer->flushDataBuffer();

	{
		ptr<streamReader> reader(new streamReader(theMemoryStream));
		reader->m_bJpegTags = true;

		for(size_t readValues = 0; readValues < bitsValue.size(); ++readValues)
		{
			std::uint32_t value(reader->readBits(bitsNumber[readValues]));
            EXPECT_EQ(bitsValue[readValues], value);
		}
	}

	{
		ptr<streamReader> reader(new streamReader(theMemoryStream));
		reader->m_bJpegTags = true;

		for(size_t readValues = 0; readValues < bitsValue.size(); ++readValues)
		{
			std::uint32_t value(0);
			for(std::uint8_t count(bitsNumber[readValues]); count != 0; --count)
			{
				value <<= 1;
				value |= reader->readBit();
			}
            EXPECT_EQ(bitsValue[readValues], value);
		}
	}

	{
		ptr<streamReader> reader(new streamReader(theMemoryStream));
		reader->m_bJpegTags = true;

		for(size_t readValues = 0; readValues < bitsValue.size(); ++readValues)
		{
			std::uint32_t value(0);
			for(std::uint8_t count(bitsNumber[readValues]); count != 0; --count)
			{
				reader->addBit(&value);
			}
            EXPECT_EQ(bitsValue[readValues], value);
		}
	}

}




} // namespace tests

} // namespace imebra

} // namespace puntoexe
