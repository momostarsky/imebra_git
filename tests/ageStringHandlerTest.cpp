#include <gtest/gtest.h>
#include <imebra/dataSet.h>

namespace imebra
{

namespace tests
{

TEST(ageStringHandlerTest, ageTest)
{
    imebra::DataSet dataSet;

    dataSet.setAge(0x0010, 0, 0x1010, 0, 3, imebra::ageUnit_t::days);
    EXPECT_EQ(L"003D", dataSet.getString(0x0010, 0, 0x1010, 0));
    EXPECT_DOUBLE_EQ(0.00821917808219178, dataSet.getDouble(0x0010, 0, 0x1010, 0));

    dataSet.setDouble(0x0010, 0, 0x1010, 0, .01);
    EXPECT_EQ(L"003D", dataSet.getString(0x0010, 0, 0x1010, 0));

    dataSet.setDouble(0x0010, 0, 0x1010, 0, .02);
    EXPECT_EQ(L"007D", dataSet.getString(0x0010, 0, 0x1010, 0));

    dataSet.setDouble(0x0010, 0, 0x1010, 0, .9);
    EXPECT_EQ(L"010M", dataSet.getString(0x0010, 0, 0x1010, 0));

    dataSet.setDouble(0x0010, 0, 0x1010, 0, .5);
    EXPECT_EQ(L"006M", dataSet.getString(0x0010, 0, 0x1010, 0));

    dataSet.setDouble(0x0010, 0, 0x1010, 0, 4.3);
    EXPECT_EQ(L"004Y", dataSet.getString(0x0010, 0, 0x1010, 0));

    dataSet.setString(0x0010, 0, 0x1010, 0, L"003Y");
    EXPECT_EQ(3, dataSet.getUnsignedLong(0x0010, 0, 0x1010, 0));

    dataSet.setString(0x0010, 0, 0x1010, 0, L"005Y");
    EXPECT_EQ(5, dataSet.getUnsignedLong(0x0010, 0, 0x1010, 0));

    dataSet.setString(0x0010, 0, 0x1010, 0, L"006M");
    EXPECT_EQ(L"006M", dataSet.getString(0x0010, 0, 0x1010, 0));
    EXPECT_EQ(0, dataSet.getUnsignedLong(0x0010, 0, 0x1010, 0));
    EXPECT_DOUBLE_EQ(0.5, dataSet.getDouble(0x0010, 0, 0x1010, 0));

}



} // namespace tests

} // namespace imebra

