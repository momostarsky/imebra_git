#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(decimalStringHandlerTest, decimalTest)
{
    DataSet testDataSet;
    testDataSet.setDouble(0x0028, 0, 0x1051, 0, 0, 0.000001, "DS");
    std::wstring decimalString = testDataSet.getStringThrow(0x0028, 0, 0x1051, 0, 0);
    ASSERT_TRUE(decimalString == L"1e-006" || decimalString == L"1e-06" || decimalString == L"1e-6");

    testDataSet.setString(0x0028, 0, 0x1051, 0, 0, L"-2e-8", "DS");
    double decimalValue = testDataSet.getDoubleThrow(0x0028, 0, 0x1051, 0, 0);
    ASSERT_FLOAT_EQ(-0.00000002, decimalValue);

}

TEST(decimalStringHandlerTest, decimalTestFail)
{
    DataSet testDataSet;
    testDataSet.setString(0x0028, 0, 0x1051, 0, 0, L"Hello", "DS");
    ASSERT_THROW(testDataSet.getDoubleThrow(0x0028, 0, 0x1051, 0, 0), DataHandlerConversionError);
}



} // namespace tests

} // namespace imebra
