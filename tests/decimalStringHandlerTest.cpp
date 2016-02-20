#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(decimalStringHandlerTest, decimalTest)
{
    DataSet testDataSet;
    {
        testDataSet.setDouble(0x0028, 0, 0x1051, 0, 0.000001, "DS");
        std::string decimalString = testDataSet.getStringThrow(0x0028, 0, 0x1051, 0, 0);
        ASSERT_TRUE(decimalString == "1e-006" || decimalString == "1e-06" || decimalString == "1e-6");
        double decimalValue = testDataSet.getDoubleThrow(0x0028, 0, 0x1051, 0, 0);
        ASSERT_FLOAT_EQ(0.000001, decimalValue);
    }

    {
        testDataSet.setString(0x0028, 0, 0x1051, 0, "-2e-8", "DS");
        double decimalValue = testDataSet.getDoubleThrow(0x0028, 0, 0x1051, 0, 0);
        ASSERT_FLOAT_EQ(-0.00000002, decimalValue);
    }
}

TEST(decimalStringHandlerTest, decimalTestFail)
{
    DataSet testDataSet;
    testDataSet.setString(0x0028, 0, 0x1051, 0, "Hello", "DS");
    ASSERT_THROW(testDataSet.getDoubleThrow(0x0028, 0, 0x1051, 0, 0), DataHandlerConversionError);
}



} // namespace tests

} // namespace imebra
