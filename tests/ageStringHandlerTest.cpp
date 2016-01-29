#include <gtest/gtest.h>
#include <imebra/dataSet.h>
#include <imebra/exceptions.h>

namespace imebra
{

namespace tests
{

TEST(ageStringHandlerTest, ageTest)
{
    imebra::DataSet dataSet;

    dataSet.setAge(0x0010, 0, 0x1010, 0, 0, Age(3, imebra::ageUnit_t::days));
    imebra::Age age = dataSet.getAgeThrow(0x0010, 0, 0x1010, 0, 0);
    EXPECT_EQ(3, age.age);
    EXPECT_EQ(imebra::ageUnit_t::days, age.units);
    EXPECT_EQ(L"003D", dataSet.getStringThrow(0x0010, 0, 0x1010, 0, 0));

    ASSERT_THROW(dataSet.setDouble(0x0010, 0, 0x1010, 0, 0, .01), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setUnsignedLong(0x0010, 0, 0x1010, 0, 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setSignedLong(0x0010, 0, 0x1010, 0, 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setDate(0x0010, 0, 0x1010, 0, 0, imebra::Date(2000, 1, 1, 0, 0, 0, 0, 0, 0)), imebra::DataHandlerDeniedConversionError);

    dataSet.setString(0x0010, 0, 0x1010, 0, 0, L"005M");
    age = dataSet.getAgeThrow(0x0010, 0, 0x1010, 0, 0);
    EXPECT_EQ(5, age.age);
    EXPECT_EQ(imebra::ageUnit_t::months, age.units);

}



} // namespace tests

} // namespace imebra

