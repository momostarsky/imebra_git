#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(stringHandlerTest, DSTest)
{
    {
        DataSet testDataSet;
        testDataSet.setDouble(TagId(0x0028, 0x1051), 0, 0.000001, tagVR_t::DS);
        std::string decimalString = testDataSet.getString(TagId(0x0028, 0x1051), 0, 0);
        ASSERT_TRUE(decimalString == "1e-006" || decimalString == "1e-06" || decimalString == "1e-6");
        double decimalValue = testDataSet.getDouble(TagId(0x0028, 0x1051), 0, 0);
        ASSERT_FLOAT_EQ(0.000001, decimalValue);
    }

    {
        DataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), 0, "-2e-8", tagVR_t::DS);
        double decimalValue = testDataSet.getDouble(TagId(0x0028, 0x1051), 0, 0);
        ASSERT_FLOAT_EQ(-0.00000002, decimalValue);
    }

    {
        DataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), 0, "Hello", tagVR_t::DS);
        ASSERT_THROW(testDataSet.getDouble(TagId(0x0028, 0x1051), 0, 0), DataHandlerConversionError);
    }
}


TEST(stringHandlerTest, ISTest)
{
    {
        DataSet testDataSet;
        testDataSet.setDouble(TagId(0x0028, 0x1051), 0, 12.004, tagVR_t::IS);
        ASSERT_EQ("12", testDataSet.getString(TagId(0x0028, 0x1051), 0, 0));
        ASSERT_EQ(12, testDataSet.getSignedLong(TagId(0x0028, 0x1051), 0, 0));
        ASSERT_FLOAT_EQ(12.0, testDataSet.getDouble(TagId(0x0028, 0x1051), 0, 0));
    }

    {
        DataSet testDataSet;
        testDataSet.setSignedLong(TagId(0x0028, 0x1051), 0, 20, tagVR_t::IS);
        ASSERT_EQ("20", testDataSet.getString(TagId(0x0028, 0x1051), 0, 0));
        ASSERT_EQ(20, testDataSet.getSignedLong(TagId(0x0028, 0x1051), 0, 0));
        ASSERT_FLOAT_EQ(20.0, testDataSet.getDouble(TagId(0x0028, 0x1051), 0, 0));
    }

    {
        DataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), 0, "123456789012", tagVR_t::IS);
        ASSERT_THROW(testDataSet.setString(TagId(0x0028, 0x1051), 0, "1234567890123", tagVR_t::IS), DataHandlerInvalidDataError);
    }

}


TEST(stringHandlerTest, AETest)
{
    DataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), 0, "0123456789012345", tagVR_t::AE);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));

    testDataSet.setString(TagId(0x0010, 0x0010), 0, "012345678901234", tagVR_t::AE);
    ASSERT_EQ("012345678901234", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));

    ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), 0, "01234567890123456", tagVR_t::AE), DataHandlerInvalidDataError);
}


TEST(stringHandlerTest, LOTest)
{
    DataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), 0, "0123456789012345", tagVR_t::LO);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));

    {
        std::string longString((size_t)63, 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), 0, longString, tagVR_t::LO);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));
    }

    {
        std::string longString((size_t)64, 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), 0, longString, tagVR_t::LO);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));
    }

    {
        std::string longString((size_t)65, 'a');
        ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), 0, longString, tagVR_t::LO), DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, LTTest)
{
    DataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), 0, "0123456789012345", tagVR_t::LT);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));

    {
        std::string longString((size_t)63, 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), 0, longString, tagVR_t::LT);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));
    }

    {
        std::string longString((size_t)10240, 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), 0, longString, tagVR_t::LT);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));
    }

    {
        std::string longString((size_t)10241, 'a');
        ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), 0, longString, tagVR_t::LT), DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, PNTest)
{
    DataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), 0, "PatientName", tagVR_t::PN);
    ASSERT_EQ("PatientName", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));

    {
        std::unique_ptr<WritingDataHandler> pnHandler(testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::PN));
        pnHandler->setString(0, "Patient 0");
        pnHandler->setString(1, "Patient 1");
        pnHandler->setString(2, "Patient 2");
    }
    ASSERT_EQ("Patient 0", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));
    ASSERT_EQ("Patient 1", testDataSet.getString(TagId(0x0010, 0x0010), 0, 1));
    ASSERT_EQ("Patient 2", testDataSet.getString(TagId(0x0010, 0x0010), 0, 2));
    std::unique_ptr<ReadingDataHandlerNumeric> rawHandler(testDataSet.getReadingDataHandlerRaw(TagId(0x0010, 0x0010), 0));
    size_t dataSize;
    const char* data = rawHandler->data(&dataSize);
    std::string fullString(data, dataSize);
    ASSERT_EQ("Patient 0=Patient 1=Patient 2 ", fullString);

    {
        std::string longString((size_t)65, 'a');
        ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), 0, longString, tagVR_t::PN), DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, CSTest)
{
    DataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), 0, "0123456789012345", tagVR_t::CS);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));

    testDataSet.setString(TagId(0x0010, 0x0010), 0, "012345678901234", tagVR_t::CS);
    ASSERT_EQ("012345678901234", testDataSet.getString(TagId(0x0010, 0x0010), 0, 0));

    ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), 0, "01234567890123456", tagVR_t::CS), DataHandlerInvalidDataError);

}


TEST(stringHandlerTest, ASTest)
{
    imebra::DataSet dataSet;

    dataSet.setAge(TagId(0x0010, 0x1010), 0, Age(3, imebra::ageUnit_t::days));
    std::unique_ptr<imebra::Age> age(dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0));
    EXPECT_EQ(3, age->age);
    EXPECT_EQ(imebra::ageUnit_t::days, age->units);
    EXPECT_EQ("003D", dataSet.getString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0));
    EXPECT_FLOAT_EQ(0.008219178, age->years());

    ASSERT_THROW(dataSet.setDouble(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, .01), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setUnsignedLong(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setSignedLong(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setDate(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, imebra::Date(2000, 1, 1, 0, 0, 0, 0, 0, 0)), imebra::DataHandlerDeniedConversionError);

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, "005M");
    age.reset(dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0));
    EXPECT_EQ(5, age->age);
    EXPECT_EQ(imebra::ageUnit_t::months, age->units);
    EXPECT_DOUBLE_EQ(0.41666666666666669, age->years());

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, "018W");
    age.reset(dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0));
    EXPECT_EQ(18, age->age);
    EXPECT_EQ(imebra::ageUnit_t::weeks, age->units);
    EXPECT_DOUBLE_EQ(0.34520548039782323, age->years());

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, "090Y");
    age.reset(dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0));
    EXPECT_EQ(90, age->age);
    EXPECT_EQ(imebra::ageUnit_t::years, age->units);
    EXPECT_DOUBLE_EQ(90, age->years());
}





} // namespace tests

} // namespace imebra
