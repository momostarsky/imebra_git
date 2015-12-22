#include "../../library/implementation/imebraImpl.h"
#include <gtest/gtest.h>

namespace puntoexe
{

namespace imebra
{

namespace tests
{

TEST(integerStringHandlerTest, integerTest)
{
    std::shared_ptr<data> tag(new data());
    {
        std::shared_ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "IS");
        hTag->setSize(1);

        hTag->setDouble(0, 6.5);
        EXPECT_EQ(L"6", hTag->getUnicodeString(0));
        EXPECT_DOUBLE_EQ(6, hTag->getDouble(0));
        EXPECT_EQ(6, hTag->getSignedLong(0));

    }
}



} // namespace tests

} // namespace imebra

} // namespace puntoexe