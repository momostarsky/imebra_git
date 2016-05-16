#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(unicodeStringHandlerTest, unicodeTest)
{

	// Try a cyrillic/arabic patient name
    std::wstring patientName0 = L"??\x0628\x062a\x062b\x062f^\0x400\0x410\0x420";
	std::wstring patientName1 = L"\0x420\x062a\x062b^\0x400\0x410\x0628\x062a";

    ReadWriteMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        DataSet testDataSet(charsets);
        testDataSet.setString(TagId(0x2, 0x10), 0, "1.2.840.10008.1.2.1");

        {
            std::unique_ptr<WritingDataHandler> handler(testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0));

            handler->setUnicodeString(0, patientName0);
            handler->setUnicodeString(1, patientName1);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
	}

	{
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        std::unique_ptr<DataSet> testDataSet(CodecFactory::load(reader));

        EXPECT_EQ(patientName0, testDataSet->getUnicodeString(TagId(0x0010, 0x0010), 0, 0));
        EXPECT_EQ(patientName1, testDataSet->getUnicodeString(TagId(0x0010, 0x0010), 0, 1));
	}
}

TEST(unicodeStringHandlerTest, iso2022Test)
{
	// Try a cyrillic /greek/latin patient name
    std::wstring patientName0 = L"???\x0430\x0402\x0403\x00c9^\x00d0\x0410\x00d5";
	std::wstring patientName1 = L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072";

    ReadWriteMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO 2022 IR 6");
        DataSet testDataSet(charsets);
        testDataSet.setString(TagId(0x2, 0x10), 0, "1.2.840.10008.1.2.1");

        {
            std::unique_ptr<WritingDataHandler> handler(testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0));

            handler->setUnicodeString(0, patientName0);
            handler->setUnicodeString(1, patientName1);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

	{
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        std::unique_ptr<DataSet> testDataSet(CodecFactory::load(reader));

        EXPECT_EQ(patientName0, testDataSet->getUnicodeString(TagId(0x0010, 0x0010), 0, 0));
        EXPECT_EQ(patientName1, testDataSet->getUnicodeString(TagId(0x0010, 0x0010), 0, 1));
    }
}


TEST(unicodeStringHandlerTest, supplementaryUnicodeChars)
{
    // Try supplementary chars
    std::wstring patientName0 = L"\x2070e\x20731\x20779\x20c53^\x00d0\x0410\x00d5";
    std::wstring patientName1 = L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072";

    ReadWriteMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 192");
        DataSet testDataSet(charsets);
        testDataSet.setString(TagId(0x2, 0x10), 0, "1.2.840.10008.1.2.1");

        {
            std::unique_ptr<WritingDataHandler> handler(testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0));

            handler->setUnicodeString(0, patientName0);
            handler->setUnicodeString(1, patientName1);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);

        CodecFactory::save(testDataSet, "/home/paolo/testcharset.dcm", codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        std::unique_ptr<DataSet> testDataSet(CodecFactory::load(reader));

        EXPECT_EQ(patientName0, testDataSet->getUnicodeString(TagId(0x0010, 0x0010), 0, 0));
        EXPECT_EQ(patientName1, testDataSet->getUnicodeString(TagId(0x0010, 0x0010), 0, 1));
    }
}


} // namespace tests

} // namespace imebra

