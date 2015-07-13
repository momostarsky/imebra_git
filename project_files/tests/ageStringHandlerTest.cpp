#include <gtest/gtest.h>
#include "../library/imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

TEST(ageStringHandlerTest, ageTest)
{
	ptr<data> tag(new data(ptr<baseObject>(0)));
	{
		ptr<handlers::dataHandler> hTag= tag->getDataHandler(0, true, "AS");
		hTag->setSize(1);

		hTag->setDouble(0, 0.01);
		std::wstring ageString = hTag->getUnicodeString(0);
        EXPECT_EQ(std::wstring(L"003D"), ageString);

		hTag->setDouble(0, 0.2);
		ageString = hTag->getUnicodeString(0);
        EXPECT_EQ(std::wstring(L"010W"), ageString);

		hTag->setDouble(0, 0.9);
		ageString = hTag->getUnicodeString(0);
        EXPECT_EQ(std::wstring(L"010M"), ageString);

		hTag->setDouble(0, 0.5);
		ageString = hTag->getUnicodeString(0);
        EXPECT_EQ(std::wstring(L"006M"), ageString);

		hTag->setDouble(0, 2.3);
		ageString = hTag->getUnicodeString(0);
        EXPECT_EQ(std::wstring(L"002Y"), ageString);

		std::uint32_t ageInt = hTag->getUnsignedLong(0);
        EXPECT_EQ(2, ageInt);
	}
}



} // namespace tests

} // namespace imebra

} // namespace puntoexe
