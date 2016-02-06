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
    EXPECT_EQ("003D", dataSet.getStringThrow(0x0010, 0, 0x1010, 0, 0));
    EXPECT_FLOAT_EQ(0.008219178, age.years());

    ASSERT_THROW(dataSet.setDouble(0x0010, 0, 0x1010, 0, 0, .01), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setUnsignedLong(0x0010, 0, 0x1010, 0, 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setSignedLong(0x0010, 0, 0x1010, 0, 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setDate(0x0010, 0, 0x1010, 0, 0, imebra::Date(2000, 1, 1, 0, 0, 0, 0, 0, 0)), imebra::DataHandlerDeniedConversionError);

    dataSet.setString(0x0010, 0, 0x1010, 0, 0, "005M");
    age = dataSet.getAgeThrow(0x0010, 0, 0x1010, 0, 0);
    EXPECT_EQ(5, age.age);
    EXPECT_EQ(imebra::ageUnit_t::months, age.units);
    EXPECT_DOUBLE_EQ(0.41666666666666669, age.years());

    dataSet.setString(0x0010, 0, 0x1010, 0, 0, "018W");
    age = dataSet.getAgeThrow(0x0010, 0, 0x1010, 0, 0);
    EXPECT_EQ(18, age.age);
    EXPECT_EQ(imebra::ageUnit_t::weeks, age.units);
    EXPECT_DOUBLE_EQ(0.34520548039782323, age.years());

    dataSet.setString(0x0010, 0, 0x1010, 0, 0, "090Y");
    age = dataSet.getAgeThrow(0x0010, 0, 0x1010, 0, 0);
    EXPECT_EQ(90, age.age);
    EXPECT_EQ(imebra::ageUnit_t::years, age.units);
    EXPECT_DOUBLE_EQ(90, age.years());
}



} // namespace tests

} // namespace imebra

