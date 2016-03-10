#include <gtest/gtest.h>
#include <imebra/imebra.h>

namespace imebra
{

namespace tests
{

TEST(ageStringHandlerTest, ageTest)
{
    imebra::DataSet dataSet;

    dataSet.setAge(TagId(0x0010, 0x1010), 0, Age(3, imebra::ageUnit_t::days));
    imebra::Age age = dataSet.getAgeThrow(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0);
    EXPECT_EQ(3, age.age);
    EXPECT_EQ(imebra::ageUnit_t::days, age.units);
    EXPECT_EQ("003D", dataSet.getStringThrow(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0));
    EXPECT_FLOAT_EQ(0.008219178, age.years());

    ASSERT_THROW(dataSet.setDouble(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, .01), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setUnsignedLong(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setSignedLong(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 1), imebra::DataHandlerDeniedConversionError);

    ASSERT_THROW(dataSet.setDate(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, imebra::Date(2000, 1, 1, 0, 0, 0, 0, 0, 0)), imebra::DataHandlerDeniedConversionError);

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, "005M");
    age = dataSet.getAgeThrow(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0);
    EXPECT_EQ(5, age.age);
    EXPECT_EQ(imebra::ageUnit_t::months, age.units);
    EXPECT_DOUBLE_EQ(0.41666666666666669, age.years());

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, "018W");
    age = dataSet.getAgeThrow(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0);
    EXPECT_EQ(18, age.age);
    EXPECT_EQ(imebra::ageUnit_t::weeks, age.units);
    EXPECT_DOUBLE_EQ(0.34520548039782323, age.years());

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, "090Y");
    age = dataSet.getAgeThrow(TagId(imebra::tagId_t::PatientAge_0010_1010), 0, 0);
    EXPECT_EQ(90, age.age);
    EXPECT_EQ(imebra::ageUnit_t::years, age.units);
    EXPECT_DOUBLE_EQ(90, age.years());
}



} // namespace tests

} // namespace imebra

